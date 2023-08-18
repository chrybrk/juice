#version 330 core

layout (location = 0) out vec4 OutColor;

uniform vec3 u_Color;

void main()
{
	OutColor = vec4(u_Color.rgb, 1.0f);
}
