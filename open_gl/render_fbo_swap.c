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
#include "shapes/basic.h"
#include "load_shaders.h"
#include "swapper.h"

#include "render_fbo_swap.h"

static GLint shader_program;

static GLFWwindow* window;
static timer* timerr;
static GLfloat vertices[]= {
        -1.0f, 1.0f, 0.0f, 0.0f, // Top left
        1.0f, 1.0f, 1.0f, 0.0f, // Top right
        1.0f, -1.0f,  1.0f, 1.0f,// bottom right
        -1.0f, -1.0f, 0.0f, 1.0f, // bottom left
    };
static GLuint elements[]= {
        0, 1, 2,
        2, 3, 0
    };
static int frames = 0;
static cpu_data s_draw_rectangle = {
        .N_vertices = 16,
        .N_elements = 6,
        .sizeof_vertices = 16 * sizeof(GLfloat),
        .sizeof_elements = 6 * sizeof(GLuint),
    };



void opengl_initialize(int width, int height, char* vertex_file_name, char* fragment_file_name) {
    window = create_window(width, height);
    timerr = initialize_timer();

    s_draw_rectangle.vertices = vertices;   
    s_draw_rectangle.elements = elements;
    
    gpu_buffers* buffers = initialize_gpu_buffers(s_draw_rectangle);
    (void) buffers; // this avoids compile warning.

    shader_program = load_shaders_into_shader_program(vertex_file_name, fragment_file_name);

    //position attribute
    GLint pos_attrib = glGetAttribLocation(shader_program, "position");
    glVertexAttribPointer(pos_attrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(pos_attrib);

    //texture attribute
    GLint tex_pos_attrib = glGetAttribLocation(shader_program, "tex_position");
    glVertexAttribPointer(tex_pos_attrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(tex_pos_attrib);

    //swapper
    /* create_swapper(width, height); */

}

static void opengl_start_frame() {
    glClear(GL_COLOR_BUFFER_BIT);
}

static void opengl_end_frame() {
    glDrawElements(GL_TRIANGLES, s_draw_rectangle.N_elements, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    frames++;
    display_fps_information(timerr, frames);

    /* Poll for and process events */
    glfwPollEvents();
}

void opengl_terminate() {
    glfwTerminate();
}

int opengl_window_open() {
    
    opengl_end_frame();
    opengl_start_frame();
    return (!glfwWindowShouldClose(window));
}



