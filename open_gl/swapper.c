#include "swapper.h"
static swapper* fbo_swapper;
static int ping_pong = 0;

static GLuint create_fbo() {
    GLuint fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    return fbo;
}

static texture create_texture(int width, int height, GLenum frame_buffer, GLenum texture_unit, GLenum color_attachment) {
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

    tex.color_attachment = color_attachment;
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer); 
    glFramebufferTexture2D(GL_FRAMEBUFFER, tex.color_attachment, GL_TEXTURE_2D, tex.id, 0);

    return tex;
}

void perform_swap(GLint shader_program) {
    if(ping_pong == 0) {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo_swapper->fbo_2);
        glUniform1i(glGetUniformLocation(shader_program, "tex"), 0);
        ping_pong = 1;
    }
    else {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo_swapper->fbo_1);
        glUniform1i(glGetUniformLocation(shader_program, "tex"), 1);
        ping_pong = 0;
    }
}

void create_swapper(int width, int height) {
    fbo_swapper = malloc(sizeof(swapper));
    fbo_swapper->fbo_1 = create_fbo();
    fbo_swapper->fbo_2 = create_fbo();
    fbo_swapper->tex_1 = create_texture(width, height, fbo_swapper->fbo_1, GL_TEXTURE0, GL_COLOR_ATTACHMENT0);
    fbo_swapper->tex_2 = create_texture(width, height, fbo_swapper->fbo_2, GL_TEXTURE1, GL_COLOR_ATTACHMENT0);
}



