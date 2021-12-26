CC = gcc
# CFLAGS = -Wall -O0 -g #when debugging with gdb use this instead
CFLAGS = -Wall -O3 -g
LIBS = `pkg-config --libs --cflags glew glfw3` -lGL -lm

OPENGL_SRCS =  open_gl/create_window_using_glfw.c \
							 open_gl/display_fps.c \
							 open_gl/initialize_gpu_buffers.c \
							 open_gl/upload_vertices.c \
							 open_gl/load_shaders.c \
							 open_gl/swapper.c \
							 open_gl/renderer.c \
							 open_gl/set_attributes.c \
							 open_gl/uniforms.c \

SRCS = $(OPENGL_SRCS) \

OBJS = $(SRCS:.c=.o)

main: main.o $(OBJS)
	$(CC) $(CFLAGS) $^ -o main.out $(LIBS)

.PHONY: clean

clean:
	rm -f $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(LIBS)

