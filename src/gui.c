#include "../include/gui.h"

#include <gtk/gtk.h>

GtkApplication *app;

void print_hello() {
    printf("Hello World!\n");
}

static void activate(GtkApplication *app,
                     gpointer user_data) {
    GtkWidget *window;
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Extreme-Autoclicker");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
    gtk_window_present(GTK_WINDOW(window));
}

void gui_init() {
    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);
}

void gui_attach_update_settings_callback(UpdateSettingsCallback callback) {
    printf("Not implemented!!\n");
}

int gui_start(int argc,
              char **argv) {
    return g_application_run(G_APPLICATION(app), argc, argv);
}

void gui_destroy() {
    g_object_unref(app);
}
