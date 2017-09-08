package com.gionee.bttx;

public class EMWifi {
	//wangzhen
	public static native void ft_test_init();
	public static native void ft_test_exit();
	public static native void wifi_tx_set_parm(int id, int index);
	public static native void wifi_tx_test();
	public static native void wifi_tx_test_stop();
	public static native void wifi_drv_load();
	public static native void wifi_drv_unload();
	public static native void wifi_connect_ap();
	public static native void bt_dev_open();
	public static native void bt_dev_close();
	public static native void bt_tx_set_parm(int id, int index);
	public static native void bt_tx_test();
	public static native void bt_tx_test_stop();
	public static native void bt_test_mode();
    	//end

	static {
		 System.loadLibrary("factorytest_bt_jni");
	}

}
