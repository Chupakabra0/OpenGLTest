#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 vertexNormal;
layout(location = 3) in vec2 texture;
layout(location = 4) in vec3 ambient;
layout(location = 5) in vec3 diffuse;
layout(location = 6) in vec3 specular;
layout(location = 7) in float shininess;

layout(location = 0) out vec3 vertexPosition;
layout(location = 1) out vec3 vertexColor;
layout(location = 2) out vec3 smoothNormal;
// layout(location = 3) out vec2 vertexTexture;
// layout(location = 4) out vec4 clippedNormal;
layout(location = 3) out vec3 vertexMaterialAmbient;
layout(location = 4) out vec3 vertexMaterialDiffuse;
layout(location = 5) out vec3 vertexMaterialSpecular;
layout(location = 6) out float vertexMaterialShininess;
layout(location = 7) out vec3 fragmentWorldPosition;
layout(location = 8) out mat4 worldMatrix;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

void main() {
    gl_Position             = u_proj * u_view * u_model * vec4(position, 1.0);
    vertexPosition          = position;
    vertexColor             = color;
    smoothNormal            = vertexNormal;
    // vertexTexture           = texture;
    // clippedNormal           = u_proj * vec4(transpose(inverse(mat3(u_view * u_model))) * vertexNormal, 0.0);
    vertexMaterialAmbient   = ambient;
    vertexMaterialDiffuse   = diffuse;
    vertexMaterialSpecular  = specular;
    vertexMaterialShininess = shininess;
    fragmentWorldPosition   = vec3(u_model * vec4(position, 1.0));
    worldMatrix             = mat4(u_model);
}
