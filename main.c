#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "open_gl/render_fbo_swap.h"
#include <assert.h>


int main(void)
{
    /* char* vertex_file_name = "/home/jeroen/December-2021/open_gl_fbo/open_gl/basic_shaders/simple.vert"; */
    /* char* fragment_file_name = "/home/jeroen/December-2021/open_gl_fbo/open_gl/basic_shaders/simple.frag"; */
    shader_files s;
    s.frag = malloc(5000);
    s.vert = malloc(5000);
    sprintf(s.vert, "%s", "/home/jeroen/December-2021/open_gl_fbo/open_gl/shaders/display_texture.vert");
    sprintf(s.frag, "%s", "/home/jeroen/December-2021/open_gl_fbo/open_gl/shaders/display_texture.frag");
    opengl_initialize(1000, 1000, s);
    int n = 0;
    while(opengl_window_open()) {
        n++;
        
    }
    opengl_terminate();


}
