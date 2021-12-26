#pragma once
#include "general_includes.h"

typedef struct {
    GLuint* elements;
    GLint N_elements;
    GLint sizeof_elements;
    GLfloat* vertices;
    GLint N_vertices;
    GLint sizeof_vertices;
} cpu_data;

void draw_rectangle();
void upload_vertices_rectangle();
