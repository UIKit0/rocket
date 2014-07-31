#ifndef SYNC_DEVICE_H
#define SYNC_DEVICE_H

#include "data.h"
#include "sync.h"

struct sync_device {
	char *base;
	struct sync_data data;

#ifndef SYNC_PLAYER
	int row;
	SOCKET sock;
#endif
	struct sync_io_cb io_cb;
};

#endif /* SYNC_DEVICE_H */
