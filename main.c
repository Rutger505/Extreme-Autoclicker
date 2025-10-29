#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/uinput.h>
#include <fcntl.h>
#include <libevdev-1.0/libevdev/libevdev.h>
#include <libevdev-1.0/libevdev/libevdev-uinput.h>
#include <errno.h>

int main(void)
{
    struct libevdev *dev = NULL;

    int fd = open("/dev/input/event6", O_RDONLY | O_NONBLOCK);
    int rc = libevdev_new_from_fd(fd, &dev);
    if (rc < 0) {
        fprintf(stderr, "Failed to init libevdev (%s)\n", strerror(-rc));
        exit(1);
    }

    printf("Input device name: \"%s\"\n", libevdev_get_name(dev));

    printf("Input device ID: bus %#x vendor %#x product %#x\n",
           libevdev_get_id_bustype(dev),
           libevdev_get_id_vendor(dev),
           libevdev_get_id_product(dev));
    printf("Evdev version: %x\n", libevdev_get_driver_version(dev));
    printf("Input device name: \"%s\"\n", libevdev_get_name(dev));
    printf("Phys location: %s\n", libevdev_get_phys(dev));
    printf("Uniq identifier: %s\n", libevdev_get_uniq(dev));


    if (!libevdev_has_event_type(dev, EV_REL) ||
        !libevdev_has_event_code(dev, EV_KEY, BTN_LEFT)) {
        printf("This device does not look like a mouse\n");
        exit(1);
    }

    for (int i = 0; i < 10; i++) {
        struct input_event ev;
        rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);
        if (rc != 0) {
            printf("Error getting event %d (%s)", rc, strerror(rc));
            continue;
        }

        printf("Event: %s %s %d\n",
               libevdev_event_type_get_name(ev.type),
               libevdev_event_code_get_name(ev.type, ev.code),
               ev.value);
    }

    return 0;
}
