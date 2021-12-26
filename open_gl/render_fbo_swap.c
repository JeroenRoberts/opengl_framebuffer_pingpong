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
#include "SOIL/SOIL.h"

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

static GLint uniform_step;

static void initialize_uniforms(){

    uniform_step = glGetUniformLocation(shader_program, "step");
}
static enum MODE M;


static void load_texture(char* file_name, GLenum texture_unit) {
    int width, height;
    glActiveTexture(texture_unit);
    GLuint tex_source;
    glGenTextures(1, &tex_source);
    glBindTexture(GL_TEXTURE_2D, tex_source);

    unsigned char* image = SOIL_load_image(file_name, &width, &height, 0, SOIL_LOAD_RGB);
    if(image) {
        printf("loaded image %d %d\n", width, height);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                  GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
    }
    else {
        fprintf(stderr, "failed to load image");
        exit(-1);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    printf("texture: %d\n", tex_source);
    glUniform1i(glGetUniformLocation(shader_program, "tex"), 0);

}

void opengl_initialize(enum MODE mode, int width, int height, char* vertex_file_name, char* fragment_file_name) {
    window = create_window(width, height);
    timerr = initialize_timer();
    M = mode;

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

    switch(M){
        case(NORMAL_DRAW): {
            break;
        }
        case(TEXTURE_SWAP): {
            create_swapper(width, height);
            break;
        }
        case(LOAD_TEXTURE): {
            load_texture("cat.jpeg", GL_TEXTURE0);
            load_texture("dog.png", GL_TEXTURE1);

            break;
        }
    }

    //uniforms
    initialize_uniforms();

}
static void update_uniforms() {
    glUniform1i(uniform_step, frames);
}

static void opengl_start_frame() {
    if(frames > 120) {
        glUniform1i(glGetUniformLocation(shader_program, "tex"), 1);
    }
    update_uniforms();
    switch(M){
        case(NORMAL_DRAW): {
            break;
        }
        case(TEXTURE_SWAP): {
            perform_swap(shader_program);
            /* glClear(GL_COLOR_BUFFER_BIT); */
            /* glDrawElements(GL_TRIANGLES, s_draw_rectangle.N_elements, GL_UNSIGNED_INT, 0); */
            break;
        }
        case(LOAD_TEXTURE): {
            break;
 
        }
    }


}

static void opengl_end_frame() {
    /* glBindFramebuffer(GL_FRAMEBUFFER, 0); // 0 = screen (visual , i.e. CAN SEE) */
    glClear(GL_COLOR_BUFFER_BIT);
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



