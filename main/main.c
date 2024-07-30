#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "./vlcdc.c"
#include "lib/utils.h"
#include "lib/commands.h"

#define PORT 4210
#define TRANSITION 1024

void app_main(){

	struct VLCDC vlcdc = vlcdc_init((char *)MY_WIFI_SSID, (char *)MY_WIFI_PASSWORD, PORT);

	while(1){

		printf("Init...\n");  // initialize
		struct VC_INIT_COMM _vic;
		_vic.width = 400;
		_vic.height = 400;
		_vic.mode = 1;
		_vic.color.red = 255;
		_vic.color.green = 255;
		_vic.color.blue = 0;
		vlcdc_screen_init(&vlcdc, _vic);
		dlay(500);



		printf("Fill...\n");  // fill
		struct VC_FILL_COMM _fill;
		_fill.color.red = 255;
		_fill.color.green = 0;
		_fill.color.blue = 0;
		vlcdc_screen_fill(&vlcdc, _fill);
		dlay(500);


		printf("SPIXEL...\n");  // fill
		struct VC_SPIXEL_COMM _spixel;
		_spixel.x = 100;
		_spixel.y = 100;
		_spixel.color.red = 0;
		_spixel.color.green = 0;
		_spixel.color.blue = 255;
		vlcdc_screen_spixel(&vlcdc, _spixel);
		dlay(500);



		vlcdc_get_key(vlcdc);  // read given keys
		dlay(500);
	}

	// wifi_setup(MY_WIFI_SSID, MY_WIFI_PASSWORD);
	// wifi_connect();
	// printf("WIFI Connected!\n");

	// struct TCP_CONN tconn = tcp_conn_init(PORT);
	// struct UDP_CONN uconn = udp_conn_init(PORT);

	// for(;;){
	// 	char init[9] = {'\x01', '\xFF', '\xFF', '\xFF', '\x01', '\xF4', '\x01', '\xF4', '\x01'};
	// 	tcp_conn_send(&tconn, init, 9);
	// 	// printf("INIT SENT\n");
	// 	dlay(500);

	// 	char fill[4] = {'\x04', '\x00', '\xFF', '\x00'};
	// 	tcp_conn_send(&tconn, fill, 4);
	// 	// printf("FILL SENT\n");
	// 	dlay(500);

	// 	char rcbf[1024] = {'\x05'};
	// 	tcp_conn_send(&tconn, rcbf, 1);
	// 	memset(rcbf, 0, 1024);
	// 	tcp_conn_recv(&tconn, rcbf, 1024);
	// 	printf("RCBF: %s\n", rcbf);

	// 	char udpbuff[9];
	// 	memset(udpbuff, 0, 9);
	// 	if(udp_conn_recv(&uconn, udpbuff, 9) > 0){
	// 		printf(">");
	// 		for(int i = 0; i < 9; ++i)
	// 			if(udpbuff[i] != 0)
	// 				printf("-");
	// 			else
	// 				printf(" ");
	// 		printf("<\n");
	// 	}

	// 	
	// }

}

