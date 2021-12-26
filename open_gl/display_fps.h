#pragma once
#include <time.h>

typedef struct{
    time_t starting_time;
    clock_t starting_clock_cyle;
    struct timespec starting_timespec;   
} timer;

void display_fps_information(timer* timer, int frames);
timer* initialize_timer();
