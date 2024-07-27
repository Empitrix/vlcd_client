#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "lib/my_wifi.h"  // you might don't have this


void dlay(int ms){
	vTaskDelay(ms / portTICK_PERIOD_MS);
}


void app_main(){
	
	wifi_setup(MY_WIFI_SSID, MY_WIFI_PASSWORD);
	wifi_connect();
	printf("WIFI Connected\n");

	for(;;){
		dlay(200);
	}
}

