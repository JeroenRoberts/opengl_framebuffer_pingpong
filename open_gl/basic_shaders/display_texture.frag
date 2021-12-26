#version 330 core

in vec4 gl_FragCoord;//is this really vec2?
out vec4 outColor;
in vec2 tex_position_out;
uniform sampler2D tex;
uniform int step;


void main()
{
    if(step <= 60) {
      /* if(gl_FragCoord.x < 100){ */
        outColor = vec4(0.5, 0.0, 0.0 , 1.0);
      /* } else { */
      /*   outColor = vec4(0.0, 0.0, 0.0 , 1.0); */
      /* } */
    } else {
      /* float pix_width_x = 1.0/1000.0; */
      /* float pix_width_y = 1.0/1000.0; */

      outColor = texture(tex, tex_position_out);
      /* vec4 left = texture(tex, vec2(tex_position_out.x-pix_width_x, tex_position_out.y)); */
      /* if(left.x > 0.4) { */
      /* outColor = vec4(outColor.x, outColor.y, 1.0 , 1.0); */ 
      /* } */
    }
}
