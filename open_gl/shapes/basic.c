#define GLEW_STATIC
#include <GL/glew.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "basic.h"


static rgb rgb_based_on_angle(double angle) {
    rgb colors;
    //0 = red
    //-pi/3 = blue;
    //pi/3 = green
    //
    /* angle = fmodf(angle + 2 *M_PI, 2 * M_PI) - 2 * M_PI; */
    /* colors.r = 0.5*(fabs(cos(0.75*angle)) + cos(0.75*angle)); */
    /* colors.g = 0.5*(fabs(cos(0.75*(angle - 0.666*M_PI))) +cos(0.75*(angle - 0.666*M_PI))) ; */
    /* colors.b = 0.5*(fabs(cos(0.75*(angle - 1.333*M_PI))) + cos(0.75*(angle - 1.333*M_PI))) ; */


    colors.r = 0.5*(fabs(cos(angle)) + cos(angle));
    colors.g = 0.5*(fabs(cos((angle - 0.666*M_PI))) +cos((angle - 0.666*M_PI))) ;
    colors.b = 0.5*(fabs(cos((angle - 1.333*M_PI))) + cos((angle - 1.333*M_PI))) ;

    return colors;
}
/* } */

void draw_ellipse(cpu_data* s, double x, double y, double l_major, double l_minor, double angle) { 
    //x in [-1,1]
    //y in [-1,1]
    //angle in [0,2 pi]
    //l_perp in [0,2]
    //l_ortho in [0,2]
   const int N_triangles = 80;
   assert(N_triangles % 4 == 0);

   for(int32_t i_triangle = 0; i_triangle < N_triangles; i_triangle=i_triangle+1) {
       int32_t i_element = 3* i_triangle;
        s->elements[s->N_elements + i_element] = s->N_vertices + 0;
       s->elements[s->N_elements + i_element+1] =s->N_vertices + i_triangle+1;
       s->elements[s->N_elements + i_element+2] = s->N_vertices + (((i_triangle+2) - 1) % N_triangles)  + 1; //subtract then add one to get positive modulues https://stackoverflow.com/questions/3803331/how-can-i-modulo-when-my-numbers-start-from-1-not-zero
   }
   s->N_elements += N_triangles * 3; //3 vertices per triangle
   s->sizeof_elements += sizeof(GLuint) * s->N_elements;



   rgb colors = rgb_based_on_angle(angle);
   int N_coords = 5; //5 = (x, y, r, g , b)
   int N_vertex_coordinates = N_coords * s->N_vertices;
   s->vertices[N_vertex_coordinates + 0] = x;
   s->vertices[N_vertex_coordinates + 1] = y;
   s->vertices[N_vertex_coordinates + 2] = colors.r;
   s->vertices[N_vertex_coordinates + 3] = colors.g;
   s->vertices[N_vertex_coordinates + 4] = colors.b;

   const double base_angle_ratio_from_two_pi = 1/(double) N_triangles; 
//https://math.stackexchange.com/questions/2645689/what-is-the-parametric-equation-of-a-rotated-ellipse-given-the-angle-of-rotatio
   for(int32_t i = 0; i < N_triangles; i=i+1) {
       double parameter_angle = i*2*M_PI * base_angle_ratio_from_two_pi;//this just varies from 0 to 2pi
       //pos
       s->vertices[N_vertex_coordinates + N_coords*(i+1)] = x + l_major*cos(parameter_angle)*cos(angle) - l_minor*sin(parameter_angle)*sin(angle);
       s->vertices[N_vertex_coordinates+ N_coords*(i+1)+1] = y + l_major*cos(parameter_angle)*sin(angle)+ l_minor*sin(parameter_angle)*cos(angle);

       //color
       s->vertices[N_vertex_coordinates+ N_coords*(i+1)+2] = colors.r;
       s->vertices[N_vertex_coordinates+ N_coords*(i+1)+3] = colors.g;
       s->vertices[N_vertex_coordinates+ N_coords*(i+1)+4] = colors.b;
   }

   s->N_vertices += N_triangles + 1;
   s->sizeof_vertices += sizeof(GLfloat) * N_coords * s->N_vertices;
}


/* cpu_data get_vertices_and_elements(char* shape_name) { */
/*    extern cpu_data s_opengl; */
/*    if(strcmp(shape_name, "triangle") == 0) { */
/*        s_opengl.N_elements = 3; */
/*        s_opengl.sizeof_elements = sizeof(GLuint) * s_opengl.N_elements; */
/*        s_opengl.elements[0] = 0; */
/*        s_opengl.elements[1] = 1; */
/*        s_opengl.elements[2] = 2; */

/*        s_opengl.N_vertices = 2; */
/*        s_opengl.sizeof_vertices = sizeof(GLfloat) * 2 * s_opengl.N_vertices; */
/*        s_opengl.vertices = malloc(sizeof(GLfloat) * 2 * s_opengl.N_vertices); // 2 = len(x, y) */
/*        s_opengl.vertices[0] = -0.5f; */
/*        s_opengl.vertices[1] = -0.5f; */

/*        s_opengl.vertices[2] = 0.5f; */
/*        s_opengl.vertices[3] = -0.5f; */

/*        s_opengl.vertices[4] = 0.0f; */
/*        s_opengl.vertices[5] = 0.5f; */

/*    }else if(strcmp(shape_name, "square") == 0) { */
/*        s_opengl.N_elements = 6; */
/*        s_opengl.sizeof_elements = sizeof(GLuint) * s_opengl.N_elements; */
/*        s_opengl.elements = malloc(sizeof(GLuint) * s_opengl.N_elements); */
/*        s_opengl.elements[0] = 0; */
/*        s_opengl.elements[1] = 1; */
/*        s_opengl.elements[2] = 3; */

/*        s_opengl.elements[3] = 1; */
/*        s_opengl.elements[4] = 2; */
/*        s_opengl.elements[5] = 3; */

/*        s_opengl.N_vertices = 4; */
/*        s_opengl.sizeof_vertices = sizeof(GLfloat) * 2 * s_opengl.N_vertices; */
/*        s_opengl.vertices = malloc(sizeof(GLfloat) * 2 * s_opengl.N_vertices); //2 = len(x,y) */
/*        s_opengl.vertices[0] = 0.5f; */
/*        s_opengl.vertices[1] = 0.5f; */

/*        s_opengl.vertices[2] = 0.5f; */
/*        s_opengl.vertices[3] = -0.5f; */

/*        s_opengl.vertices[4] = -0.5f; */
/*        s_opengl.vertices[5] = -0.5f; */

/*        s_opengl.vertices[6] = -0.5f; */
/*        s_opengl.vertices[7] = 0.5f; */


/*    } */
/*    else if(strcmp(shape_name, "circle") == 0) { */
/*        const int N_triangles = 80; */
/*        assert(N_triangles % 4 == 0); */

/*        s_opengl.N_elements = N_triangles * 3; //3 vertices per triangle */
/*        s_opengl.sizeof_elements = sizeof(GLuint) * s_opengl.N_elements; */
/*        s_opengl.elements = malloc(sizeof(GLuint) * s_opengl.N_elements); */
/*        for(int32_t i_triangle = 0; i_triangle < N_triangles; i_triangle=i_triangle+1) { */
/*            int32_t i_element = 3* i_triangle; */
/*            s_opengl.elements[i_element] = 0; */
/*            s_opengl.elements[i_element+1] = i_triangle+1; */
/*            s_opengl.elements[i_element+2] = (((i_triangle+2) - 1) % N_triangles)  + 1; //subtract then add one to get positive modulues https://stackoverflow.com/questions/3803331/how-can-i-modulo-when-my-numbers-start-from-1-not-zero */
/*        } */

/*        s_opengl.N_vertices = N_triangles + 1; */
/*        s_opengl.sizeof_vertices = sizeof(GLfloat) * 2 * s_opengl.N_vertices; */
/*        s_opengl.vertices = malloc(sizeof(GLfloat) * 2 * s_opengl.N_vertices); */
/*        s_opengl.vertices[0] = 0.0f; */
/*        s_opengl.vertices[1] = 0.0f; */

/*        const double base_angle_ratio_from_two_pi = 1/(double) N_triangles; */ 
/*        for(int32_t i = 0; i < N_triangles; i=i+1) { */
/*            s_opengl.vertices[2*(i+1)] = 0.5*cos(i*2*M_PI * base_angle_ratio_from_two_pi); */
/*            s_opengl.vertices[2*(i+1)+1] = 0.5*sin(i*2*M_PI * base_angle_ratio_from_two_pi); */
/*        } */

/*    } else if(strcmp(shape_name, "ellipse") == 0) { */
/*        const int N_triangles = 80; */
/*        assert(N_triangles % 4 == 0); */

/*        s_opengl.N_elements = N_triangles * 3; //3 vertices per triangle */
/*        s_opengl.sizeof_elements = sizeof(GLuint) * s_opengl.N_elements; */
/*        s_opengl.elements = malloc(sizeof(GLuint) * s_opengl.N_elements); */
/*        for(int32_t i_triangle = 0; i_triangle < N_triangles; i_triangle=i_triangle+1) { */
/*            int32_t i_element = 3* i_triangle; */
/*            s_opengl.elements[i_element] = 0; */
/*            s_opengl.elements[i_element+1] = i_triangle+1; */
/*            s_opengl.elements[i_element+2] = (((i_triangle+2) - 1) % N_triangles)  + 1; //subtract then add one to get positive modulues https://stackoverflow.com/questions/3803331/how-can-i-modulo-when-my-numbers-start-from-1-not-zero */
/*        } */

/*        s_opengl.N_vertices = N_triangles + 1; */
/*        s_opengl.sizeof_vertices = sizeof(GLfloat) * 2 * s_opengl.N_vertices; */
/*        s_opengl.vertices = malloc(sizeof(GLfloat) * 2 * s_opengl.N_vertices); */
/*        s_opengl.vertices[0] = 0.0f; */
/*        s_opengl.vertices[1] = 0.0f; */

/*        const double base_angle_ratio_from_two_pi = 1/(double) N_triangles; */ 
/*        for(int32_t i = 0; i < N_triangles; i=i+1) { */
/*            s_opengl.vertices[2*(i+1)] = 0.3*cos(i*2*M_PI * base_angle_ratio_from_two_pi); */
/*            s_opengl.vertices[2*(i+1)+1] = 0.6*sin(i*2*M_PI * base_angle_ratio_from_two_pi); */
/*        } */

/*    } */


/*    else{ */
/*        printf("error invalid shape, EXITING\n"); */
/*        exit(-1); */
/*    } */

/*    return s_opengl; */
/* } */


