#include "load_shaders.h"

static char* read_from_file(char* file_name) {
    FILE* f = fopen(file_name, "r");
    assert(f != NULL);

    fseek(f, 0, SEEK_END);
    const long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    char* string = calloc(size, 1);
    assert(fread(string, size, 1, f) > 0);
    fclose(f);

    return string;
}
static GLuint compile_shader(char* file_name, char* type) {
    char* fragmentSource = read_from_file(file_name);
    GLuint fragmentShader;
    if (strcmp(type, "vert") == 0) {
        fragmentShader = glCreateShader(GL_VERTEX_SHADER);
    } else if (strcmp(type, "frag") == 0) {
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    } else {
        exit(-1);
    }
    glShaderSource(fragmentShader, 1, (const GLchar* const*)(&fragmentSource),
                   NULL);
    glCompileShader(fragmentShader);
    GLint status;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        fprintf(stderr, "%s compilation failed\n", type);
        int max_length = 10000;
        char error_log[max_length];
        glGetShaderInfoLog(fragmentShader, max_length, &max_length, error_log);
        fprintf(stderr, "\n\n%s Compile Error:\n%s\n\n", type, error_log);
    }
    return fragmentShader;
}

GLuint load_shaders_into_shader_program(shader_files s_files) {
    GLuint vertexShader = compile_shader(s_files.vert, "vert");
    GLuint fragmentShader = compile_shader(s_files.frag, "frag");

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glBindFragDataLocation(
        shaderProgram, 0,
        "outColor"); // selects which draw buffer
                     // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBindFragDataLocation.xhtml
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    return shaderProgram;
}
