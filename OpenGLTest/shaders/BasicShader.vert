#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 vertexNormal;
layout(location = 3) in vec2 texture;

layout(location = 0) out vec4 vertexPosition;
layout(location = 1) out vec4 vertexColor;
layout(location = 2) out vec4 smoothNormal;
layout(location = 3) out vec2 vertexTexture;
layout(location = 4) out vec4 clippedNormal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

void main() {
    gl_Position    = u_proj * u_view * u_model * vec4(position, 1.0);
    vertexPosition = vec4(position, 1.0);
    vertexColor    = vec4(color, 1.0);
    smoothNormal   = vec4(vertexNormal, 0.0);
    vertexTexture  = texture;
    clippedNormal  = u_proj * vec4(transpose(inverse(mat3(u_view * u_model))) * vertexNormal, 0.0);
}
