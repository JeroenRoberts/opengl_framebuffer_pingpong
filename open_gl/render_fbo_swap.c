#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "create_window_using_glfw.h"
#include "display_fps.h"
#include "initialize_gpu_buffers.h"
#include "upload_vertices.h"
#include "load_shaders.h"
#include "swapper.h"
#include "SOIL/SOIL.h"

#include "render_fbo_swap.h"
#include "upload_vertices.h"

static GLint shader_program_update;
static GLint shader_program_screen;

static GLFWwindow* window;
static timer* timerr;
static int frames = 0;
static GLint uniform_step;

static void initialize_uniforms(){

    uniform_step = glGetUniformLocation(shader_program_update, "step");
}


void opengl_initialize(int width, int height, shader_files s) {
    window = create_window(width, height);
    timerr = initialize_timer();

    
    gpu_buffers* buffers = initialize_gpu_buffers();
    (void) buffers; // this avoids compile warning.
    upload_vertices_rectangle();

    shader_program_update = load_shaders_into_shader_program(s);
    /* shader_program_screen = load_shaders_into_shader_program(s); */

    //position attribute
    GLint pos_attrib = glGetAttribLocation(shader_program_update, "position");
    glVertexAttribPointer(pos_attrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(pos_attrib);

    //texture attribute
    GLint tex_pos_attrib = glGetAttribLocation(shader_program_update, "tex_position");
    glVertexAttribPointer(tex_pos_attrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(tex_pos_attrib);

    create_swapper(width, height);
    //uniforms
    initialize_uniforms();

}
static void update_uniforms() {
    glUniform1i(uniform_step, frames);
}

void opengl_terminate() {
    glfwTerminate();
}

int opengl_window_open() {
    update_uniforms();

    perform_swap(shader_program_update);
    glClear(GL_COLOR_BUFFER_BIT);
    draw_rectangle();

    
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // 0 = screen (visual , i.e. CAN SEE)
    glClear(GL_COLOR_BUFFER_BIT);
    draw_rectangle();

    glfwSwapBuffers(window);
    frames++;
    display_fps_information(timerr, frames);

    /* Poll for and process events */
    glfwPollEvents();

    return (!glfwWindowShouldClose(window));
}



