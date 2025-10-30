#include "../include/gui.h"

#include <gtk/gtk.h>

GtkApplication *app;

void print_hello() {
    printf("Hello World!\n");
}

static void activate(GtkApplication *app,
                     gpointer user_data) {
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "builder.ui", NULL);

    /* Connect signal handlers to the constructed widgets. */
    GObject *window = gtk_builder_get_object(builder, "window");
    gtk_window_set_application(GTK_WINDOW(window), app);

    GObject *button = gtk_builder_get_object(builder, "button1");
    g_signal_connect(button, "clicked", G_CALLBACK (print_hello), NULL);

    button = gtk_builder_get_object(builder, "button2");
    g_signal_connect(button, "clicked", G_CALLBACK (print_hello), NULL);

    button = gtk_builder_get_object(builder, "quit");
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (gtk_window_destroy), window);

    gtk_widget_set_visible(GTK_WIDGET(window), TRUE);

    /* We do not need the builder any more */
    g_object_unref(builder);
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
