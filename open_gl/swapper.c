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
#include "shapes/basic.h"


#include "swapper.h"
static swapper* fbo_swapper;
static int current_color_attachment = 0;

static GLuint create_fbo() {
    GLuint fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    return fbo;
}

static texture create_texture(int width, int height, GLenum texture_unit) {
    texture tex;
    tex.GL_unit = texture_unit;
    glGenTextures(1, &(tex.id)); // here 1 means create 1 texture
    glActiveTexture(tex.GL_unit); //TODO: is this really neccesary?
    glBindTexture(GL_TEXTURE_2D, tex.id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width,height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    tex.fbo = create_fbo();

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex.id, 0);

    return tex;
}

void perform_swap() {
    if(current_color_attachment == 0) {
        current_color_attachment = 1;
    }
    else {
        current_color_attachment = 0;
    }
}

void create_swapper(int width, int height) {
    fbo_swapper = malloc(sizeof(swapper));
    fbo_swapper->tex_1 = create_texture(width, height, GL_TEXTURE0);
    fbo_swapper->tex_2 = create_texture(width, height, GL_TEXTURE1);
}



