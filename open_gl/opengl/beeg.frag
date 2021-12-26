#version 330 core
//uniform float pos_x;
//uniform float pos_y;


in vec4 gl_FragCoord;

out vec4 outColor;



void main()
{
    outColor = vec4(0.8, 0.1, 0.2, 1.0);
 

    /*
    float x = gl_FragCoord.x / 800.0;
    float y = gl_FragCoord.y / 800.0;
     
    if(radius(x-0.5, y -0.5) < 0.3)
    {
        outColor = vec4(0.5, 0.0, 1.0, 1.0);
    }

    if(radius(x - pos_x, y - pos_y) < 0.01)
    {
        outColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
    */


}
