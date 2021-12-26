#version 330 core
in vec2 position;
in vec3 color;

out vec3 vertex_color;

//this wont work since center also needs to be periodic boundary conditioned
/* vec2 periodic_boundary_condition(vec2 position) { */
/*   if(position.x > 1.0) { */
/*     position.x = position.x - 1; */
/*   }else if (position.x < -1.0) { */
/*     position.x = position.x + 1; */
/*   } */

/*   if(position.y > 1.0) { */
/*     position.y = position.y - 1; */
/*   }else if (position.y < -1.0) { */
/*     position.y = position.y + 1; */
/*   } */
/*   return position; */
/* } */

void main()
{
  gl_Position = vec4(position, 0.0, 1.0);
  vertex_color = color;
}
