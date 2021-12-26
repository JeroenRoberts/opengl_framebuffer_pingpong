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

GLint initialize_shader(char* vertex_file_name, char* fragment_file_name) {
    shader_files s;
    s.frag = malloc(5000);
    s.vert = malloc(5000);
    /* sprintf(s.vert, "%s", "/home/jeroen/December-2021/open_gl_fbo/open_gl/shaders/display_texture.vert"); */
    /* sprintf(s.frag, "%s", "/home/jeroen/December-2021/open_gl_fbo/open_gl/shaders/display_texture.frag"); */
    sprintf(s.vert, "%s", vertex_file_name);
    sprintf(s.frag, "%s", fragment_file_name);

    GLint shader_program_update;
    shader_program_update = load_shaders_into_shader_program(s);
    set_attributes(shader_program_update);

    return shader_program_update;
}

int main(void)
{
    /* char* vertex_file_name = "/home/jeroen/December-2021/open_gl_fbo/open_gl/basic_shaders/simple.vert"; */
    /* char* fragment_file_name = "/home/jeroen/December-2021/open_gl_fbo/open_gl/basic_shaders/simple.frag"; */
    int pixel_width = 1000;
    int pixel_height = 1000;
    opengl_initialize(pixel_width, pixel_width);
    GLint shader_program_update = initialize_shader(
            "/home/jeroen/December-2021/open_gl_fbo/open_gl/shaders/display_texture.vert",
            "/home/jeroen/December-2021/open_gl_fbo/open_gl/shaders/display_texture.frag"
    );

    /* GLint shader_program_screen = initialize_shader( */
    /*         "/home/jeroen/December-2021/open_gl_fbo/open_gl/shaders/simple.vert", */
    /*         "/home/jeroen/December-2021/open_gl_fbo/open_gl/shaders/simple.frag" */
    /* ); */

    /* static GLint shader_program_screen; */
    /* shader_program_screen = load_shaders_into_shader_program(s); */
    /* set_attributes(shader_program_update); */
    /* shader_program_screen = load_shaders_into_shader_program(s); */

    create_swapper(pixel_width, pixel_height);
    //uniforms
    initialize_uniforms(shader_program_update);
    int frames = 0;
    while(opengl_window_open()) {
        update_uniforms(frames);

        perform_swap(shader_program_update);
        glClear(GL_COLOR_BUFFER_BIT);
        draw_rectangle();

        
        glBindFramebuffer(GL_FRAMEBUFFER, 0); // 0 = screen (visual , i.e. CAN SEE)
        glClear(GL_COLOR_BUFFER_BIT);
        draw_rectangle();
        frames++;
    }
    opengl_terminate();


}
