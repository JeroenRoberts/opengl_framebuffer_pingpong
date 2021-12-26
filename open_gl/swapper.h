#pragma once
#include "general_includes.h"

typedef struct{
    GLuint id;
    GLenum GL_unit;
    GLenum color_attachment;
}texture;

typedef struct{
    GLuint fbo_1;
    GLuint fbo_2;
    texture tex_1;
    texture tex_2;
}swapper;

void create_swapper(int width, int height);
void perform_swap(GLint shader_program_update, GLint shader_program_screen);
