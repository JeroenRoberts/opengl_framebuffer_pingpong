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

#define WIDTH 800
#define HEIGHT 800


enum consts { 
 max_N_vertices = 10000,
 max_N_elements = 30000
 };


int main()
{
    GLFWwindow* window = create_window(WIDTH, HEIGHT);
    timer* timer = initialize_timer();

    const GLint max_sizeof_vertices = 5 * max_N_vertices * sizeof(GLfloat);
    const GLint max_sizeof_elements = max_N_elements * sizeof(GLuint);
    GLfloat* vertices = malloc(max_sizeof_vertices);
    GLuint* elements = malloc(max_sizeof_elements);
    /* cpu_data s = get_vertices_and_elements("ellipse"); */
    cpu_data s = {
        .N_vertices = 0,
        .N_elements = 0,
        .sizeof_vertices = 0,
        .sizeof_elements = 0,
        .vertices = vertices,   
        .elements = elements,
        .max_sizeof_vertices = max_sizeof_vertices,
        .max_sizeof_elements = max_sizeof_elements,
    };

    gpu_buffers* buffers = initialize_gpu_buffers(s);
    GLuint shader_program = load_shaders_into_shader_program();

    //position attribute
    GLint pos_attrib = glGetAttribLocation(shader_program, "position");
    glVertexAttribPointer(pos_attrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(pos_attrib);
     //color attribute
    GLint col_attrib = glGetAttribLocation(shader_program, "color");
    glVertexAttribPointer(col_attrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*) (2* sizeof(GLfloat)));
    glEnableVertexAttribArray(col_attrib);

    

    int32_t frames = 0;
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //reset
        s.N_elements = 0 ;
        s.N_vertices = 0 ;
        s.sizeof_elements = 0;
        s.sizeof_vertices = 0;

        /* draw_ellipse(&s, -0.5, -0.5, 0.6, 0.3, 0.5*M_PI); */
        /* draw_ellipse(&s, -0.5, 0.0, 0.6, 0.3, 0.5*M_PI); */
        /* draw_ellipse(&s, -0.5, 0.0, 0.6*cos(frames*0.01), 0.3*cos(frames*0.003), M_PI*frames*frames*0.0001); */
        /* draw_ellipse(&s, 0.5, 0.0, 0.6*sin(frames*0.01), 0.3*sin(frames*0.003), M_PI*frames*frames*0.0001); */


        draw_ellipse(&s, -0.5, 0.0, 0.3, 0.1, 0+ M_PI*frames*0.01);
        draw_ellipse(&s, 0.0, 0.0, 0.3, 0.1, 0.666*M_PI + M_PI*frames*0.01);
        draw_ellipse(&s, 0.5, 0.0, 0.3, 0.1, 1.333*M_PI+ M_PI*frames*0.01);
        /* draw_ellipse(&s, 0.5, 0.0, 0.6, 0.3, M_PI*frames*0.01); */
        /* draw_ellipse(&s, 0.5, 0.0, 0.6*sin(frames*0.01), 0.3*sin(frames*0.003), M_PI*frames*frames*0.0001); */
        glBufferSubData(GL_ARRAY_BUFFER, 0, s.sizeof_vertices, s.vertices);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, s.sizeof_elements, s.elements);
        glDrawElements(GL_TRIANGLES, s.N_elements, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        frames++;
        display_fps_information(timer, frames);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();


    return 0;
}
