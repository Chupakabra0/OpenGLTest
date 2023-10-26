#version 460 core

layout(location = 1) in vec4 vertexColor;

void main() {
    gl_FragColor = vertexColor;
}
