#include "initialize_gpu_buffers.h"

gpu_buffers* initialize_gpu_buffers() {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint ebo;
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    gpu_buffers* buffers = malloc(sizeof(gpu_buffers));
    buffers->vao = vao;
    buffers->vbo = vbo;
    buffers->ebo = ebo;
    return buffers;
}
