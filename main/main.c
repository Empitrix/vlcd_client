#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "lib/my_wifi.h"  // you might don't have this
#include "lib/wifi.h"
#include "lib/tcpconn.h"
#include "lib/udpconn.h"


#define PORT 4210
#define TRANSITION 1024

void dlay(int ms){
	vTaskDelay(ms / portTICK_PERIOD_MS);
}

void app_main(){
	
	wifi_setup(MY_WIFI_SSID, MY_WIFI_PASSWORD);
	wifi_connect();
	printf("WIFI Connected!\n");

	struct TCP_CONN tconn = tcp_conn_init(PORT);
	struct UDP_CONN uconn = udp_conn_init(PORT);

	for(;;){
		char init[9] = {'\x01', '\xFF', '\xFF', '\xFF', '\x01', '\xF4', '\x01', '\xF4', '\x01'};
		tcp_conn_send(&tconn, init, 9);
		// printf("INIT SENT\n");
		dlay(500);

		char fill[4] = {'\x04', '\x00', '\xFF', '\x00'};
		tcp_conn_send(&tconn, fill, 4);
		// printf("FILL SENT\n");
		dlay(500);

		char rcbf[1024] = {'\x05'};
		tcp_conn_send(&tconn, rcbf, 1);
		memset(rcbf, 0, 1024);
		tcp_conn_recv(&tconn, rcbf, 1024);
		printf("RCBF: %s\n", rcbf);

		char udpbuff[9];
		memset(udpbuff, 0, 9);
		if(udp_conn_recv(&uconn, udpbuff, 9) > 0){
			printf(">");
			for(int i = 0; i < 9; ++i)
				if(udpbuff[i] != 0)
					printf("-");
				else
					printf(" ");
			printf("<\n");
		}

		
	}

}

