#version 460 core

layout(location = 0) in vec4 vertexPosition;
layout(location = 2) in vec4 smoothNormal;

uniform bool u_isFlat;

float normalizeValue(float value, vec2 inputRange, vec2 outputRange) {
    float minX = inputRange.x;
    float maxX = inputRange.y;
    float minY = outputRange.x;
    float maxY = outputRange.y;

    return (value - minX) * (maxY - minY) / (maxX - minX) + minY;
}

void main() {
    vec4 flatNormal = vec4(normalize(cross(dFdx(vertexPosition.xyz / vertexPosition.w), dFdy(vertexPosition.xyz / vertexPosition.w))), 0.0);
    if (!gl_FrontFacing) {
        flatNormal = -flatNormal;
    }

    vec4 nrml = u_isFlat ? flatNormal : smoothNormal;

    gl_FragColor = vec4(
        normalizeValue(nrml.x, vec2(-1.0, 1.0), vec2(1.0, 0.0)),
        normalizeValue(nrml.y, vec2(-1.0, 1.0), vec2(1.0, 0.0)),
        normalizeValue(nrml.z, vec2(-1.0, 1.0), vec2(1.0, 0.0)),
        1.0
    );
}
