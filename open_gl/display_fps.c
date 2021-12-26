#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "display_fps.h"

const double convert_to_second = 1/((double) 1000000000);

timer* initialize_timer() {
    timer* timerr = malloc(sizeof(timer));
    timerr->starting_clock_cyle = clock();
    timerr->starting_time = time(NULL);
    clock_gettime(CLOCK_MONOTONIC, &(timerr->starting_timespec));
    return timerr;
}

int64_t timespecDiff(struct timespec *timeA_p, struct timespec *timeB_p)
{
  return ((timeA_p->tv_sec * 1000000000) + timeA_p->tv_nsec) -
           ((timeB_p->tv_sec * 1000000000) + timeB_p->tv_nsec);
}

double get_seconds_elapsed(timer* timer) {

    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    int64_t nanosecs_elapsed = timespecDiff(&now, &(timer->starting_timespec));
    double seconds = nanosecs_elapsed *convert_to_second;
    return seconds;
}

void display_fps_information(timer* timer, int frames) {
    static int amount_of_displays = 0;
    double display_fps_every = 1;


    /* long time_elapsed = time(NULL) - timer->starting_time; */
    double time_elapsed = get_seconds_elapsed(timer);
    if(time_elapsed > display_fps_every * (amount_of_displays + 1))
    {
        double cpu_time_used =  ((double)(clock() - timer->starting_clock_cyle ))/ CLOCKS_PER_SEC;
        double fps = (double)frames / time_elapsed;
        printf("cputime %f  ---  realtime %f --- frames: %d --- fps: %f \n", cpu_time_used, time_elapsed , frames, fps);
        amount_of_displays ++;
    }
}


