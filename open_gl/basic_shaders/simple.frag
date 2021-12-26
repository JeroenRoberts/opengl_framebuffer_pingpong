#version 330 core

in vec4 gl_FragCoord;//is this really vec2?
out vec4 outColor;
in vec2 tex_position_out;
uniform sampler2D tex;
uniform int step;


void main()
{
    /* float x = tex_position_out.x; */
    outColor = texture(tex, tex_position_out);
    /* outColor = vec4(x, 0.0, 0.0, 1.0); */
}
