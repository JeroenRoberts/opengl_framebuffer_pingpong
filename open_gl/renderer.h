#pragma once
#include "create_window_using_glfw.h"
#include "display_fps.h"
#include "general_includes.h"
#include "initialize_gpu_buffers.h"
#include "load_shaders.h"
#include "set_attributes.h"
#include "swapper.h"
#include "uniforms.h"
#include "upload_vertices.h"

void opengl_terminate();
int opengl_window_open();
void opengl_initialize(int width, int height);
