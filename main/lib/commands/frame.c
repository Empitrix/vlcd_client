#include "../tcpconn.h"
#include "../udpconn.h"
#include "../structs.h"
#include "../utils.h"

#include <stdio.h>

/* _vc_frame_comm: Setup a frame */
int _vc_frame_comm(struct VLCDC *vlcdc, struct VC_FRAME_COMM comm){

	int dsiz = 0;
	dsiz = (comm.width * comm.height);  // data size

	int bufsiz = 9 + dsiz;
	char frame[bufsiz];

	frame[0] = '\x02';            // index
	frame[1] = first_h(comm.x);   // X (a)
	frame[2] = second_h(comm.x);  // X (b)

	frame[3] = first_h(comm.y);   // Y (a)
	frame[4] = second_h(comm.y);  // Y (b)

	frame[5] = first_h(comm.width);   // Width (a)
	frame[6] = second_h(comm.width);  // Width (b)

	frame[7] = first_h(comm.height);   // Height (a)
	frame[8] = second_h(comm.height);  // Height (b)

	int rem = 9;  // remaining of buffer (ended at idx:8)

	for(int i = 0, kidx = 0; i < dsiz; ++i){
		frame[rem++] = ghex(comm.buffer[kidx++]);
	}

	// printf("BUFSIZ: %d\n", bufsiz);
	free(comm.buffer);
	return tcp_conn_send(&vlcdc->tconn, frame, bufsiz);
}

