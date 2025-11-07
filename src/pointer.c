#include "../include/pointer.h"
#include <linux/uinput.h>
#include <libevdev-1.0/libevdev/libevdev.h>
#include <libevdev-1.0/libevdev/libevdev-uinput.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


struct libevdev *vdev = NULL;
struct libevdev_uinput *uidev = NULL;

void pointer_init() {
    vdev = libevdev_new();
    if (!vdev) {
        fprintf(stderr, "failed to create virtual device\n");
        exit(1);
    }

    libevdev_set_name(vdev, "extreme autoclicker");
    libevdev_set_id_bustype(vdev, BUS_USB);

    libevdev_set_id_vendor(vdev, 0x1234);
    libevdev_set_id_product(vdev, 0x5678);

    libevdev_enable_event_type(vdev, EV_KEY);
    libevdev_enable_event_code(vdev, EV_KEY, BTN_LEFT, NULL);
    libevdev_enable_event_code(vdev, EV_KEY, BTN_RIGHT, NULL);
    libevdev_enable_event_code(vdev, EV_KEY, BTN_MIDDLE, NULL);

    libevdev_enable_event_type(vdev, EV_REL);
    libevdev_enable_event_code(vdev, EV_REL, REL_X, NULL);
    libevdev_enable_event_code(vdev, EV_REL, REL_Y, NULL);

    libevdev_enable_event_type(vdev, EV_SYN);

    const int rc = libevdev_uinput_create_from_device(vdev, LIBEVDEV_UINPUT_OPEN_MANAGED, &uidev);
    if (rc != 0) {
        fprintf(stderr, "failed to create uinput device (%s)\n", strerror(-rc));
        exit(1);
    }

    printf("virtual mouse device created: extreme autoclicker\n");
}

void pointer_start() {
    // todo make seperate thread for this:
    for (int i = 0; i < 100; i++) {
        printf("sending automatic left mouse click...\n");

        // press
        libevdev_uinput_write_event(uidev, EV_KEY, BTN_LEFT, 1);
        libevdev_uinput_write_event(uidev, EV_SYN, SYN_REPORT, 0);

        usleep(50000);

        // release
        libevdev_uinput_write_event(uidev, EV_KEY, BTN_LEFT, 0);
        libevdev_uinput_write_event(uidev, EV_SYN, SYN_REPORT, 0);

        usleep(500000);


        printf("  -> click sent\n");
    }
}

void pointer_stop() {
}


void pointer_destroy() {
    libevdev_uinput_destroy(uidev);
    libevdev_free(vdev);
}


