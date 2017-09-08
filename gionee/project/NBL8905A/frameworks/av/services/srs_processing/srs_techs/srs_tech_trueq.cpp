/*======================================================================*
 DTS, Inc.
 5220 Las Virgenes Road
 Calabasas, CA 91302  USA

 CONFIDENTIAL: CONTAINS CONFIDENTIAL PROPRIETARY INFORMATION OWNED BY
 DTS, INC. AND/OR ITS AFFILIATES ("DTS"), INCLUDING BUT NOT LIMITED TO
 TRADE SECRETS, KNOW-HOW, TECHNICAL AND BUSINESS INFORMATION. USE,
 DISCLOSURE OR DISTRIBUTION OF THE SOFTWARE IN ANY FORM IS LIMITED TO
 SPECIFICALLY AUTHORIZED LICENSEES OF DTS.  ANY UNAUTHORIZED
 DISCLOSURE IS A VIOLATION OF STATE, FEDERAL, AND INTERNATIONAL LAWS.
 BOTH CIVIL AND CRIMINAL PENALTIES APPLY.

 DO NOT DUPLICATE. COPYRIGHT 2014, DTS, INC. ALL RIGHTS RESERVED.
 UNAUTHORIZED DUPLICATION IS A VIOLATION OF STATE, FEDERAL AND
 INTERNATIONAL LAWS.

 ALGORITHMS, DATA STRUCTURES AND METHODS CONTAINED IN THIS SOFTWARE
 MAY BE PROTECTED BY ONE OR MORE PATENTS OR PATENT APPLICATIONS.
 UNLESS OTHERWISE PROVIDED UNDER THE TERMS OF A FULLY-EXECUTED WRITTEN
 AGREEMENT BY AND BETWEEN THE RECIPIENT HEREOF AND DTS, THE FOLLOWING
 TERMS SHALL APPLY TO ANY USE OF THE SOFTWARE (THE "PRODUCT") AND, AS
 APPLICABLE, ANY RELATED DOCUMENTATION:  (i) ANY USE OF THE PRODUCT
 AND ANY RELATED DOCUMENTATION IS AT THE RECIPIENT’S SOLE RISK:
 (ii) THE PRODUCT AND ANY RELATED DOCUMENTATION ARE PROVIDED "AS IS"
 AND WITHOUT WARRANTY OF ANY KIND AND DTS EXPRESSLY DISCLAIMS ALL
 WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO ANY
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 PURPOSE, REGARDLESS OF WHETHER DTS KNOWS OR HAS REASON TO KNOW OF THE
 USER'S PARTICULAR NEEDS; (iii) DTS DOES NOT WARRANT THAT THE PRODUCT
 OR ANY RELATED DOCUMENTATION WILL MEET USER'S REQUIREMENTS, OR THAT
 DEFECTS IN THE PRODUCT OR ANY RELATED DOCUMENTATION WILL BE
 CORRECTED; (iv) DTS DOES NOT WARRANT THAT THE OPERATION OF ANY
 HARDWARE OR SOFTWARE ASSOCIATED WITH THIS DOCUMENT WILL BE
 UNINTERRUPTED OR ERROR-FREE; AND (v) UNDER NO CIRCUMSTANCES,
 INCLUDING NEGLIGENCE, SHALL DTS OR THE DIRECTORS, OFFICERS, EMPLOYEES,
 OR AGENTS OF DTS, BE LIABLE TO USER FOR ANY INCIDENTAL, INDIRECT,
 SPECIAL, OR CONSEQUENTIAL DAMAGES (INCLUDING BUT NOT LIMITED TO
 DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION, AND LOSS
 OF BUSINESS INFORMATION) ARISING OUT OF THE USE, MISUSE, OR INABILITY
 TO USE THE PRODUCT OR ANY RELATED DOCUMENTATION.
*======================================================================*/

#include "srs_techs/srs_tech_headers.h"

#include <media/AudioSystem.h>

#include SRSLIBINC(srs_peq_api.h)
#include SRSLIBINC(srs_common_ver_api.h)
#include SRSLIBINC(srs_parametriceq_design_api.h)

#define TruEQ_BandCount 4
#define TruEQ_FilterWl  SRSFilter32

char TEQScratch[512];

#undef  LOG_TAG
#define LOG_TAG "SRS_Tech_TruEQ"

namespace android {

struct SRS_Source_TruEQ {

    SRSPeqObj       PObjL;
    SRSPeqObj       PObjR;
    void            *pPBufferL; // TruEQ support
    void            *pPBufferR;
    int             SampleRate;
    int             ChannelCount;
    SRS_Tech_TruEQ  Active;
    bool            ForceActive;
    SRSCoef32       CoefL[SRS_PEQ_FXP_COEFFICIENT_ARRAY_LEN(TruEQ_BandCount)];
    SRSCoef32       CoefR[SRS_PEQ_FXP_COEFFICIENT_ARRAY_LEN(TruEQ_BandCount)];
    bool            DidCreate;
    bool            DidConfig;

    SRS_Source_TruEQ();
    ~SRS_Source_TruEQ();

    void Create(SRS_Source_Out *pOut);
    void Config(SRS_Source_Out *pOut, SRS_Tech_TruEQ *pCFG, bool bBypass);
    void Process_256(SRSSamp *pData);
};

SRS_Source_TruEQ::SRS_Source_TruEQ(){
    SRS_LOG("TruEQ Created");

    DidCreate = false;
    DidConfig = false;

    int tBufRAM = 0;

    const SRSPeqCreateData numBands = { TruEQ_BandCount };
    tBufRAM = SRS_PEQ_GetObjSize(&numBands);

    pPBufferL = malloc(tBufRAM);
    pPBufferR = malloc(tBufRAM);

#ifdef _SRSCFG_PERFTRACK
    SRS_LOG("[SRS_RAMSIZE] TruEQ: %d", (tBufRAM*2)+sizeof(SRS_Source_TruEQ));
#endif  //_SRSCFG_PERFTRACK
}

SRS_Source_TruEQ::~SRS_Source_TruEQ(){
    if (pPBufferL != NULL) free(pPBufferL);
    pPBufferL = NULL;
    if (pPBufferR != NULL) free(pPBufferR);
    pPBufferR = NULL;

    DidCreate = false;
    DidConfig = false;

    SRS_LOG("TruEQ Destroyed");
}

void SRS_Source_TruEQ::Create(SRS_Source_Out *pOut){
    if (pOut->SampleRate <= 0) return;
    if (pOut->ChannelCount != 2) return;

    SampleRate = pOut->SampleRate;
    ChannelCount = pOut->ChannelCount;

    DidCreate = true;
    ForceActive = true;

    const SRSPeqCreateData numBands = { TruEQ_BandCount };
    SRS_PEQ_CreateObj(&PObjL, pPBufferL, NULL, NULL, &numBands);
    SRS_PEQ_CreateObj(&PObjR, pPBufferR, NULL, NULL, &numBands);

    DidConfig = false;
}

void SRS_Source_TruEQ::Config(SRS_Source_Out *pOut, SRS_Tech_TruEQ *pCFG, bool bBypass){
    if (DidCreate == false) return;

    int i;
    int numBandsActive = 0;

    // TruEQ
    bool bCalcL = false;
    for (i=0; i<4; i++){
        if (DIFF_FORCED(Params[i][0]) || DIFF_FORCED(Params[i][1]) || DIFF_FORCED(Params[i][2]) || DIFF_FORCED(LBands[i])){
            bCalcL = true;
        }
    }

    bool bCalcR = false;
    for (i=0; i<4; i++){
        if (DIFF_FORCED(Params[i+4][0]) || DIFF_FORCED(Params[i+4][1]) || DIFF_FORCED(Params[i+4][2]) || DIFF_FORCED(RBands[i])){
            bCalcR = true;
        }
    }

    bool bMirrorCoefs = false;
    if (bCalcL || bCalcR){
        bool bSame = true;

        for (i=0; i<4; i++){
            if (pCFG->Params[i][0] != pCFG->Params[i+4][0]) bSame = false;
            if (pCFG->Params[i][1] != pCFG->Params[i+4][1]) bSame = false;
            if (pCFG->Params[i][2] != pCFG->Params[i+4][2]) bSame = false;
            if (pCFG->LBands[i] != pCFG->RBands[i]) bSame = false;
        }

        if (bSame == true){
            bMirrorCoefs = true;
            bCalcL = true;
            bCalcR = false;
        }
    }

    if (bCalcL){

        SRSParametriceqBandSpec tBands[TruEQ_BandCount];
        SRSParametriceqSpec tSpec;

        // Design the filter bands, only if it is enabled and the center frequency is less than the samplerate/2
        numBandsActive = 0;
        for (i=0; i<4; i++){
            if(pCFG->LBands[i] == true){                            // Band enabled
                if(pCFG->Params[i][0] <= (SampleRate*0.5f)){        // Center frequency is within nyquist rate
                    tBands[numBandsActive].Type = SRS_PEQ_BAND_TYPE_TRADITIONAL;
                    tBands[numBandsActive].CenterFreq = pCFG->Params[i][0];
                    tBands[numBandsActive].Gain = pCFG->Params[i][1];
                    tBands[numBandsActive].QFactor = pCFG->Params[i][2];
                    tBands[numBandsActive].InvertPhase = 0;

                    if(tBands[numBandsActive].CenterFreq < 5.0f) tBands[numBandsActive].CenterFreq = 5.0f;
                    // if(tBands[numBandsActive].CenterFreq > (SampleRate*0.5f)) tBands[i].CenterFreq = SampleRate*0.5f; (This doesnt make sense here )

                    if(tBands[numBandsActive].QFactor < 0.1f) tBands[numBandsActive].QFactor = 0.1f;
                    if(tBands[numBandsActive].QFactor > 10.0f) tBands[numBandsActive].QFactor = 10.0f;

                    // if(pCFG->LBands[i] == false) tBands[i].Gain = 0.0f;    // Disabled means disabled... (This doesnt make sense here )
                    numBandsActive++;
                }
            }
        }

        tSpec.SampleRate = SampleRate;
        tSpec.BandSpecs  = tBands;
        tSpec.NumOfBands = numBandsActive;

        char tWork[SRS_PEQ_DESIGN_WORKSPACE_SIZE(TruEQ_BandCount)];
        SRS_ParametriceqDesignFxp32(&tSpec, CoefL, tWork); //Design TruEQ filters

        SRSPeqFilterCfg filterCfg;
        filterCfg.NumOfBands = numBandsActive;
        filterCfg.FilterCoefs = (void *)CoefL;
        filterCfg.FilterWl = TruEQ_FilterWl;
        SRS_PEQ_InitObj(PObjL, &filterCfg);

        ForceActive = true;
    }

    //if (DIFF_FORCED(LBands[0])) SRS_SetParametricEqBandEnable(PObjL, 0, pCFG->LBands[0]);
    //if (DIFF_FORCED(LBands[1])) SRS_SetParametricEqBandEnable(PObjL, 1, pCFG->LBands[1]);
    //if (DIFF_FORCED(LBands[2])) SRS_SetParametricEqBandEnable(PObjL, 2, pCFG->LBands[2]);
    //if (DIFF_FORCED(LBands[3])) SRS_SetParametricEqBandEnable(PObjL, 3, pCFG->LBands[3]);
    //if (DIFF_FORCED(LEnable)) SRS_PEQ_SetEnable(PObjL, pCFG->LEnable);

    if (DIFF_FORCED(LEnable))
        SRS_PEQ_SetEnable(PObjL, pCFG->LEnable);

    if (bMirrorCoefs)
    {
        SRSPeqFilterCfg filterCfg;
        filterCfg.NumOfBands = numBandsActive;
        filterCfg.FilterCoefs = (void *)CoefL;
        filterCfg.FilterWl = TruEQ_FilterWl;
        SRS_PEQ_InitObj(PObjR, &filterCfg);
    }

    if (bCalcR){

        SRSParametriceqBandSpec tBands[TruEQ_BandCount];
        SRSParametriceqSpec tSpec;

        // Design the filter bands, only if it is enabled and the center frequency is less than the samplerate/2
        numBandsActive = 0;
        for (i=0; i<4; i++){
            if(pCFG->RBands[i] == true){                            // Band enabled
                if(pCFG->Params[i+4][0] <= (SampleRate*0.5f)){      // Center frequency is within nyquist rate
                    tBands[numBandsActive].Type = SRS_PEQ_BAND_TYPE_TRADITIONAL;
                    tBands[numBandsActive].CenterFreq = pCFG->Params[i+4][0];
                    tBands[numBandsActive].Gain = pCFG->Params[i+4][1];
                    tBands[numBandsActive].QFactor = pCFG->Params[i+4][2];
                    tBands[numBandsActive].InvertPhase = 0;

                    if(tBands[numBandsActive].CenterFreq < 5.0f) tBands[numBandsActive].CenterFreq = 5.0f;
                    // if(tBands[numBandsActive].CenterFreq > (SampleRate*0.5f)) tBands[i].CenterFreq = SampleRate*0.5f; (This doesnt make sense here )

                    if(tBands[numBandsActive].QFactor < 0.1f) tBands[numBandsActive].QFactor = 0.1f;
                    if(tBands[numBandsActive].QFactor > 10.0f) tBands[numBandsActive].QFactor = 10.0f;

                    // if(pCFG->RBands[i] == false) tBands[i].Gain = 0.0f;    // Disabled means disabled... (This doesnt make sense here )
                    numBandsActive++;
                }
            }
        }

        tSpec.SampleRate = SampleRate;
        tSpec.BandSpecs = tBands;
        tSpec.NumOfBands = numBandsActive;

        char tWork[SRS_PEQ_DESIGN_WORKSPACE_SIZE(TruEQ_BandCount)];
        SRS_ParametriceqDesignFxp32(&tSpec, CoefR, tWork); //Design TruEQ filters

        SRSPeqFilterCfg filterCfg;
        filterCfg.NumOfBands = numBandsActive;
        filterCfg.FilterCoefs = (void *)CoefR;
        filterCfg.FilterWl = TruEQ_FilterWl;
        SRS_PEQ_InitObj(PObjR, &filterCfg);

        ForceActive = true;
    }

    //if (DIFF_FORCED(RBands[0])) SRS_SetParametricEqBandEnable(PObjR, 0, pCFG->RBands[0]);
    //if (DIFF_FORCED(RBands[1])) SRS_SetParametricEqBandEnable(PObjR, 1, pCFG->RBands[1]);
    //if (DIFF_FORCED(RBands[2])) SRS_SetParametricEqBandEnable(PObjR, 2, pCFG->RBands[2]);
    //if (DIFF_FORCED(RBands[3])) SRS_SetParametricEqBandEnable(PObjR, 3, pCFG->RBands[3]);
    //if (DIFF_FORCED(REnable)) SRS_PEQ_SetEnable(PObjR, pCFG->REnable);
    if (DIFF_FORCED(REnable))
      SRS_PEQ_SetEnable(PObjR, pCFG->REnable);


    if (DIFF_FORCED(IGain)){
        SRS_PEQ_SetInputGain(PObjL, SRS_FXP16(pCFG->IGain, SRS_PEQ_GAIN_IWL));
        SRS_PEQ_SetInputGain(PObjR, SRS_FXP16(pCFG->IGain, SRS_PEQ_GAIN_IWL));
    }
    if (DIFF_FORCED(OGain)){
        SRS_PEQ_SetOutputGain(PObjL, SRS_FXP16(pCFG->OGain, SRS_PEQ_GAIN_IWL));
        SRS_PEQ_SetOutputGain(PObjR, SRS_FXP16(pCFG->OGain, SRS_PEQ_GAIN_IWL));
    }
    if (DIFF_FORCED(BGain)){
        SRS_PEQ_SetBypassGain(PObjL, SRS_FXP16(pCFG->BGain, SRS_PEQ_GAIN_IWL));
        SRS_PEQ_SetBypassGain(PObjR, SRS_FXP16(pCFG->BGain, SRS_PEQ_GAIN_IWL));
    }

    DidConfig = true;
    Active = *pCFG;

    if (bBypass){
        SRS_PEQ_SetEnable(PObjL, false);
        Active.LEnable = false;
        SRS_PEQ_SetEnable(PObjR, false);
        Active.REnable = false;
    }

    ForceActive = false;
}

void SRS_Source_TruEQ::Process_256(SRSSamp *pData){
    SRS_PEQ_Process(PObjL, pData, 256);
    SRS_PEQ_Process(PObjR, pData + 256, 256);
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// =-=-=-=-=-=- External Interfacing =-=-=-=-=-=-
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

SRS_Source_TruEQ* SRS_Create_TruEQ(SRS_Source_Out* pOut){
    SRS_Source_TruEQ* pSrc = new SRS_Source_TruEQ();
    pSrc->Create(pOut);
    return pSrc;
}

void SRS_Destroy_TruEQ(SRS_Source_TruEQ* pSrc, SRS_Source_Out* pOut){
    if (pSrc == NULL) return;
    delete pSrc;
}

void SRS_Config_TruEQ(SRS_Source_TruEQ* pSrc, SRS_Source_Out* pOut, SRS_Tech_TruEQ* pCFG, bool bBypass){
    if (pSrc == NULL) return;
    pSrc->Config(pOut, pCFG, bBypass);
}

void SRS_Process_TruEQ_256(SRS_Source_TruEQ* pSrc, SRSSamp* pData){
    if (pSrc == NULL) return;
    if (pSrc->DidConfig == false) return;

    pSrc->Process_256(pData);
}

enum {
    TEQ_IGain,
    TEQ_OGain,
    TEQ_BGain,
    TEQ_L_Enable,
    TEQ_R_Enable,
    TEQ_LB0,
    TEQ_LB1,
    TEQ_LB2,
    TEQ_LB3,
    TEQ_RB0,
    TEQ_RB1,
    TEQ_RB2,
    TEQ_RB3,
    TEQ_Def_LBand0,
    TEQ_Def_LBand1,
    TEQ_Def_LBand2,
    TEQ_Def_LBand3,
    TEQ_Def_RBand0,
    TEQ_Def_RBand1,
    TEQ_Def_RBand2,
    TEQ_Def_RBand3,
    TEQ_Skip,
};

SRS_Param gTruEQ_Params[] = {
    { TEQ_IGain,        SRS_PTYP_CFG,   SRS_PFMT_FLOAT,     1.0f,   0.0f,   1.0f,   "trueq_igain", "TruEQ Input Gain", "gain", "", 0},
    { TEQ_OGain,        SRS_PTYP_CFG,   SRS_PFMT_FLOAT,     1.0f,   0.0f,   4.0f,   "trueq_ogain", "TruEQ Output Gain", "gain", "", 0},
    { TEQ_BGain,        SRS_PTYP_CFG,   SRS_PFMT_FLOAT,     1.0f,   0.0f,   4.0f,   "trueq_bgain", "TruEQ Bypass Gain", "gain", "", 0},

    { TEQ_L_Enable,     SRS_PTYP_CFG,   SRS_PFMT_BOOL,      0.0f,   0.0f,   1.0f,   "trueq_left_enable", "TruEQ Left Toggle", "toggle", "", 0},
    { TEQ_LB0,          SRS_PTYP_CFG,   SRS_PFMT_BOOL,      0.0f,   0.0f,   1.0f,   "trueq_lband0_enable", "TruEQ Left Band 0 Toggle", "toggle", "", 0},
    { TEQ_LB1,          SRS_PTYP_CFG,   SRS_PFMT_BOOL,      0.0f,   0.0f,   1.0f,   "trueq_lband1_enable", "TruEQ Left Band 1 Toggle", "toggle", "", 0},
    { TEQ_LB2,          SRS_PTYP_CFG,   SRS_PFMT_BOOL,      0.0f,   0.0f,   1.0f,   "trueq_lband2_enable", "TruEQ Left Band 2 Toggle", "toggle", "", 0},
    { TEQ_LB3,          SRS_PTYP_CFG,   SRS_PFMT_BOOL,      0.0f,   0.0f,   1.0f,   "trueq_lband3_enable", "TruEQ Left Band 3 Toggle", "toggle", "", 0},

    { TEQ_R_Enable,     SRS_PTYP_CFG,   SRS_PFMT_BOOL,      0.0f,   0.0f,   1.0f,   "trueq_right_enable", "TruEQ Right Toggle", "toggle", "", 0},
    { TEQ_RB0,          SRS_PTYP_CFG,   SRS_PFMT_BOOL,      0.0f,   0.0f,   1.0f,   "trueq_rband0_enable", "TruEQ Right Band 0 Toggle", "toggle", "", 0},
    { TEQ_RB1,          SRS_PTYP_CFG,   SRS_PFMT_BOOL,      0.0f,   0.0f,   1.0f,   "trueq_rband1_enable", "TruEQ Right Band 1 Toggle", "toggle", "", 0},
    { TEQ_RB2,          SRS_PTYP_CFG,   SRS_PFMT_BOOL,      0.0f,   0.0f,   1.0f,   "trueq_rband2_enable", "TruEQ Right Band 2 Toggle", "toggle", "", 0},
    { TEQ_RB3,          SRS_PTYP_CFG,   SRS_PFMT_BOOL,      0.0f,   0.0f,   1.0f,   "trueq_rband3_enable", "TruEQ Right Band 3 Toggle", "toggle", "", 0},

    { TEQ_Def_LBand0,   SRS_PTYP_CFG,   SRS_PFMT_FLOATARRAY,    0.0f,   0.0f,   0.0f,   "trueq_lband0", "TruEQ Left Band 0 Tuning (CF Gain Q)", "", "3", 0},
    { TEQ_Def_LBand1,   SRS_PTYP_CFG,   SRS_PFMT_FLOATARRAY,    0.0f,   0.0f,   0.0f,   "trueq_lband1", "TruEQ Left Band 1 Tuning", "", "3", 0},
    { TEQ_Def_LBand2,   SRS_PTYP_CFG,   SRS_PFMT_FLOATARRAY,    0.0f,   0.0f,   0.0f,   "trueq_lband2", "TruEQ Left Band 2 Tuning", "", "3", 0},
    { TEQ_Def_LBand3,   SRS_PTYP_CFG,   SRS_PFMT_FLOATARRAY,    0.0f,   0.0f,   0.0f,   "trueq_lband3", "TruEQ Left Band 3 Tuning", "", "3", 0},
    { TEQ_Def_RBand0,   SRS_PTYP_CFG,   SRS_PFMT_FLOATARRAY,    0.0f,   0.0f,   0.0f,   "trueq_rband0", "TruEQ Right Band 0 Tuning", "", "3", 0},
    { TEQ_Def_RBand1,   SRS_PTYP_CFG,   SRS_PFMT_FLOATARRAY,    0.0f,   0.0f,   0.0f,   "trueq_rband1", "TruEQ Right Band 1 Tuning", "", "3", 0},
    { TEQ_Def_RBand2,   SRS_PTYP_CFG,   SRS_PFMT_FLOATARRAY,    0.0f,   0.0f,   0.0f,   "trueq_rband2", "TruEQ Right Band 2 Tuning", "", "3", 0},
    { TEQ_Def_RBand3,   SRS_PTYP_CFG,   SRS_PFMT_FLOATARRAY,    0.0f,   0.0f,   0.0f,   "trueq_rband3", "TruEQ Right Band 3 Tuning", "", "3", 0},

    { TEQ_Skip,         SRS_PTYP_CFG,   SRS_PFMT_BOOL,      0.0f,   0.0f,   1.0f,   "trueq_skip", "Skips TruEQ when true", "toggle", "", 0},
};

SRS_Param* SRS_GetBank_TruEQ(int& paramCount){
    paramCount = sizeof(gTruEQ_Params)/sizeof(SRS_Param);
    return gTruEQ_Params;
}

char* SRS_GetVersion_TruEQ(char* pWork, size_t maxBytes){
    int v1 = SRS_PEQ_GetTechVersion(SRS_VERSION_MAJOR);
    int v2 = SRS_PEQ_GetTechVersion(SRS_VERSION_MINOR);
    int v3 = SRS_PEQ_GetTechVersion(SRS_VERSION_REVISION);
    int v4 = SRS_PEQ_GetTechVersion(SRS_VERSION_RELEASE);
    int l1 = SRS_PEQ_GetLibVersion(SRS_VERSION_MAJOR);
    int l2 = SRS_PEQ_GetLibVersion(SRS_VERSION_MINOR);
    int l3 = SRS_PEQ_GetLibVersion(SRS_VERSION_REVISION);
    int l4 = SRS_PEQ_GetLibVersion(SRS_VERSION_RELEASE);
    snprintf(pWork, maxBytes, "%d.%d.%d.%d - lib %d.%d.%d.%d", v1, v2, v3, v4, l1, l2, l3, l4);
    return pWork;
}

void SRS_SetParam_TruEQ(SRS_Tech_TruEQ* pCFG, SRS_Param* pParam, const char* pValue){
    HELP_ParamIn In;

    switch (pParam->EnumID){
        case TEQ_IGain: pCFG->IGain = In.GetFloat(pValue); break;
        case TEQ_OGain: pCFG->OGain = In.GetFloat(pValue); break;
        case TEQ_BGain: pCFG->BGain = In.GetFloat(pValue); break;
        case TEQ_Skip: pCFG->Skip = In.GetBool(pValue); break;

        case TEQ_L_Enable: pCFG->LEnable = In.GetBool(pValue); break;
        case TEQ_R_Enable: pCFG->REnable = In.GetBool(pValue); break;

        case TEQ_LB0:
        case TEQ_LB1:
        case TEQ_LB2:
        case TEQ_LB3: { int tIdx = pParam->EnumID-TEQ_LB0; pCFG->LBands[tIdx] = In.GetBool(pValue); } break;

        case TEQ_RB0:
        case TEQ_RB1:
        case TEQ_RB2:
        case TEQ_RB3: { int tIdx = pParam->EnumID-TEQ_RB0; pCFG->RBands[tIdx] = In.GetBool(pValue); } break;

        case TEQ_Def_LBand0:
        case TEQ_Def_LBand1:
        case TEQ_Def_LBand2:
        case TEQ_Def_LBand3:
        case TEQ_Def_RBand0:
        case TEQ_Def_RBand1:
        case TEQ_Def_RBand2:
        case TEQ_Def_RBand3:
        {
            int tIdx = pParam->EnumID-TEQ_Def_LBand0;
            float tHold[3];
            float* pD = tHold;
            int i;

            float* pS = pCFG->Params[tIdx];
            for (i=0; i<3; i++) tHold[i] = pS[i];       // Fill with current values...
            if (sscanf(pValue, "%f,%f,%f", pD+0, pD+1, pD+2) == 3){
                for (i=0; i<3; i++) pS[i] = tHold[i];
            }
        } break;
    }
}

const char* SRS_GetParam_TruEQ(SRS_Tech_TruEQ* pCFG, SRS_Param* pParam){
    HELP_ParamOut Out;

    switch (pParam->EnumID){
        case TEQ_IGain: return Out.FromFloat(pCFG->IGain);
        case TEQ_OGain: return Out.FromFloat(pCFG->OGain);
        case TEQ_BGain: return Out.FromFloat(pCFG->BGain);
        case TEQ_Skip: return Out.FromBool(pCFG->Skip);

        case TEQ_L_Enable: return Out.FromBool(pCFG->LEnable);
        case TEQ_R_Enable: return Out.FromBool(pCFG->REnable);

        case TEQ_LB0:
        case TEQ_LB1:
        case TEQ_LB2:
        case TEQ_LB3: { int tIdx = pParam->EnumID-TEQ_LB0; return Out.FromBool(pCFG->LBands[tIdx]); } break;

        case TEQ_RB0:
        case TEQ_RB1:
        case TEQ_RB2:
        case TEQ_RB3: { int tIdx = pParam->EnumID-TEQ_RB0; return Out.FromBool(pCFG->RBands[tIdx]); } break;

        case TEQ_Def_LBand0:
        case TEQ_Def_LBand1:
        case TEQ_Def_LBand2:
        case TEQ_Def_LBand3:
        case TEQ_Def_RBand0:
        case TEQ_Def_RBand1:
        case TEQ_Def_RBand2:
        case TEQ_Def_RBand3:
        {
            int tIdx = pParam->EnumID-TEQ_Def_LBand0;
            float* pS = pCFG->Params[tIdx];

            snprintf(TEQScratch, sizeof(TEQScratch), "%f,%f,%f", pS[0], pS[1], pS[2]);
            return TEQScratch;
        } break;
    }

    return "";
}

void SRS_Default_TruEQ(SRS_Tech_TruEQ* pCFG){
    pCFG->IGain = 1.0f;
    pCFG->OGain = 1.0f;
    pCFG->BGain = 1.0f;
    pCFG->Skip = false;

    pCFG->LEnable = false;
    pCFG->REnable = false;
    memset(pCFG->LBands, 0, sizeof(pCFG->LBands));
    memset(pCFG->RBands, 0, sizeof(pCFG->RBands));

    memset(pCFG->Params, 0, sizeof(pCFG->Params));

    for (int i=0; i<8; i++) pCFG->Params[i][2] = 2.0f;
}

};

