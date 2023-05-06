#version 410 core

/* TODO Task 1 update your vertex shader so that...
 *      ...it emits the color for phong illumination
 *      ...it emits the color from the vertex shader in case you do gouraud shading there
 */

in vec3 objectColor;
in vec3 normal;
in vec3 worldPos;

/* TODO Task 1 fill these structs with values from outside the shader similar
 *      to your matric variables
 */

uniform vec3 lightPos;
uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform vec3 camPos;

uniform float shiny;

// END TODO

uniform bool gouraudShading;

// Ouput data
out vec3 color;

void main()
{
    // Output color = color specified in the vertex shader,
    // interpolated between all 3 surrounding vertices
    color = objectColor;

    if(!gouraudShading)
    {
        // TODO Task 1 add there code for phong lighting
		vec3 lightDirection = normalize(lightPos - worldPos);
		vec3 viewDirection = normalize(camPos - worldPos);
		vec3 normNormal = normalize(normal);
		vec3 reflectionDirection = reflect(-lightDirection, normNormal);

		vec3 ambient_shader = ambient;

		vec3 diffuse_shader = diffuse * max(dot(normNormal, lightDirection), 0.0);

		vec3 specular_shader = specular * pow(max(dot(viewDirection, reflectionDirection), 0.0), shiny);

		color = (ambient_shader + diffuse_shader + specular_shader) * objectColor;
        // END TODO
    }
}

