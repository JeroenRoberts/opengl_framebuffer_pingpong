#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "upload_vertices.h"

typedef struct{
    GLuint vao;
    GLuint ebo;
    GLuint vbo;
    cpu_data s;
}gpu_buffers;


gpu_buffers* initialize_gpu_buffers();
