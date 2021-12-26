#version 330 core

in vec4 gl_FragCoord;//is this really vec2?
in vec3 vertex_color;

out vec4 outColor;



void main()
{
    outColor = vec4(vertex_color, 1.0);
}
