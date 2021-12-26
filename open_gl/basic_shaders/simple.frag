#version 330 core

in vec4 gl_FragCoord;//is this really vec2?
out vec4 outColor;
in vec2 tex_position_out;
uniform sampler2D tex;
uniform int step;


void main()
{
    outColor = texture(tex, tex_position_out);
}
