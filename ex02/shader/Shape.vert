#version 410 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec3 vNormal;

out vec3 objectColor;

uniform mat4 modelMatrix;
uniform mat4 mvpMatrix;
uniform mat4 normalMatrix;

void main()
{
	gl_Position = mvpMatrix * vec4(vPosition, 1);

	// TODO: use the normal matrix


	//objectColor = vColor;

	// TODO: uncomment this line to display the normals as color
	objectColor = (mat3(normalMatrix) * vNormal);
	//objectColor = vNormal;
}

