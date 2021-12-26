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


void opengl_terminate();
void opengl_draw_ellipse(double x, double y, double l_major, double l_minor, double angle);
int opengl_window_open();
void opengl_draw_ellipse_pbc(double x_, double y_, double l_major_, double l_minor_, double angle);
void opengl_initialize(int width, int height, double box_width_, double box_height_);
