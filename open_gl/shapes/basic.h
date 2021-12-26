#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    GLuint* elements;
    GLint N_elements;
    GLint sizeof_elements;
    GLfloat* vertices;
    GLint N_vertices;
    GLint sizeof_vertices;
    GLint max_sizeof_vertices;
    GLint max_sizeof_elements;
}cpu_data;

typedef struct{
    GLfloat r;
    GLfloat g;
    GLfloat b;
} rgb;

/* cpu_data get_vertices_and_elements(char* shape); */
void draw_ellipse(cpu_data* s, double x, double y, double l_major, double l_minor, double angle);

