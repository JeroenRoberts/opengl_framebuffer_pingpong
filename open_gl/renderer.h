#pragma once
#include "general_includes.h"
#include "load_shaders.h"
#include "display_fps.h"
#include "create_window_using_glfw.h"
#include "set_attributes.h"
#include "swapper.h"
#include "initialize_gpu_buffers.h"
#include "upload_vertices.h"
#include "uniforms.h"

void opengl_terminate();
int opengl_window_open();
void opengl_initialize(int width, int height);
