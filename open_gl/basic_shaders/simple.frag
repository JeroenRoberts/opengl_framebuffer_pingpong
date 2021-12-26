#version 330 core

in vec4 gl_FragCoord;//is this really vec2?
out vec4 outColor;


void main()
{
    /* outColor = vec4(1.0, 0.0, 0.0 , 1.0); */
    outColor = vec4(gl_FragCoord.x/1000.0, gl_FragCoord.y/1000.0, 0.5 , 1.0);
}
