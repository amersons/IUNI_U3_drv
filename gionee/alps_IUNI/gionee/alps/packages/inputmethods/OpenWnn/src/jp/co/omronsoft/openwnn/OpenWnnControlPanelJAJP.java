/*
 * Copyright (C) 2008-2012  OMRON SOFTWARE Co., Ltd.
 * Copyright (c) 2013, The Linux Foundation. All rights reserved.
 *
 * Not a Contribution. Apache license notifications and license are retained
 * for attribution purposes only.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package jp.co.omronsoft.openwnn;

import android.os.Bundle;
import android.preference.PreferenceActivity;
import android.preference.PreferenceScreen;

/**
 * The control panel preference class for Japanese IME.
 *
 * @author Copyright (C) 2009 OMRON SOFTWARE CO., LTD.  All Rights Reserved.
 */
public class OpenWnnControlPanelJAJP extends PreferenceActivity {

    private static final String KEY_DICTIONARY_JA = "user_dictionary_edit_words_ja";
    private static final String KEY_DICTIONARY_EN = "user_dictionary_edit_words_en";
    private PreferenceScreen mJpUserDictPref;
    private PreferenceScreen mEnUserDictPref;

    /** @see android.preference.PreferenceActivity#onCreate */
    @Override public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (OpenWnnJAJP.getInstance() == null) {
            new OpenWnnJAJP(this);
        }

        addPreferencesFromResource(R.xml.openwnn_pref_ja);

        mJpUserDictPref = (PreferenceScreen) findPreference(KEY_DICTIONARY_JA);
        mEnUserDictPref = (PreferenceScreen) findPreference(KEY_DICTIONARY_EN);
    }

    @Override
    protected void onResume() {
        super.onResume();
        updateUserDictEnableState();
    }

    private void updateUserDictEnableState() {
        if (null != mJpUserDictPref) {
            mJpUserDictPref.setEnabled(isUserDictEnable());
        }
        if (null != mEnUserDictPref) {
            mEnUserDictPref.setEnabled(isUserDictEnable());
        }
    }
    /**
     * Check whether the user dictionary is available. When current IME isn't
     * Japanese, OpenWnn.getCurrentIme() returns null. And under this condition,
     * user dictionary isn't available because mConverterJAJP/mConverterEN will
     * be null.
     *
     * @return true if user dictionary is available.
     */
    private boolean isUserDictEnable() {
        return null != OpenWnn.getCurrentIme();
    }
}
