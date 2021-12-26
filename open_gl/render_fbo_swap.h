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
#include "create_window_using_glfw.h"
#include "display_fps.h"
#include "initialize_gpu_buffers.h"
#include "shapes/basic.h"
#include "load_shaders.h"

enum MODE {
    NORMAL_DRAW,
    TEXTURE_SWAP,
    LOAD_TEXTURE,
};


void opengl_terminate();
int opengl_window_open();
void opengl_initialize(enum MODE M, int width, int height, char* vertex_file_name, char* fragment_file_name);
