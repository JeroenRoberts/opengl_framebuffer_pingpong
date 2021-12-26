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
#include "load_shaders.h"

static char* read_from_file(char* file_name) {
    FILE* f = fopen(file_name, "r");

    fseek(f, 0, SEEK_END);
    const long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    char* string = calloc(size, 1);
    assert(fread(string, size, 1, f) > 0);
    fclose(f);

    return string;
}

static GLuint compile_vertex_shader() {
    char* vertexSource = read_from_file("/home/jeroen/PhD_simulations/opengl_plotting/basic_shaders/simple.vert");
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1,  (const GLchar* const*) (&vertexSource), NULL);
    glCompileShader(vertexShader);
    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);

    if(status != GL_TRUE)
    {
        fprintf(stderr, "vert compilation failed\n");
    }
    
    return vertexShader;
}

static GLuint compile_fragment_shader() {
    char* fragmentSource = read_from_file("/home/jeroen/PhD_simulations/opengl_plotting/basic_shaders/simple.frag");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1,(const GLchar* const*) (&fragmentSource), NULL);
    glCompileShader(fragmentShader);
    GLint status;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE)
    {
        fprintf(stderr, "frag compilation failed\n");
    }
    return fragmentShader;
}


GLuint load_shaders_into_shader_program(){
    GLuint vertexShader =  compile_vertex_shader();
    GLuint fragmentShader=  compile_fragment_shader();

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glBindFragDataLocation(shaderProgram, 0, "outColor");//selects which draw buffer https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBindFragDataLocation.xhtml
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    return shaderProgram;
}

