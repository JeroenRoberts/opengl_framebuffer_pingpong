#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


typedef struct{
    GLuint shaderProgram;
    GLFWwindow* window;
    GLuint vao;
    GLuint ebo;
    GLuint vbo;
}renderer;


renderer start_render(const int32_t width, const int32_t height, const int32_t N);

void get_vertices(float* vertices, float* xs, float* ys, const int32_t N);
