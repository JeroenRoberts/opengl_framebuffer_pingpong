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
#include "initialize_gpu_buffers.h"
#include "shapes/basic.h"

typedef struct{
    GLuint id;
    GLenum GL_unit;
    GLuint fbo;
}texture;

typedef struct{
    texture tex_1;
    texture tex_2;
}swapper;

void create_swapper(int width, int height);
