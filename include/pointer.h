#pragma once

#include <stdint.h>


typedef struct {
    uint32_t pressDuration;
    uint32_t delay;
    uint32_t maxClicks;
} PointerSettings;

void pointer_init();

void pointer_set_settings(PointerSettings settings);

void pointer_start();

void pointer_stop();

void pointer_destroy();
