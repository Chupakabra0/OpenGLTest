#version 460 core
layout(triangles) in;
layout(line_strip, max_vertices = 8) out;

layout(location = 4) in vec4 clippedNormals[];

float MAGNITUDE = 50.0;

void GenerateNormal(int index) {
    gl_Position = gl_in[index].gl_Position;
    EmitVertex();
    gl_Position += vec4(clippedNormals[index].xyz, 0.0) * MAGNITUDE;
    EmitVertex();
    EndPrimitive();
}

void GenerateFaceNormal() {
    gl_Position = gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position;
    EmitVertex();
    gl_Position += vec4((clippedNormals[0].xyz + clippedNormals[1].xyz + clippedNormals[2].xyz) / 3.0, 0.0) * MAGNITUDE;
    EmitVertex();
    EndPrimitive();
}

void main() {
    for (int i = 0; i < 3; ++i) {
        GenerateNormal(i);
    }

    // GenerateFaceNormal();
}
