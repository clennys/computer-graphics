#version 410 core

/* TODO Task 2 update your vertex shader so that...
 *      ...it has texture samplers declared
 *      ...it outputs a diffuse texture as diffuse color
 *      ...it uses a light map to modify the specular highlights
 */

in vec3 objectColor;

/* TODO Task 2 Add the required input data */
in vec2 fTexCoords;
// END TODO

/* TODO Task 2 declare texture samplers here */
uniform sampler2D cubetex;

// END TODO

/* TODO Task 2 fill these structs with values from outside the shader similar
 *      to your matric variables
 */

uniform vec3 lightPos;
uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform vec3 camPos;
uniform float shiny;

// TODO END

out vec3 color;

void main()
{
	color = objectColor;

	/* TODO Task 2 add the source code to do phong shading but with the values of the color, normal and specular texture.
	 *      Remember that you can also use the color output for debugging of the
	 *      texture maps and texture coordinates in case that you face troubles.
	 */

	
	 color =  diffuse * texture(cubetex, fTexCoords).rgb;
 
	// TODO END
}

