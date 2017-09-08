struct wifi_opt
{
	const char* tx;
	const char* txfreq;
	const char* txrate;
	const char* pwr_cntl_mode;
	const char* pwr;
	const char* pck_type;
	const char* pck_length1;
	const char* pck_length2;
	const char* set_cb;
};

void ft_init();

void ft_exit();

void wifi_drv_load();

void wifi_drv_unload();

void wifi_drv_load_wcn36x0();

void wifi_drv_unload_wcn36x0();


void wifi_connect_ap();

void wifi_tx_test(struct wifi_opt wo);

void wifi_tx_test_36x0(struct wifi_opt wo);

void wifi_tx_test_36x0_stop(struct wifi_opt wo);

void bt_dev_open();

void bt_dev_close();

void bt_tx_test(struct wifi_opt wo);

void bt_tx_burst(struct wifi_opt wo);

void bt_tx_test_stop();

void bt_test_mode();

void lcd_test();

void lcd_test_stop();
