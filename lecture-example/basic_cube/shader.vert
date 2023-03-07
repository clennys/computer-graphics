#version 330

// uniform shader block variables
layout(std140) uniform settingsBlock
{
  bool wire;
} settings;

// uniform variables
uniform mat4 viewMatrix, projMatrix;
uniform vec4 ext_color;

// input and output variables
in vec3 in_position;
in vec3 in_color;
in vec3 in_normal;

out vec4 v_color;


void main()
{
  // model-view camera transform
  vec4 p = viewMatrix * vec4(in_position, 1.0);
  
  //set base color
  vec4 color = vec4(in_color, 1.0);

  if (settings.wire)
	v_color = ext_color;
  else
	v_color = color;

  gl_Position = projMatrix * p;
}
