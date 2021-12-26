#pragma once
#include "general_includes.h"

typedef struct {
    char* vert;
    char* frag;
} shader_files;

GLuint load_shaders_into_shader_program(shader_files s);
