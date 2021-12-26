#pragma once
#include "general_includes.h"

typedef struct {
    GLuint vao;
    GLuint ebo;
    GLuint vbo;
} gpu_buffers;

gpu_buffers* initialize_gpu_buffers();
