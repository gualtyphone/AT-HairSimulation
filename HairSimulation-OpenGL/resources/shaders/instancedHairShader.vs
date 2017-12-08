#version 330 

in vec3 position;
in vec3 instancePos;
in vec4 instanceColor;
in vec3 direction;

out vec4 color0;
out vec3 direction0;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4((position + instancePos), 1.0);
	direction0 = normalize(direction);//normalize((transform * vec4(normal, 0.0)).xyz);
	color0 = instanceColor;
}