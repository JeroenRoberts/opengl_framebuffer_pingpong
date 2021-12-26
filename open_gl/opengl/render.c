#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "render.h"

static void get_elements(GLuint* elements, const int32_t N)
{
    for(int n = 0; n < N; n++)
    {
        elements[12*n + 0] = n*5 + 0;
        elements[12*n + 1] = n*5 + 4;
        elements[12*n + 2] = n*5 + 1;
        elements[12*n + 3] = n*5 + 0;
        elements[12*n + 4] = n*5 + 3;
        elements[12*n + 5] = n*5 + 2;
        elements[12*n + 6] = n*5 + 0;
        elements[12*n + 7] = n*5 + 4;
        elements[12*n + 8] = n*5 + 2;
        elements[12*n + 9] = n*5 + 0;
        elements[12*n + 10] = n*5 + 3;
        elements[12*n + 11] = n*5 + 1;
        
    }

}
/*
 GLuint elements[] = {
        0, 4, 1,
        0, 3, 2,
        0, 4, 2,
        0, 3, 1,
    };
    */
    
void get_vertices(float* vertices, float* xs, float* ys, const int32_t N)
{
    for(int n = 0; n < N; n++)
    {
        float x = xs[n];
        float y = ys[n];
        float dist  = 0.01;
        vertices[10*n + 0] = x;
        vertices[10*n + 1] = y;
        vertices[10*n + 2] = x + dist;
        vertices[10*n + 3] = y;
        vertices[10*n + 4] = x - dist;
        vertices[10*n + 5] = y;
        vertices[10*n + 6] = x;
        vertices[10*n + 7] = y - dist;
        vertices[10*n + 8] = x;
        vertices[10*n + 9] = y + dist;

    }
}

renderer start_render(const int32_t width, const int32_t height, const int32_t N){

    FILE* f_vert_beeg = fopen("beeg.vert", "r");
    FILE* f_frag_beeg = fopen("beeg.frag", "r");

    fseek(f_vert_beeg, 0, SEEK_END);
    const long size_vert = ftell(f_vert_beeg);
    fseek(f_vert_beeg, 0, SEEK_SET);
    char* vertexSource = calloc(size_vert, 1);
    fread(vertexSource, size_vert, 1, f_vert_beeg);

    //const char* const vertexSource[size_vert] 

    fseek(f_frag_beeg, 0, SEEK_END);
    const long size_frag = ftell(f_frag_beeg);
    fseek(f_frag_beeg, 0, SEEK_SET);
    char* fragmentSource = calloc(size_frag, 1);
    fread(fragmentSource, size_frag, 1, f_frag_beeg);
    fclose(f_vert_beeg);
    fclose(f_frag_beeg);


    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        exit(-1);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(-1);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();
    glfwSwapInterval(1);
    //float dist = 0.4;
        //circle with 8 triangle
    float x[N];// = {0 , 0.5};
    float y[N];// = {0, 0};
    for(int n = 0; n < N; n++)
    {
        x[n] = -1 + 0.1*n;
        y[n] = -1 + 0.1*n;
    }
    float vertices[2 * 5 * N];// 2 for (x,y) , 5 for squares

    get_vertices(vertices, x, y, N);
    /*
        float vertices2[] = {
        //  Position      Color             Texcoords
        -1.0f, 1.0f, 
        1.0f,  1.0f,
        1.0f,  -1.0f,
        -1.0f, -1.0f,
    };
    */


         // x, y,  upper right 0,
           // x,  y + dist, 4
            //x + dist,  y , 1
            //
            // x, y,  LWOER LEFT 0
            //x,  y - dist, 3
            //x - dist,  y ,2
            //
            // UPPER LEFT
            // x, y,  0
            //x,  y + dist, 4
            //x - dist,  y , 2
            //
            //LOWER RIGHT
            //  x, y, 0
            //x,  y - dist, 3
            //x + dist,  y , 1
 
    GLuint elements[3 * 4 * N ];//3 per triangle , 4 triangle per
    get_elements(elements, N);
         

    /*
    GLuint elements2[] = {
        0, 1, 2,
        2, 3, 0
    };
    */
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint ebo;
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        sizeof(elements), elements, GL_STATIC_DRAW);


    GLuint vbo;
    glGenBuffers(1, &vbo); // Generate 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        /* Loop until the user closes the window */
    //printf("%ld\n", size_vert);
    //fwrite(vertexSource, size_vert, 1, stdout);
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1,  (const GLchar* const*) (&vertexSource), NULL);
    glCompileShader(vertexShader);
    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);

    if(status != GL_TRUE)
    {
        fprintf(stderr, "vert compilation failed\n");
    }
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1,(const GLchar* const*) (&fragmentSource), NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE)
    {
        fprintf(stderr, "frag compilation failed\n");
    }
 
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");

    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);



    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);
    
    renderer r = {.shaderProgram = shaderProgram, .window = window,
                  .vao = vao, .ebo = ebo, .vbo=vbo};
    return r;
}
