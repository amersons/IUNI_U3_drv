/*******************************************************************************
 *
 * Description: 
 *		Define ScaladoLiveEffect to set scalado live effects.
 *
 * Author  : wutangzhi
 * Email   : wutz@gionee.com
 * Date    : 2012-06-11
 *
 *******************************************************************************/

#include <utils/Log.h>
#include "ScaladoLiveEffect.h"

#define LOG_TAG "ScaladoLiveEffect"

#define BASE_WIDTH 640
#define BASE_HEIGHT 480

namespace android {

ScaladoLiveEffect::ScaladoLiveEffect() 
	:mHeight(0),
	mWidth(0)
{

}

CRESULT 
ScaladoLiveEffect::
setScaladoLiveEffect(CTSession session, GNLiveEffect_t effect, int width, int height)
{
	CRESULT result = CERR_OK;

	if (effect < GN_LIVE_EFFECT_NONE || effect >= GN_LIVE_EFFECT_MAX) {
		PRINTE("invalid effect value");

		result= CERR_INVALID_PARAMETER;
		return result;
	}

	mWidth = width;
	mHeight = height;

	switch (effect) {
		case GN_LIVE_EFFECT_NONE:
			break;
		case GN_LIVE_EFFECT_ANTIQUE:
			result = setAntiqueEffect(session);
			break;
		case GN_LIVE_EFFECT_CARTOON:
			result = setCartoonEffect(session);
			break;
		case GN_LIVE_EFFECT_EMBOSS:
			result = setEmbossEffect(session);
			break;
		case GN_LIVE_EFFECT_FLIP:
			result = setFlipEffect(session);
			break;
		case GN_LIVE_EFFECT_FOG:
			result = setFogEffect(session);
			break;
		case GN_LIVE_EFFECT_GRAYSCALE:
			result = setGrayscaleEffect(session);
			break;
		case GN_LIVE_EFFECT_LOMO_BLUE:
			result = setLomoEffect(session, LOMO_STYLE_BLUE);
			break;
		case GN_LIVE_EFFECT_LOMO_GREEN:
			result = setLomoEffect(session, LOMO_STYLE_GREEN);
			break;
		case GN_LIVE_EFFECT_LOMO_NEUTRAL:
			result = setLomoEffect(session, LOMO_STYLE_NEUTRAL);
			break;
		case GN_LIVE_EFFECT_LOMO_RED:
			result = setLomoEffect(session, LOMO_STYLE_RED);
			break;
		case GN_LIVE_EFFECT_LOMO_YELLOW:
			result = setLomoEffect(session, LOMO_STYLE_YELLOW);
			break;
		case GN_LIVE_EFFECT_MAGICPEN:
			result = setMagicpenEffect(session);
			break;
		case GN_LIVE_EFFECT_MILKY:
			result = setMilkyEffect(session);
			break;
		case GN_LIVE_EFFECT_MIRROR:
			result = setMirrorEffect(session);
			break;
		case GN_LIVE_EFFECT_NEGATIVE:
			result = setNegativeEffect(session);
			break;
		case GN_LIVE_EFFECT_OILY:
			result = setOilyEffect(session);
			break;
		case GN_LIVE_EFFECT_PAINT:
			result = setPaintEffect(session);
			break;
		case GN_LIVE_EFFECT_SEPIA:
			result = setSepiaEffect(session);
			break;
		case GN_LIVE_EFFECT_SKETCH_COLOR:
			result = setSketchEffect(session, SKETCH_COLOR);
			break;
		case GN_LIVE_EFFECT_SKETCH_GRAY:
			result = setSketchEffect(session, SKETCH_GRAY);
			break;
		case GN_LIVE_EFFECT_SOLARIZE:
			result = setSolarizeEffect(session);
			break;
		case GN_LIVE_EFFECT_STAMP:
			result = setStampEffect(session);
			break;
		case GN_LIVE_EFFECT_DOF:
			result = setDofEffect(session);
			break;
		case GN_LIVE_EFFECT_VIGNETTING:
			result = setVignettingEffect(session);
			break;
		case GN_LIVE_EFFECT_WARP_FISHEYE:
			result = setWarpEffect(session, WARP_WARP_FISHEYE_FILENAME, -1);
			break;
		case GN_LIVE_EFFECT_WARP_ALIENSCUM:
			result = setWarpEffect(session, WARP_ALIENSCUM_FILENAME, -1);
			break;
		case GN_LIVE_EFFECT_WARP_BIGBUPPA:
			result = setWarpEffect(session, WARP_BIGBUPPA_FILENAME, -1);
			break;
		case GN_LIVE_EFFECT_WARP_BOOZIEBOWL:
			result = setWarpEffect(session, WARP_BOOZIEBOWL_FILENAME, -1);
			break;
		case GN_LIVE_EFFECT_WARP_CONEHEAD:
			result = setWarpEffect(session, WARP_CONEHEAD_FILENAME, -1);
			break;
		case GN_LIVE_EFFECT_WARP_FUNKYFRESH:
			result = setWarpEffect(session, WARP_FUNKYFRESH_FILENAME, -1);
			break;
		case GN_LIVE_EFFECT_WARP_JELLYBELLY:
			result = setWarpEffect(session, WARP_JELLYBELLY_FILENAME, -1);
			break;
		case GN_LIVE_EFFECT_WARP_PETTYPETIT:
			result = setWarpEffect(session, WARP_PETTYPETIT_FILENAME, -1);
			break;
		case GN_LIVE_EFFECT_WARP_EYEBALLEDEVY:
			result = setWarpEffect(session, WARP_EYEBALLEDEVY_FILENAME, -1);
			break;
		case GN_LIVE_EFFECT_WARP_SPEEDYWEED:
			result = setWarpEffect(session, WARP_SPEEDYWEED_FILENAME, -1);
			break;
		case GN_LIVE_EFFECT_WARP_MOSAIC:
			result = setMosaicEffect(session);
			break;
		case GN_LIVE_EFFECT_WARP_FROST:
			result = setForstEffect(session);
			break;
		case GN_LIVE_EFFECT_WARP_MOON_LIGHT:
			result = setMoonLightEffect(session);
			break;
		case GN_LIVE_EFFECT_WARP_NOISE:
			result = setNoiseEffect(session);
			break;
		case GN_LIVE_EFFECT_WARP_WATER_COLOR:
			result = setWaterColorEffect(session);
			break;
		default:
			PRINTE("unknown effect value");
			break;
	}

	return result;
}

CRESULT ScaladoLiveEffect::setAntiqueEffect(CTSession session)
{
	CRESULT result = CERR_OK;

	result = caps_applyAntique(session);
	if (result != CERR_OK) {
		PRINTE("Failed to set antique effect");
	}
	
	return result;
}

CRESULT ScaladoLiveEffect::setCartoonEffect(CTSession session)
{
	CRESULT result = CERR_OK;

	result = caps_beginCartoon(session);
	if (result == CERR_OK) {
		result = caps_setCartoon(session, true);

		if (result != CERR_OK) {
			PRINTE("Failed to set cartoon effect");
		}

		caps_endCartoon(session);
	}
	
	return result;
}

CRESULT ScaladoLiveEffect::setEmbossEffect(CTSession session)
{
	CRESULT result = CERR_OK;

	result = caps_beginEmboss(session);
	if (result == CERR_OK) {
		result = caps_setEmboss(session, 1.0);

		if (result != CERR_OK) {
			PRINTE("Failed to set emboss effect");
		}

		caps_endEmboss(session);
	}
	
	return result;
}

CRESULT ScaladoLiveEffect::setFlipEffect(CTSession session)
{
	CRESULT result = CERR_OK;

#if 0
	result = caps_beginRotation(session);
	if (result == CERR_OK) {
		result = caps_setRotation(session, 180, SCALE_IGNORE);

		if (result != CERR_OK) {
			PRINTE("Failed to set flip effect");
		}

		caps_endRotation(session);
	}
#else
	result = caps_beginFlip(session);
	if (result == CERR_OK) {
		result = caps_setFlip(session, FLIP_HORIZONTAL);

		if (result != CERR_OK) {
			PRINTE("Failed to set flip effect");
		}

		caps_endFlip(session);
	}
#endif
	
	return result;
}

CRESULT ScaladoLiveEffect::setFogEffect(CTSession session)
{
	CRESULT result = CERR_OK;
	
	result = caps_applyFog(session);
	if (result != CERR_OK) {
		PRINTE("Failed to set fog effect");
	}
	
	return result;
}

CRESULT ScaladoLiveEffect::setGrayscaleEffect(CTSession session)
{
	CRESULT result = CERR_OK;

	result = caps_applyGrayscale(session);
	if (result != CERR_OK) {
		PRINTE("Failed to set grayscale effect");
	}
	
	return result;
}

CRESULT ScaladoLiveEffect::setLomoEffect(CTSession session, CAPS_LOMO_STYLE lomoStyle)
{
	CRESULT result = CERR_OK;

	result = caps_beginLomo(session);
	if (result == CERR_OK) {
		result = caps_setLomo(session, 0.5, 0.5, LOMO_VIGNETTING_MEDIUM, lomoStyle);

		if (result != CERR_OK) {
			PRINTE("Failed to set lomo effect");
		}

		caps_endLomo(session);
	}
	
	return result;
}

CRESULT ScaladoLiveEffect::setMagicpenEffect(CTSession session)
{
	CRESULT result = CERR_OK;

	result = caps_applyMagicPen(session);
	if (result != CERR_OK) {
		PRINTE("Failed to set magicpen effect");
	}
	
	return result;
}

CRESULT ScaladoLiveEffect::setMilkyEffect(CTSession session)
{
	CRESULT result = CERR_OK;

	result = caps_applyMilky(session);
	if (result != CERR_OK) {
		PRINTE("Failed to set milky effect");
	}
	
	return result;
}

CRESULT ScaladoLiveEffect::setMirrorEffect(CTSession session)
{
	CRESULT result = CERR_OK;

	result = caps_applyMirror(session);
	if (result != CERR_OK) {
		PRINTE("Failed to set mirror effect");
	}
	
	return result;
}

CRESULT ScaladoLiveEffect::setNegativeEffect(CTSession session)
{
	CRESULT result = CERR_OK;
	
	result = caps_applyNegative(session);
	if (result != CERR_OK) {
		PRINTE("Failed to set negative effect");
	}
	
	return result;
}

CRESULT ScaladoLiveEffect::setOilyEffect(CTSession session)
{
	CRESULT result = CERR_OK;

	result = caps_applyOily(session);
	if (result != CERR_OK) {
		PRINTE("Failed to set oily effect");
	}
	
	return result;
}

CRESULT ScaladoLiveEffect::setPaintEffect(CTSession session)
{
	CRESULT result = CERR_OK;

	result = caps_beginPaint(session);
	if (result == CERR_OK) {
		result = caps_setPaint(session, 3);

		if (result != CERR_OK) {
			PRINTE("Failed to set paint effect");
		}

		caps_endPaint(session);
	}
	
	return result;
}

CRESULT ScaladoLiveEffect::setSepiaEffect(CTSession session)
{
	CRESULT result = CERR_OK;

	result = caps_beginSepia(session);
	if (result == CERR_OK) {
		result = caps_setSepia(session, SEPIA_HIGH);

		if (result != CERR_OK) {
			PRINTE("Failed to set sepia effect");
		}

		caps_endSepia(session);
	}
	
	return result;
}

CRESULT ScaladoLiveEffect::setSketchEffect(CTSession session, CAPS_SKETCH_MODE mode)
{
	CRESULT result = CERR_OK;
	
	result = caps_applySketch(session, mode);
	if (result != CERR_OK) {
		PRINTE("Failed to set sketch effect");
	}
	
	return result;
}

CRESULT ScaladoLiveEffect::setSolarizeEffect(CTSession session)
{
	CRESULT result = CERR_OK;
	
	result = caps_beginSolarize(session);
	if (result == CERR_OK) {
		result = caps_setSolarize(session, 0.5);

		if (result != CERR_OK) {
			PRINTE("Failed to set solarize effect");
		}

		caps_endSolarize(session);
	}
	
	return result;
}

CRESULT ScaladoLiveEffect::setStampEffect(CTSession session)
{
	CRESULT result = CERR_OK;
	
	result = caps_beginStamp(session);
	if (result == CERR_OK) {
		result = caps_setStamp(session, 0, 128);

		if (result != CERR_OK) {
			PRINTE("Failed to set stamp effect");
		}

		caps_endStamp(session);
	}
	
	return result;
}

CRESULT ScaladoLiveEffect::setDofEffect(CTSession session)
{
	CRESULT result = CERR_OK;
	#if 0
	CTRect resion[] = {{0, 0, 160, 480}, {480, 0, 160, 480}, 
		{160, 0, 320, 120}, {160, 360, 320, 120}};

	result = caps_beginBlur(session);
	if (result == CERR_OK) {
		caps_setBlurRegionMode(session, BLUR_REGION_RECTANGULAR);
		result = caps_setBlur(session, BLUR_HIGH, resion);

		if (result != CERR_OK) {
			PRINTE("Failed to set dof effect");
		}

		caps_endBlur(session);
	}
	#endif
	
	return result;
}

CRESULT ScaladoLiveEffect::setVignettingEffect(CTSession session)
{
	CRESULT result = CERR_OK;
	CTRect resion = {0, 0, 0, 0};
	CTColor color = {255, 0, 0, 0};

	resion.x = (mWidth >> 4) * 5;
	resion.y = (mHeight >> 4) * 5;
	resion.w = (mWidth >> 4) * 5;
	resion.h = (mHeight >> 4) * 5;

	result = caps_beginVignetting(session);
	if (result == CERR_OK) {
		result = caps_setVignetting(session, resion, 3, color);

		if (result != CERR_OK) {
			PRINTE("Failed to set vignetting effect");
		}

		caps_endVignetting(session);
	}
	
	return result;
}

CRESULT ScaladoLiveEffect::setWarpEffect(CTSession session, const DCHAR* filename, int index)
{
	CRESULT result = CERR_OK;

	if ((filename != NULL) && (index == -1)) {
		result = caps_applyWarpFromFile(session, filename);

		if (result != CERR_OK) {
			PRINTE("Failed to set warp effect");
		}
	} else if ((index >= CAPS_WARP_UPNOSE) && (index <= CAPS_WARP_INSECT)) {
		//TODO
	}
	
	return result;
}

CRESULT ScaladoLiveEffect::setMosaicEffect(CTSession session)
{
	CRESULT result = CERR_OK;
	int index = 0;

	result = caps_beginMosaic(session);
	if (result == CERR_OK) {
		index = (((mWidth * mHeight) / (BASE_WIDTH * BASE_HEIGHT)) >> 3) + MOSAIC_SIZE_8;  
		result = caps_setMosaic(session, (CAPS_MOSAIC_SIZE)index);
		if (result != CERR_OK) {
			PRINTE("Failed to set mosaic effect");
		}

		caps_endMosaic(session);
	}
	
	return result;
}

CRESULT ScaladoLiveEffect::setForstEffect(CTSession session)
{
	CRESULT result = CERR_OK;
	CAPS_FROSTED_LEVEL level = FROSTED_HIGH;

	result = caps_beginFrostedGlass(session);
	if (result == CERR_OK) {
		if (mWidth > BASE_WIDTH && mHeight > BASE_HEIGHT) {
			level = FROSTED_8;
		}
		
		result = caps_setFrostedGlass(session, level);

		if (result != CERR_OK) {
			PRINTE("Failed to set frost effect");
		}

		caps_endFrostedGlass(session);
	}
	
	return result;
}

CRESULT ScaladoLiveEffect::setMoonLightEffect(CTSession session)
{
	CRESULT result = CERR_OK;

	result = caps_applyMoonlight(session, 2);
	if (result != CERR_OK) {
		PRINTE("Failed to set moon light effect");
	}

	return result;
}

CRESULT ScaladoLiveEffect::setNoiseEffect(CTSession session)
{
	CRESULT result = CERR_OK;

	result = caps_beginNoise(session);
	if (result == CERR_OK) {
		result = caps_setNoise(session, NOISE_MAX);

		if (result != CERR_OK) {
			PRINTE("Failed to set noise effect");
		}

		caps_endNoise(session);
	}

	return result;
}

CRESULT ScaladoLiveEffect::setWaterColorEffect(CTSession session)
{
	CRESULT result = CERR_OK;

	result = caps_beginWatercolor(session);
	if (result == CERR_OK) {
		result = caps_setWatercolor(session, 0.5, 0.5);

		if (result != CERR_OK) {
			PRINTE("Failed to set water color effect");
		}

		caps_endWatercolor(session);
	}

	return result;
}

};
