
struct VLCDC {
	struct TCP_CONN tconn;
	struct UDP_CONN uconn;
};


enum client_command_type {
	cc_INIT,
	cc_FILL,
	cc_SPIXEL,
	cc_FRAME,
	cc_READ,
};


struct VC_COLOR {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	// int red;
	// int green;
	// int blue;
};


struct VC_INIT_COMM {
	struct VC_COLOR color;
	int width, height;
	int mode;
};


struct VC_FILL_COMM {
	struct VC_COLOR color;
};


struct VC_SPIXEL_COMM {
	int x, y;
	int width, height;
	struct VC_COLOR color;
};


struct VC_FRAME_COMM {
	int x, y;
	int width, height;
	// struct VC_COLOR colors[500];
	// struct VC_COLOR *colors;
	// struct VC_COLOR **colors;
	char *buffer;
};




struct VC_READ_OBJ {
	int x, y;
	struct VC_COLOR color;
};

struct VC_READ_COMM {
	int ecode;
	int len;
	struct VC_READ_OBJ *objs;
	// int x, y;
	// struct VC_COLOR color;
};



struct VC_KEY_COMM {
	unsigned int key;
	int is_down;
	int is_shift;
	int is_ctrl;
	unsigned int mouse_key;
	int mouse_x;
	int mouse_y;
};

