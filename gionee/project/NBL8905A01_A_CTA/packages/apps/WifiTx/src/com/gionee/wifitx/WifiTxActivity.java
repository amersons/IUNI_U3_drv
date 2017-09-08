package com.gionee.wifitx;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.text.TextUtils;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;
import android.os.AsyncTask;
import android.app.ProgressDialog;

import com.gionee.wifi.R;


public class WifiTxActivity extends Activity implements OnClickListener {
	private final String TAG = "WifiTxActivity";
	private ProgressDialog pDialog;
	private Spinner mChannelSpinner;
	private Spinner mSignalSpinner;
	private Spinner mRateSpinner;
	private Spinner mPowerSpinner;
	private Spinner mPowerModeSpinner;
	private Spinner mModeSpinner;
	private Button mGoBtn;
	private Button mStopBtn;
	private ArrayAdapter<String> mChannelAdatper;
	private ArrayAdapter<String> mRateAdatper;
	private ArrayAdapter<String> mPowerAdatper;
	private ArrayAdapter<String> mPowerModeAdatper;
	private ArrayAdapter<String> mSignalAdapter;
	private ArrayAdapter<String> mModeAdatper;
	private int mPowerIndex = 0;
	private int mPowerModeIndex = 0;
	private int mSignalIndex = 0;
	private int mChannelIndex = 0;
	private int mRateIndex = 0;
	private int mModeIndex = 0;
	//option id
	private int OPT_ID_SIGNAL_MODE = 0;
	private int OPT_ID_FREQ = 1;
	private int OPT_ID_RATE = 2;
	private int OPT_ID_POWER = 3;
	private int OPT_ID_POWER_MODE = 5;
	private int OPT_ID_MODE = 4;
	//stop wifi tx index
	private int OFF = 2;
	/*
	String[] mPower = { 
		"tgtpwr", 
		"txpwr 1",
		"txpwr 2",
		"txpwr 3",
	    	"txpwr 4",
	    	"txpwr 5",
	    	"txpwr 6",
	    	"txpwr 7",
	    	"txpwr 8",
	    	"txpwr 9",
	    	"txpwr 10",
	    	"txpwr 11",
	    	"txpwr 12",
	    	"txpwr 13",
	    	"txpwr 14",
		};*/
	String[] mPower = { 
		"9",
		"10",
		"11",
		"12",
		"13",
		"14",
		"15",
		"16",
		"17",
		"18",
		"19",
		"20",
		"21",
		"22",
		"23",
		"24",
		};

	String[] mPowerMode = {
		"0",
		"1",
		"2",
		};
	
	String[] mSignal = { 
		"CW Signal",
		"TX Continuous Signal",
		};
	
/*	String[] mChannel = { 
//2.4GHz frequency serials			
		"Channel 1 [2412MHz]", 
		"Channel 2 [2417MHz]", 
		"Channel 3 [2422MHz]",
		"Channel 4 [2417MHz]", 
		"Channel 5 [2432MHz]", 
		"Channel 6 [2437MHz]", 
		"Channel 7 [2442MHz]", 
		"Channel 8 [2447MHz]",
		"Channel 9 [2452MHz]", 
		"Channel 10 [2457MHz]", 
		"Channel 11 [2462MHz]", 
		"Channel 12 [2467MHz]",
		"Channel 13 [2472MHz]", 
		//"Channel 14 [2484MHz]", 
		};*/
	String[] mChannel_bgn_ht20 = { 		
		"Channel 1 [2412MHz]", 
		"Channel 6 [2437MHz]", 
		"Channel 11 [2462MHz]", 
		"Channel 13 [2472MHz]", 
		"Channel 149 [5745MHz]", 
		"Channel 165 [5825MHz]",
		};
	String[] mChannel_n_ht40 = { 		
		"Channel 3 [2422MHz]",
		"Channel 6 [2437MHz]",
		"Channel 9 [2452MHz]",
		"Channel 11 [2462MHz]", 
		"Channel 151 [5755MHz]",
		"Channel 159 [5795MHz]", 
		"Channel 163 [5815MHz]", 
		};
	String[] mChannel_ac_ht20 = { 		
		"Channel 36 [5180MHz]", 
		"Channel 64 [5320MHz]", 
		};
	String[] mChannel_ac_ht40 = { 		
		"Channel 38 [5190MHz]", 
		"Channel 62 [5310MHz]", 
		};
	String[] mChannel_ac_ht80 = { 		
		"Channel 42 [5210MHz]", 
		"Channel 58 [5290MHz]", 
		"Channel 155 [5775MHz]", 
		};
	String[] mChannel_a_ht20 = { 		
		"Channel 149 [5745MHz]", 
		"Channel 165 [5825MHz]",
		};
	String[] mMode = {
		"11b",
		"11g",
		"11n_ht20",
		"11n_ht40",
		"11ac_ht20",
		"11ac_ht40",
		"11ac_ht80",
		"11a",
		};
	/*
	String[] mRate = { 
			"1M", 
			"2M", 
			"5.5M", 
			"11M", 
			"6M",
			"9M", 
			"12M", 
			"18M", 
			"24M", 
			"36M", 
			"48M", 
			"54M",
			"MCS0",
			"MCS1",
			"MCS2",
			"MCS3",
			"MCS4",
			"MCS5",
			"MCS6",
			"MCS7",			
			};*/
	String[] mRate_b = { 
			"1M", 	
			"5.5M",
			"11M",
			};
	String[] mRate_g = { 
			"6M", 	
			"24M",
			"54M",
			};
	String[] mRate_n_ht20 = { 
			"MCS0 6.5M", 	
			"MCS4 39M",
			"MCS7 65M",
			};
	String[] mRate_n_ht40 = { 
			"MCS0 13.5M", 	
			"MCS4 81M",
			"MCS7 135M",
			};
	String[] mRate_ac_ht20 = { 
			"MCS0 6.5M", 	
			"MCS5 39M",
			"MCS8 78M",
			};
	String[] mRate_ac_ht40 = { 
			"MCS0 13.5M", 	
			"MCS5 108M",
			"MCS9 180M",
			};
	String[] mRate_ac_ht80 = { 
			"MCS0 29.3M", 	
			"MCS5 234M",
			"MCS9 390M",
			};
	String[] mRate_a_ht20 = { 
			"6M", 	
			"24M",
			"54M",
			};			
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.wifi_tx_6620);
		
		//EMWifi.ft_test_init();
		//EMWifi.wifi_drv_load();
		mChannelSpinner = (Spinner) findViewById(R.id.WiFi_Channel_Spinner);
		mSignalSpinner = (Spinner) findViewById(R.id.WiFi_Signal_Spinner);
		mRateSpinner = (Spinner) findViewById(R.id.WiFi_Rate_Spinner);
		mPowerSpinner = (Spinner) findViewById(R.id.WiFi_Power_Spinner);
		mPowerModeSpinner = (Spinner) findViewById(R.id.WiFi_Power_Mode_Spinner);
		mModeSpinner = (Spinner) findViewById(R.id.WiFi_Mode_Spinner);
		mGoBtn = (Button) findViewById(R.id.WiFi_Go);
		mStopBtn = (Button) findViewById(R.id.WiFi_Stop);
		
		
		if(null != mGoBtn)
		{
			mGoBtn.setOnClickListener(this);
		}
		else
		{
			Log.e(TAG, "findViewById(R.id.WiFi_Go) failed");
		}
		if(null != mStopBtn)
		{
			mStopBtn.setOnClickListener(this);
		}
		else
		{
			Log.e(TAG, "findViewById(R.id.mStopBtn) failed");
		}
		
		
		//mChannel = new ChannelInfo();
		//mRate = new RateInfo();
		
		
		mChannelAdatper = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item);
		mChannelAdatper.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
		for (int i = 0; i < mChannel_bgn_ht20.length; i++) {
			mChannelAdatper.add(mChannel_bgn_ht20[i]);
		}
		
		if(null != mChannelSpinner)
		{
			mChannelSpinner.setAdapter(mChannelAdatper);
			mChannelSpinner.setOnItemSelectedListener(new OnItemSelectedListener() {
				
				public void onItemSelected(AdapterView<?> arg0, View arg1,
						int arg2, long arg3) {
					mChannelIndex = arg2;
					Log.i(TAG, "The mChannelIndex is : " + mChannelIndex);
					uiUpdateTxPower();
				}
				
				public void onNothingSelected(AdapterView<?> arg0) {
				}
			});
		}
		else
		{
			Log.e(TAG, "findViewById(R.id.WiFi_Channel_Spinner) failed");
		}
		
		mModeAdatper = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item);
		mModeAdatper.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
		for (int i = 0; i < mMode.length; i++) {
			mModeAdatper.add(mMode[i]);
		}
		
		if(null != mModeSpinner)
		{
			mModeSpinner.setAdapter(mModeAdatper);
			mModeSpinner.setOnItemSelectedListener(new OnItemSelectedListener() {
				
				public void onItemSelected(AdapterView<?> arg0, View arg1,
						int arg2, long arg3) {
					mModeIndex = arg2;
					Log.i(TAG, "The mModeIndex is : " + mModeIndex);
					uiUpdateTxPower();
					switch(mModeIndex){
					case 0:
						mChannelAdatper.clear();
						for (int i = 0; i < mChannel_bgn_ht20.length; i++) {
							mChannelAdatper.add(mChannel_bgn_ht20[i]);
						}
						mRateAdatper.clear();
						for (int i = 0; i < mRate_b.length; i++) {
							mRateAdatper.add(mRate_b[i]);
						}
						break;
					case 1:
						mChannelAdatper.clear();
						for (int i = 0; i < mChannel_bgn_ht20.length; i++) {
							mChannelAdatper.add(mChannel_bgn_ht20[i]);
						}
						mRateAdatper.clear();
						for (int i = 0; i < mRate_b.length; i++) {
							mRateAdatper.add(mRate_g[i]);
						}
						break;
					case 2:
						mChannelAdatper.clear();
						for (int i = 0; i < mChannel_bgn_ht20.length; i++) {
							mChannelAdatper.add(mChannel_bgn_ht20[i]);
						}
						mRateAdatper.clear();
						for (int i = 0; i < mRate_n_ht20.length; i++) {
							mRateAdatper.add(mRate_n_ht20[i]);
						}
						break;
					case 3:				
						mChannelAdatper.clear();
						for (int i = 0; i < mChannel_n_ht40.length; i++) {
							mChannelAdatper.add(mChannel_n_ht40[i]);
						}
						mRateAdatper.clear();
						for (int i = 0; i < mRate_n_ht40.length; i++) {
							mRateAdatper.add(mRate_n_ht40[i]);
						}
						break;
					case 4:				
						mChannelAdatper.clear();
						for (int i = 0; i < mChannel_ac_ht20.length; i++) {
							mChannelAdatper.add(mChannel_ac_ht20[i]);
						}
						mRateAdatper.clear();
						for (int i = 0; i < mRate_ac_ht20.length; i++) {
							mRateAdatper.add(mRate_ac_ht20[i]);
						}
						break;
					case 5:			
						mChannelAdatper.clear();
						for (int i = 0; i < mChannel_ac_ht40.length; i++) {
							mChannelAdatper.add(mChannel_ac_ht40[i]);
						}
						mRateAdatper.clear();
						for (int i = 0; i < mRate_ac_ht40.length; i++) {
							mRateAdatper.add(mRate_ac_ht40[i]);
						}
						break;
					case 6:	
						mChannelAdatper.clear();
						for (int i = 0; i < mChannel_ac_ht80.length; i++) {
							mChannelAdatper.add(mChannel_ac_ht80[i]);
						}
						mRateAdatper.clear();
						for (int i = 0; i < mRate_ac_ht80.length; i++) {
							mRateAdatper.add(mRate_ac_ht80[i]);
						}
						break;
					case 7:	
						mChannelAdatper.clear();
						for (int i = 0; i < mChannel_a_ht20.length; i++) {
							mChannelAdatper.add(mChannel_a_ht20[i]);
						}
						mRateAdatper.clear();
						for (int i = 0; i < mRate_a_ht20.length; i++) {
							mRateAdatper.add(mRate_a_ht20[i]);
						}
						break;
					}
				}
				
				public void onNothingSelected(AdapterView<?> arg0) {
				}
			});
		}
		else
		{
			Log.e(TAG, "findViewById(R.id.WiFi_Mode_Spinner) failed");
		}
		
		mRateAdatper = new ArrayAdapter<String>(this,android.R.layout.simple_spinner_item);
		mRateAdatper.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
		for (int i = 0; i < mRate_b.length; i++) {
			mRateAdatper.add(mRate_b[i]);
		}
		if(null != mRateSpinner)
		{
			mRateSpinner.setAdapter(mRateAdatper);
			mRateSpinner.setOnItemSelectedListener(new OnItemSelectedListener() {
				
				public void onItemSelected(AdapterView<?> arg0, View arg1, int arg2, long arg3) {
					mRateIndex = arg2;
					
					//set Tx Rate
					Log.i(TAG, "The mRateIndex is : " + arg2);
					uiUpdateTxPower();
				}
				
				public void onNothingSelected(AdapterView<?> arg0) {
				}
			});
		}
		else
		{
			Log.e(TAG, "findViewById(R.id.WiFi_Rate_Spinner) failed");
		}
		mPowerAdatper = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item);
		mPowerAdatper.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
		for (int i = 0; i < mPower.length; i++) {
			mPowerAdatper.add(mPower[i]);
		}
		if(null != mPowerSpinner)
		{
			mPowerSpinner.setAdapter(mPowerAdatper);
			mPowerSpinner.setOnItemSelectedListener(new OnItemSelectedListener() {
				
				public void onItemSelected(AdapterView<?> arg0, View arg1,
						int arg2, long arg3) {
					mPowerIndex = arg2;
					Log.i(TAG, "The mPowerIndex is : " + arg2);
					uiUpdateTxPower();
				}
				
				public void onNothingSelected(AdapterView<?> arg0) {
				}
			});
		}
		else
		{
			Log.e(TAG, "findViewById(R.id.WiFi_Power_Spinner) failed");
		}
		mPowerModeAdatper = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item);
		mPowerModeAdatper.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
		for (int i = 0; i < mPowerMode.length; i++) {
			mPowerModeAdatper.add(mPowerMode[i]);
		}
		if(null != mPowerModeSpinner)
		{
			mPowerModeSpinner.setAdapter(mPowerModeAdatper);
			mPowerModeSpinner.setOnItemSelectedListener(new OnItemSelectedListener() {
				
				public void onItemSelected(AdapterView<?> arg0, View arg1,
						int arg2, long arg3) {
					mPowerModeIndex = arg2;
					Log.i(TAG, "The mPowerModeIndex is : " + arg2);
					uiUpdateTxPower();
				}
				
				public void onNothingSelected(AdapterView<?> arg0) {
				}
			});
		}
		else
		{
			Log.e(TAG, "findViewById(R.id.WiFi_Power_Mode_Spinner) failed");
		}
		//signal select seetings
		mSignalAdapter = new ArrayAdapter<String>(this,android.R.layout.simple_spinner_item);
		mSignalAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
		for (int i = 0; i < mSignal.length; i++) {
			mSignalAdapter.add(mSignal[i]);
		}
		if(null != mSignalAdapter)
		{
			mSignalSpinner.setAdapter(mSignalAdapter);
			mSignalSpinner.setOnItemSelectedListener(new OnItemSelectedListener() {
				
				public void onItemSelected(AdapterView<?> arg0, View arg1,
						int arg2, long arg3) {
					mSignalIndex = arg2;
					uiUpdateTxPower();
				}
				
				public void onNothingSelected(AdapterView<?> arg0) {
				}
			});
		}
		else
		{
			Log.e(TAG, "findViewById(R.id.WiFi_11n_Power_Spinner) failed");
		}		
		setViewEnabled(true);
		pDialog = new ProgressDialog(this);
		pDialog.setProgressStyle(ProgressDialog.STYLE_SPINNER);
		new InitNetworkTask().execute(new Void[] {});
	}
	
private class InitNetworkTask extends AsyncTask<Void, Void, Boolean> {
		@Override
		protected void onPreExecute() {
			super.onPreExecute();
			pDialog.setTitle("Initialization");
			pDialog.show();
		}

		@Override
		protected void onPostExecute(Boolean r) {
			super.onPostExecute(r);
			pDialog.dismiss();
			if (r.booleanValue() == true) {
				//test();
			} else {
				//showAlert();
			}
		}

		@Override
		protected Boolean doInBackground(Void... params) {
			/*if (isTestWifi()) {
				return true;
			}*/

			try {
					EMWifi.ft_test_init();
					EMWifi.wifi_drv_load();
			} catch (Exception e) {
				Log.e(TAG,"InitNetworkTask.doInBackground()");
			}
			//threadSleep(5000);
			return true;
		}
	};


	public void onClick(View view) {
		Log.d(TAG, "view_id = " + view.getId());

		switch (view.getId()) {
		case R.id.WiFi_Go:
			onClickBtnTxGo();
			break;

		case R.id.WiFi_Stop:
			onClickBtnTxStop();
			break;
		default:
			break;
		}
	}

	protected void onDestroy() {
		super.onDestroy();
		Log.e(TAG,"onDestroy");
		EMWifi.wifi_drv_unload();
		EMWifi.ft_test_exit();
		}
	
/*	protected void onStop() {
		super.onStop();
		if(true)return;
		if(eventHandler != null)
		{
			eventHandler.removeMessages(HANDLER_EVENT_TIMER);
			if (mbTestInPorcess)
			{
//				EMWifi.setATParam(1, 0); //chencc
				mbTestInPorcess = false;
			}
			eventHandler.getLooper().quit();
		}
		super.onStop();
		finish();
	}*/

	private void uiUpdateTxPower() {
		Log.d(TAG, "channelIdx "+mChannelIndex+" mModeIndex "+mModeIndex+" rateIdx "+mRateIndex+ " power "+ mPowerIndex+" powermode "+mPowerModeIndex+" signal "+mSignalIndex);
	}
	private void onClickBtnTxGo() {
		EMWifi.wifi_tx_set_parm(OPT_ID_MODE,mModeIndex);
		EMWifi.wifi_tx_set_parm(OPT_ID_SIGNAL_MODE,mSignalIndex);
		EMWifi.wifi_tx_set_parm(OPT_ID_FREQ,mChannelIndex);
		EMWifi.wifi_tx_set_parm(OPT_ID_RATE,mRateIndex);
		EMWifi.wifi_tx_set_parm(OPT_ID_POWER,mPowerIndex);
		EMWifi.wifi_tx_set_parm(OPT_ID_POWER_MODE,mPowerModeIndex);
		EMWifi.wifi_tx_test();
		setViewEnabled(false);
	}
	private void setViewEnabled(boolean state)
	{
		mChannelSpinner.setEnabled(state);
		mModeSpinner.setEnabled(state);
		mSignalSpinner.setEnabled(state);
		mRateSpinner.setEnabled(state);
		mPowerSpinner.setEnabled(state);
		mPowerModeSpinner.setEnabled(state);
		mGoBtn.setEnabled(state);
		mStopBtn.setEnabled(!state);
	}
	private void onClickBtnTxStop() {
			EMWifi.wifi_tx_test_stop();
			setViewEnabled(true);
	}
}
