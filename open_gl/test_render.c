#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "renderer.h"

int main()
{
    opengl_initialize(600, 600);
    int i =0;
    while(opengl_window_open()) {
        i++;
        opengl_draw_ellipse(-0.5, 0.0, 0.3, 0.1, 0+ M_PI*i*0.01);
        opengl_draw_ellipse(0.0, 0.0, 0.3, 0.1, 0.666*M_PI + M_PI*i*0.01);
        opengl_draw_ellipse(0.5, 0.0, 0.3, 0.1, 1.333*M_PI+ M_PI*i*0.01);
    }

    opengl_terminate();
    return 0;
}
