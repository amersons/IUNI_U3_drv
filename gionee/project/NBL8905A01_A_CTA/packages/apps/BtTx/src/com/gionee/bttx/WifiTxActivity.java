package com.gionee.bttx;

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


public class WifiTxActivity extends Activity implements OnClickListener {
	private final String TAG = "WifiTxActivity";
	private ProgressDialog pDialog;
	private Spinner mChannelSpinner;
	private Spinner mSignalSpinner;
	//private Spinner mRateSpinner;
	private Spinner mPowerSpinner;
	private Button mGoBtn;
	private Button mStopBtn;
	private Button mBtTestModeBtn;
	private ArrayAdapter<String> mChannelAdatper;
	//private ArrayAdapter<String> mRateAdatper;
	private ArrayAdapter<String> mPowerAdatper;
	private ArrayAdapter<String> mSignalAdapter;
	private int mPowerIndex = 0;
	private int mSignalIndex = 0;
	private int mChannelIndex = 0;
	//private int mRateIndex = 0;
	//option id
	private int OPT_ID_SIGNAL_MODE = 0;
	private int OPT_ID_FREQ = 1;
	private int OPT_ID_RATE = 2;
	private int OPT_ID_POWER = 3;
	//stop wifi tx index
	private int OFF = 2;

	String[] mPower = { 
		"tgtpwr", 
		/*"txpwr 1",
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
	    	"txpwr 14",*/
		};
	
	String[] mSignal = { 
		"CW Signal",
//		"TX Continuous Signal 1M(GFSK)",
//		"TX Continuous Signal 3M(8DPSK)",
		"1DH1",
		"2DH1",
		"3DH1",
		"1DH2",
		"2DH2",
		"3DH2",
		"1DH3",
		"2DH3",
		"3DH3",
		};
	
	String[] mChannel = { 
//2.4GHz frequency serials			
		"Channel 0 [2402MHz]", 
		"Channel 39 [2441MHz]", 
		"Channel 78 [2480MHz]",
		};
	
	/*String[] mRate = { 
			"1M(GFSK)", 
			"", 		
			};*/
		
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.wifi_tx_6620);
		
		
		mChannelSpinner = (Spinner) findViewById(R.id.WiFi_Channel_Spinner);
		mSignalSpinner = (Spinner) findViewById(R.id.WiFi_Signal_Spinner);
		//mRateSpinner = (Spinner) findViewById(R.id.WiFi_Rate_Spinner);
		mPowerSpinner = (Spinner) findViewById(R.id.WiFi_Power_Spinner);
		mGoBtn = (Button) findViewById(R.id.WiFi_Go);
		mStopBtn = (Button) findViewById(R.id.WiFi_Stop);
		mBtTestModeBtn = (Button) findViewById(R.id.Bt_Test_Mode);
		
		
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
		if(null != mBtTestModeBtn)
		{
			mBtTestModeBtn.setOnClickListener(this);
		}
		else
		{
			Log.e(TAG, "findViewById(R.id.mBtTestModeBtn) failed");
		}
		
		
		
		mChannelAdatper = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item);
		mChannelAdatper.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
		for (int i = 0; i < mChannel.length; i++) {
			mChannelAdatper.add(mChannel[i]);
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
		/*mRateAdatper = new ArrayAdapter<String>(this,android.R.layout.simple_spinner_item);
		mRateAdatper.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
		for (int i = 0; i < mRate.length; i++) {
			mRateAdatper.add(mRate[i]);
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
		}*/
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
			try {
					EMWifi.ft_test_init();
					EMWifi.bt_dev_open();
			} catch (Exception e) {
				Log.e(TAG,"InitNetworkTask.doInBackground()");
			}
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
		case R.id.Bt_Test_Mode:
			onClickBtnBtTestMode();
			break;
		default:
			break;
		}
	}

	protected void onDestroy() {
		super.onDestroy();
		Log.e(TAG,"onDestroy");
		EMWifi.bt_dev_close();
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
		Log.d(TAG, "channelIdx "+mChannelIndex+ " power "+ mPowerIndex+" signal "+mSignalIndex);
	}
	private void onClickBtnBtTestMode() {
		EMWifi.bt_test_mode();
		setViewEnabled(false);
	}
	private void onClickBtnTxGo() {
		EMWifi.bt_tx_set_parm(OPT_ID_SIGNAL_MODE,mSignalIndex);
		EMWifi.bt_tx_set_parm(OPT_ID_FREQ,mChannelIndex);
		//EMWifi.wifi_tx_set_parm(OPT_ID_RATE,mRateIndex);
		EMWifi.bt_tx_set_parm(OPT_ID_POWER,mPowerIndex);
		EMWifi.bt_tx_test();
		setViewEnabled(false);
	}
	private void setViewEnabled(boolean state)
	{
		mChannelSpinner.setEnabled(state);
		mSignalSpinner.setEnabled(state);
		//mRateSpinner.setEnabled(state);
		mPowerSpinner.setEnabled(state);
		mGoBtn.setEnabled(state);
		mBtTestModeBtn.setEnabled(state);
		mStopBtn.setEnabled(!state);
	}
	private void onClickBtnTxStop() {
			EMWifi.bt_tx_test_stop();
			setViewEnabled(true);
	}
}
