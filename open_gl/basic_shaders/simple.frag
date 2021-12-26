#version 330 core

in vec4 gl_FragCoord;//is this really vec2?
out vec4 outColor;
in vec2 tex_position_out;
uniform sampler2D tex;
uniform int step;


void main()
{
    float r = step/600.0;
    outColor = vec4(r, 0.5, 0.0 , 1.0);
    /* outColor = vec4(gl_FragCoord.x/1000.0, gl_FragCoord.y/1000.0, 0.5 , 1.0); */
    /* outColor= texture(tex, tex_position_out); */
}
