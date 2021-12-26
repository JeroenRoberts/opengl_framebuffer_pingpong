#include "upload_vertices.h"
static GLfloat vertices[]= {
        -1.0f, 1.0f, 0.0f, 0.0f, // Top left: pos_x, pos_y, texture_pos_x, texture_pos_y
        1.0f, 1.0f, 1.0f, 0.0f, // Top right: pos_x, pos_y, texture_pos_x, texture_pos_y
        1.0f, -1.0f,  1.0f, 1.0f,// bottom right: pos_x, pos_y, texture_pos_x, texture_pos_y
        -1.0f, -1.0f, 0.0f, 1.0f, // bottom left: pos_x, pos_y, texture_pos_x, texture_pos_y
    };
static GLuint elements[]= {
        0, 1, 2, //Draws top right triangle
        2, 3, 0  //Draws bottom left triangle
    };

static cpu_data s_draw_rectangle = {
    .N_vertices = 16,
    .N_elements = 6,
    .sizeof_vertices = 16 * sizeof(GLfloat),
    .sizeof_elements = 6 * sizeof(GLuint),
};


void upload_vertices_rectangle() {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, s_draw_rectangle.sizeof_elements, elements, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, s_draw_rectangle.sizeof_vertices, vertices, GL_STATIC_DRAW);
}
void draw_rectangle() {
    glDrawElements(GL_TRIANGLES, s_draw_rectangle.N_elements, GL_UNSIGNED_INT, 0);
}



