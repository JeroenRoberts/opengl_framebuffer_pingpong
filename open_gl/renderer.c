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

#include "renderer.h"

enum consts_renderer { 
 max_N_vertices = 10000000,
 max_N_elements = 30000000
 };

static GLint shader_program;

static const GLint max_sizeof_vertices = 5 * max_N_vertices * sizeof(GLfloat);
static const GLint max_sizeof_elements = max_N_elements * sizeof(GLuint);
static GLFWwindow* window;
static timer* timerr;
static GLfloat* vertices;
static GLuint* elements;
static int frames = 0;
static cpu_data s_opengl = {
        .N_vertices = 0,
        .N_elements = 0,
        .sizeof_vertices = 0,
        .sizeof_elements = 0,
        .max_sizeof_vertices = max_sizeof_vertices,
        .max_sizeof_elements = max_sizeof_elements,
    };
static double box_width;
static double box_height;



void opengl_initialize(int width, int height, double box_width_, double box_height_) {
    window = create_window(width, height);
    timerr = initialize_timer();

    box_width = box_width_;
    box_height = box_height_;
    printf("%f %f\n", box_width, box_height);

    vertices = malloc(max_sizeof_vertices);
    elements = malloc(max_sizeof_elements);
    s_opengl.vertices = vertices;   
    s_opengl.elements = elements;
    
    /* cpu_data s = get_vertices_and_elements("ellipse"); */
    gpu_buffers* buffers = initialize_gpu_buffers(s_opengl);
    (void) buffers; // removes compile warning.
    shader_program = load_shaders_into_shader_program();

    //position attribute
    GLint pos_attrib = glGetAttribLocation(shader_program, "position");
    glVertexAttribPointer(pos_attrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(pos_attrib);
     //color attribute
    GLint col_attrib = glGetAttribLocation(shader_program, "color");
    glVertexAttribPointer(col_attrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*) (2* sizeof(GLfloat)));
    glEnableVertexAttribArray(col_attrib);
}

static void opengl_start_frame() {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);
    //reset
    s_opengl.N_elements = 0 ;
    s_opengl.N_vertices = 0 ;
    s_opengl.sizeof_elements = 0;
    s_opengl.sizeof_vertices = 0;
}

static void opengl_end_frame() {
    glBufferSubData(GL_ARRAY_BUFFER, 0, s_opengl.sizeof_vertices, s_opengl.vertices);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, s_opengl.sizeof_elements, s_opengl.elements);
    glDrawElements(GL_TRIANGLES, s_opengl.N_elements, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    frames++;
    display_fps_information(timerr, frames);

    /* Poll for and process events */
    glfwPollEvents();
}

void opengl_terminate() {
    glfwTerminate();
    free(vertices);
    free(elements);
}

void opengl_draw_ellipse_pbc(double x_, double y_, double l_major_, double l_minor_, double angle) {
    /* printf("box:%f %f\n", box_width, box_height); */
    double opengl_coordinate_rescale_factor_x = 2.0/box_width;
    /* double opengl_coordinate_rescale_factor_y = 2.0/box_height; */
    double opengl_coordinate_rescale_factor_y = 2.0/box_width; // TODO FIX THIS STILL
    /* printf("scale:%f %f\n",opengl_coordinate_rescale_factor_x, opengl_coordinate_rescale_factor_y); */

    double x = opengl_coordinate_rescale_factor_x*x_;
    double y = opengl_coordinate_rescale_factor_y*y_;
    /* printf("x:%f %f\n",x_, x); */
    /* printf("y:%f %f\n",y_, y); */

    //this below is not completely correct be careful cus these are not aligned at x or y , depends on angle!!!
    double l_major = opengl_coordinate_rescale_factor_x*l_major_;
    double l_minor = opengl_coordinate_rescale_factor_x*l_minor_;


    double dist = l_major* 0.5;
    if(x < -1.0 + dist) {
        draw_ellipse(&s_opengl, x+2.0, y, l_major, l_minor, angle);
    } else if ( x > 1.0 - dist) {
        draw_ellipse(&s_opengl, x-2.0, y, l_major, l_minor, angle);
    }
    if(y < -1.0 + dist) {
        draw_ellipse(&s_opengl, x, y+2.0, l_major, l_minor, angle);
    } else if ( y > 1.0 - dist) {
        draw_ellipse(&s_opengl, x, y-2.0, l_major, l_minor, angle);
    }
    draw_ellipse(&s_opengl, x, y, l_major, l_minor, angle);
}



void opengl_draw_ellipse(double x, double y, double l_major, double l_minor, double angle) {
    draw_ellipse(&s_opengl, x, y, l_major, l_minor, angle);
}

int opengl_window_open() {
    opengl_end_frame();
    opengl_start_frame();
    return (!glfwWindowShouldClose(window));
}


