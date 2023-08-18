#version 330 core

layout (location = 0) in vec4 u_Position;

uniform mat4 u_ViewPorjectionMatrix;
uniform mat4 u_ModalViewMatrix = mat4(1.0f);

void main()
{
    gl_Position = u_ViewPorjectionMatrix * u_ModalViewMatrix * u_Position;
};
