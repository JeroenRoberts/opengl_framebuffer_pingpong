#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "render.h"
#include <assert.h>

#define WIDTH 1080.0
#define HEIGHT 1080.0

float test_cases(float *angle, float *pos_x, float *pos_y, int test_id) {
    *angle = M_PI / 2;
    *pos_x = 0.7 - 0.01;
    *pos_y = 0.01;

    test_id = 2;
    float expected_angle = 0;
    switch (test_id) {
    case 0:
        *angle = M_PI / 4;
        *pos_x = 0;
        *pos_y = 0;
        expected_angle = *angle + M_PI;
        break;
    case 1:
        *angle = 3 * M_PI / 4;
        *pos_x = 1;
        *pos_y = 0;
        break;
    case 2:
        *angle = 2.5 * M_PI / 4;
        *pos_x = 1;
        *pos_y = 0;
     
        break;
    case 3:
        break;
    case 4:
        break;
    }
    return expected_angle;
}

float reflect_from_center(float angle, float* pos_x, float* pos_y, float velocity)
{
        float pos_x_from_center = *pos_x;
        float pos_y_from_center = *pos_y;

        float new_angle = angle;
        if(sqrt(pos_x_from_center * pos_x_from_center + pos_y_from_center * pos_y_from_center) < 0.7)
        {

            if(angle > 2 * M_PI)
            {
                angle = angle - 2*M_PI;
            }
            *pos_x -= velocity * cos(angle);
            *pos_y -= velocity * sin(angle);


            //printf("original angle: %f\n", angle);
            

            float inc_angle;
            if( angle > M_PI )
            {
                inc_angle = angle - M_PI;
            } else
            {
                inc_angle = angle + M_PI;
            }
            //printf("incoming angle: %f\n", inc_angle);
            float norm_x = *pos_x;
            float norm_y = *pos_y;

            float norm_angle;
            if(norm_y < 0.0)
            {
                norm_angle =  M_PI + atan(norm_y / norm_x);
            } else if (norm_x < 0.0)
            {
                norm_angle =  2 * M_PI + atan(norm_y / norm_x);
            } else 
            {
                norm_angle = atan(norm_y / norm_x);
            }
            assert( 0< norm_angle && norm_angle < 2* M_PI);

            //printf("normal angle: %f\n", norm_angle);


            float angle_incidence = norm_angle - inc_angle;

            //float angle_out = angle_incidence;
            
            /*
            if( angle_incidence < 0 )
            {
                //new_angle =  norm_angle + angle_incidence;// this is doing nothing
                angle_incidence = angle_incidence + M_PI;
            }else
            {
                //new_angle =  angle + angle_incidence;
                angle_incidence = angle_incidence - M_PI;
            }
            */
           
            //printf("incidence angle: %f\n", angle_incidence);
            new_angle =  inc_angle + 2 * angle_incidence;
            //printf("outgoing angle %f\n", new_angle);


        }
        return new_angle;

}


float bc_torus(float pos_x)
{
    if(pos_x > 1.0)
    {
        pos_x = pos_x - 2.0;
    }

    if(pos_x < -1.0)
    {
        pos_x = pos_x + 2.0;
    }

    return pos_x;
}


int main(void)
{

    const int32_t N = 40000;
    renderer r = start_render(WIDTH, HEIGHT, N);
    //GLuint shaderProgram = r.shaderProgram;
    GLFWwindow* window = r.window;
    //GLuint vbo = r.vbo;
    //GLint u_pos_x = glGetUniformLocation(shaderProgram, "pos_x");
    //GLint u_pos_y = glGetUniformLocation(shaderProgram, "pos_y");

    clock_t start = clock();
    int frames = 0;
    int seconds_passed =0;
    float velocity[N];
    float angle[N];
    float x[N];
    float y[N];
    for(int n = 0; n < N; n++)
    {
        velocity[n] = 0.02;
        angle[n] = 3*M_PI / 4;//((double)n/N)* 2 * M_PI;
        x[n] = -1 + 0.003 * ( (double) n / N );//-1 + 0.1 * ((double) n /N);
        y[n] = -0.98;
    }
    
    //float expected_angle = test_cases(&angle, &pos_x, &pos_y, 2);
    //printf("expected angle %f \n", expected_angle);
   while (!glfwWindowShouldClose(window))
    {

        clock_t now = clock();
        double time =  ((double)(now - start ))/ CLOCKS_PER_SEC;
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //circle with 8 triangle
        for(int n = 0; n < N; n++)
        {
            x[n] = bc_torus(x[n] + velocity[n] * cos(angle[n]));
            y[n] = bc_torus(y[n] + velocity[n] * sin(angle[n]));

            angle[n] = reflect_from_center(angle[n], &x[n], &y[n], velocity[n]);
        }

        float vertices_circle[2 * 5 * N];// 2 for (x,y) , 5 for squares
        get_vertices(vertices_circle, x, y, N);
        /*float vertices_circle[] = {
        //  Position  
            x, y, //0
            x + dist,  y,//1
            x - dist,  y,//2
            x,  y - dist,//3
            x,  y + dist,//4
        };
        */

         // x, y,  upper right 1,
           // x,  y + dist, 5
            //x + dist,  y , 2
            //
            // x, y,  LWOER LEFT 1
            //x,  y - dist, 4
            //x - dist,  y , 3
            //
            // UPPER LEFT
            // x, y,  1
            //x,  y + dist, 5
            //x - dist,  y , 3
            //
            //LOWER RIGHT
            //  x, y, 1
            //x,  y - dist, 4
            //x + dist,  y , 2
           
            
            

        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices_circle), vertices_circle);
           // (GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glDrawElements(GL_TRIANGLES, 12*N, GL_UNSIGNED_INT, 0);


        //pos_x += velocity * cos(angle);
        //pos_y += velocity * sin(angle);

        //pos_x = bc_torus(pos_x);
        //pos_y = bc_torus(pos_y);

        //angle = reflect_from_center(angle, &pos_x, &pos_y, velocity);
        

        //glUniform1f(u_pos_x, pos_x);
        //glUniform1f(u_pos_y, pos_y);


        /* Swap front and back buffers */

        frames++;
        glfwSwapBuffers(window);
        if(time > 0.01 * (seconds_passed + 1))
        {
            printf("time %f frames: %d\n",time , frames);
            seconds_passed++;
            // frames = 0;
        }

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
