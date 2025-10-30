#pragma once

#include "types.h"


typedef void (*UpdateSettingsCallback)(PointerSettings);

void gui_init();

int gui_start(int argc,
              char **argv);

void gui_attach_update_settings_callback(UpdateSettingsCallback callback);

void gui_destroy();
