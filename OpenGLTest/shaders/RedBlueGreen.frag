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

    vec4 nrml     = u_isFlat ? flatNormal : smoothNormal;
    float maxNrml = max(abs(nrml.x), max(abs(nrml.y), abs(nrml.z)));
    
    if (maxNrml == abs(nrml.x)) {
        gl_FragColor = vec4(nrml.x > 0.0 ? 1.0 : 0.5, 0.0, 0.0, 1.0);
    }
    else if (maxNrml == abs(nrml.y)) {
        gl_FragColor = vec4(0.0, nrml.y > 0.0 ? 1.0 : 0.5, 0.0, 1.0);
    }
    else if (maxNrml == abs(nrml.z)) {
        gl_FragColor = vec4(0.0, 0.0, nrml.z > 0.0 ? 1.0 : 0.5, 1.0);
    }
    else {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
}
