#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "initialize_gpu_buffers.h"
#include "shapes/basic.h"

gpu_buffers* initialize_gpu_buffers(cpu_data s){
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint ebo;
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, s.sizeof_elements, s.elements, GL_STATIC_DRAW);

    GLuint vbo;
    glGenBuffers(1, &vbo); // Generate 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, s.sizeof_vertices, s.vertices, GL_STATIC_DRAW);
    gpu_buffers* buffers = malloc(sizeof(gpu_buffers));
    buffers->vao = vao;
    buffers->vbo = vbo;
    buffers->ebo = ebo;
    buffers->s = s;
    return buffers;
}



