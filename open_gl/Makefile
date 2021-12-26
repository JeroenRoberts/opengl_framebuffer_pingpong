CC = gcc
CFLAGS = -Wall -Og -g
LIBS = `pkg-config --libs --cflags glew glfw3` -lGL -lm -I.


SRCS = create_window_using_glfw.c \
			 display_fps.c \
			 initialize_gpu_buffers.c \
			 shapes/basic.c \
			 load_shaders.c \
			 renderer.c \

OBJS = $(SRCS:.c=.o)


main: main.o $(OBJS) 
	$(CC) $(CFLAGS) $^ -o $(<:.o=.out) $(LIBS)

test_render: test_render.o $(OBJS) 
	$(CC) $(CFLAGS) $^ -o $(<:.o=.out) $(LIBS)



.PHONY: clean

clean:
	rm -f $(OBJS)


%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(LIBS)

