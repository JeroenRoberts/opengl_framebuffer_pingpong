#include "uniforms.h"
static GLint uniform_step;

void initialize_uniforms(GLint shader_program){

    uniform_step = glGetUniformLocation(shader_program, "step");
}

void update_uniforms(int frames) { // before calling this make sure correct shader program is activated
    glUniform1i(uniform_step, frames);
}


