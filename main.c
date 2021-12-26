#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "open_gl/renderer.h"
#include <assert.h>

#define WIDTH 1080.0
#define HEIGHT 1080.0


int main(void)
{
    opengl_initialize(1000, 1000, 10, 20);
    int n = 0;
    while(opengl_window_open()) {
        n++;

        double x = 0.0001*n;
        double y = 0;
    opengl_draw_ellipse_pbc(x, y, 1.0, 0.5, M_PI/2); 
    }
    opengl_terminate();


}
