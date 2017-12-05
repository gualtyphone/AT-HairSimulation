#version 120


uniform sampler2D diffuse;

varying vec4 color0;
varying vec3 normal0;
//uniform vec3 lightdirection;

void main()
{
	gl_FragColor = color0;// * dot(-vec3(0, 0, 1), normal0);
}
