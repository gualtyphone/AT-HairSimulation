#version 330

in highp vec4 color0;
in highp vec3 direction0;

uniform vec3 lightDirection;

out highp vec4 output;

void main()
{
	output = color0 * (1- dot(lightDirection, direction0));
}
