#version 120

attribute vec3 position;
attribute vec3 instancePos;
attribute vec4 instanceColor;
attribute vec3 normal;

varying vec4 color0;
varying vec3 normal0;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4((position + instancePos), 1.0);
	normal0 = normalize((transform * vec4(normal, 0.0)).xyz);
	color0 = instanceColor;
}