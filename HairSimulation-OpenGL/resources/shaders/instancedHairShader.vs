#version 120

attribute vec3 position;
attribute vec3 instancePos;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4((position + instancePos), 1.0);

}