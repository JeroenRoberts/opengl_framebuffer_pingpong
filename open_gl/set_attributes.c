#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "create_window_using_glfw.h"
#include "display_fps.h"
#include "initialize_gpu_buffers.h"
#include "upload_vertices.h"
#include "load_shaders.h"
#include "swapper.h"
#include "SOIL/SOIL.h"
#include "set_attributes.h"


void set_attributes(GLint shader_program) {
    //position attribute
    GLint pos_attrib = glGetAttribLocation(shader_program, "position");
    glVertexAttribPointer(pos_attrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(pos_attrib);

    //texture attribute
    GLint tex_pos_attrib = glGetAttribLocation(shader_program, "tex_position");
    glVertexAttribPointer(tex_pos_attrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(tex_pos_attrib);

}
