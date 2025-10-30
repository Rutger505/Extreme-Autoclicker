#include <stdio.h>
#include <gtk/gtk.h>
#include "../include/types.h"
#include "../include/pointer.h"
#include "../include/gui.h"

static void print_settings(PointerSettings settings) {
    g_print("Updated settings\n");
}


int main(int argc,
         char **argv) {
    pointer_init();

    pointer_start();

    gui_init();

    gui_attach_update_settings_callback(print_settings);

    const int status = gui_start(argc, argv);

    pointer_destroy();
    gui_destroy();

    return status;
}

