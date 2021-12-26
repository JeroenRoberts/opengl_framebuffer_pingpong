#version 330 core
in vec2 position;
in vec2 tex_position;
out vec2 tex_position_out;


void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
    tex_position_out = tex_position;
}
