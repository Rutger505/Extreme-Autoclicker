#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/uinput.h>
#include <libevdev-1.0/libevdev/libevdev.h>
#include <libevdev-1.0/libevdev/libevdev-uinput.h>
#include <time.h>
#include <gtk/gtk.h>

static void
print_hello(GtkWidget *widget,
            gpointer data) {
    g_print("Hello World\n");
}

static void activate(GtkApplication *app,
                     gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;

    /* create a new window, and set its title */
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Window");

    /* Here we construct the container that is going pack our buttons */
    grid = gtk_grid_new();

    /* Pack the container in the window */
    gtk_window_set_child(GTK_WINDOW(window), grid);

    button = gtk_button_new_with_label("Button 1");
    g_signal_connect(button, "clicked", G_CALLBACK (print_hello), NULL);

    /* Place the first button in the grid cell (0, 0), and make it fill
     * just 1 cell horizontally and vertically (ie no spanning)
     */
    gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);

    button = gtk_button_new_with_label("Button 2");
    g_signal_connect(button, "clicked", G_CALLBACK (print_hello), NULL);

    /* Place the second button in the grid cell (1, 0), and make it fill
     * just 1 cell horizontally and vertically (ie no spanning)
     */
    gtk_grid_attach(GTK_GRID(grid), button, 1, 0, 1, 1);

    button = gtk_button_new_with_label("Quit");
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (gtk_window_destroy), window);

    /* Place the Quit button in the grid cell (0, 1), and make it
     * span 2 columns.
     */
    gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 2, 1);

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc,
         char **argv) {
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


    for (int i = 0; i < 1; i++) {
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
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}

