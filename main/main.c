#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


void dlay(int ms){
	vTaskDelay(ms / portTICK_PERIOD_MS);
}


void app_main(){
	for(;;){
	}
}

