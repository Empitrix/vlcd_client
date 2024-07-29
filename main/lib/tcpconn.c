#include <string.h>
#include <sys/param.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "nvs.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>


struct TCP_CONN {
	char *msg;
	int ecode;
	int sock;
	char addr_str[128];
	struct sockaddr_in source_addr;
};

struct TCP_CONN tcp_conn_init(int port){

	int addr_family;
	int ip_protocol;

	struct TCP_CONN tcpconn;
	tcpconn.ecode = 1;
	char msg[1000];

	struct sockaddr_in destAddr;
	destAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	destAddr.sin_family = AF_INET;
	destAddr.sin_port = htons(port);
	addr_family = AF_INET;
	ip_protocol = IPPROTO_IP;
	inet_ntoa_r(destAddr.sin_addr, tcpconn.addr_str, sizeof(tcpconn.addr_str) - 1);


	int listen_sock = socket(addr_family, SOCK_STREAM, ip_protocol);
	if (listen_sock < 0) {
		sprintf(msg, "Unable to create socket: errno %d\n", errno);
		tcpconn.msg = msg;
		return tcpconn;
	}

	int err = bind(listen_sock, (struct sockaddr *)&destAddr, sizeof(destAddr));

	if (err != 0) {
		sprintf(msg, "Socket unable to bind: errno %d\n", errno);
		tcpconn.msg = msg;
		return tcpconn;
	}

	err = listen(listen_sock, 1);
	if (err != 0) {
		sprintf(msg, "Error occured during listen: errno %d\n", errno);
		tcpconn.msg = msg;
		return tcpconn;
	}

	uint addrLen = sizeof(tcpconn.source_addr);
	tcpconn.sock = accept(listen_sock, (struct sockaddr *)&tcpconn.source_addr, &addrLen);

	if (tcpconn.sock < 0) {
		sprintf(msg, "Unable to accept connection: errno %d\n", errno);
		tcpconn.msg = msg;
		return tcpconn;
	}

	tcpconn.ecode = 0;
	return tcpconn;
}




int tcp_conn_recv(struct TCP_CONN *tcpconn, char *buffer, int siz){
	if(tcpconn->ecode != 0){
		return -1;
	}

	int len = recv(tcpconn->sock, buffer, siz - 1, 0);
	return len;
}


int tcp_conn_send(struct TCP_CONN *tcpconn, char *buffer, int siz){
	inet_ntoa_r(((struct sockaddr_in *)&tcpconn->source_addr)->sin_addr.s_addr, tcpconn->addr_str, sizeof(tcpconn->addr_str) - 1);
	return send(tcpconn->sock, buffer, siz, 0);
}

