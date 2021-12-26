#include "renderer.h"

static GLFWwindow* window;
static timer* timerr;
static int frames = 0;

void opengl_initialize(int width, int height) {
    window = create_window(width, height);
    timerr = initialize_timer();

    
    gpu_buffers* buffers = initialize_gpu_buffers();
    (void) buffers; // this avoids compile warning.
    upload_vertices_rectangle();

}
void opengl_terminate() {
    glfwTerminate();
}

int opengl_window_open() {

    glfwSwapBuffers(window);
    frames++;
    display_fps_information(timerr, frames);

    /* Poll for and process events */
    glfwPollEvents();

    return (!glfwWindowShouldClose(window));
}



