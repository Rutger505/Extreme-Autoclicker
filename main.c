#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/uinput.h>
#include <fcntl.h>
#include <libevdev-1.0/libevdev/libevdev.h>
#include <libevdev-1.0/libevdev/libevdev-uinput.h>
#include <time.h>

int main(void) {
    struct libevdev *vdev = NULL;
    struct libevdev_uinput *uidev = NULL;


    vdev = libevdev_new();
    if (!vdev) {
        fprintf(stderr, "Failed to create virtual device\n");
        exit(1);
    }

    libevdev_set_name(vdev, "Extreme Autoclicker");
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
        fprintf(stderr, "Failed to create uinput device (%s)\n", strerror(-rc));
        exit(1);
    }

    printf("Virtual Mouse Device Created: Extreme Autoclicker\n");
    printf("Move your mouse and autoclicker will send clicks\n");
    printf("Press Ctrl+C to stop\n\n");


    for (int i = 0; i < 10000; i++) {
        printf("Sending automatic left mouse click...\n");

        // Press
        libevdev_uinput_write_event(uidev, EV_KEY, BTN_LEFT, 1);
        libevdev_uinput_write_event(uidev, EV_SYN, SYN_REPORT, 0);

        usleep(50000);

        // Release
        libevdev_uinput_write_event(uidev, EV_KEY, BTN_LEFT, 0);
        libevdev_uinput_write_event(uidev, EV_SYN, SYN_REPORT, 0);

        usleep(50000);


        printf("  -> Click sent\n");
    }

    libevdev_uinput_destroy(uidev);
    libevdev_free(vdev);
    return 0;
}

