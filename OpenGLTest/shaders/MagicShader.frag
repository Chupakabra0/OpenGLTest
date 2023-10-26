#version 460 core

layout(location = 3) in vec2 vertexTexture;

uniform float u_time;
uniform sampler2D u_texture;
uniform vec3 u_rgb;
uniform vec2 u_resolution;

vec3 pallete(float t, vec3 a, vec3 b, vec3 c, vec3 d) {
    const float magicValue = 6.28318;
    return a + b * cos(magicValue * (c * t + d));
}

void main() {
    // Normalized pixel coordinates (from -1 to 1), center it and fix aspect ratio
    vec2 uv = (gl_FragCoord.xy * 2.0 - u_resolution.xy) / u_resolution.y;
    vec2 uv0 = uv;

    // Result color var
    vec4 finalColor = vec4(vec3(0.0), 1.0);
    
    for (int i = 0; i < 3; ++i) {
        // Fract pattern
        uv = fract(uv * 1.25) - 0.5;

        // Calculate vector's length from origin of current frac to current pixel
        float lengthUV = length(uv);

        // Calculate vector's length from origin of system (0,0) to current pixel
        float lengthUV0 = length(uv0);

        // Calculate shape
        float d = lengthUV * exp(-lengthUV0);
        d = abs(sin(d * 8.0 - 0.4 * (float(i) + u_time)) / 8.0);
        d = pow(100.0 * d, -1.2);

        // Calculate color from my pallete
        vec3 paletteColor = pallete(
            lengthUV0 + 0.4 * (float(i) + u_time),
            vec3(0.5),
            vec3(0.5),
            vec3(1.0),
            (vec3(0.5, 0.25, 0.125) + u_rgb) / 2.0
        );

        // Accumulate color
        finalColor += vec4(paletteColor * d, 0.0);
    }

    // Calc texture color
    // [-1, 1] -> [0.4, 1]
    float textureAlpha = (sin((u_time + 2.25 * acos(-1.0)) * 2.0) + 1.0) * 0.3 + 0.4;
    vec4 textureColor = mix(
        vec4(u_rgb, 1.0),
        texture(u_texture, vertexTexture),
        textureAlpha
    );

    // Output to screen
     gl_FragColor = mix(finalColor, textureColor, 0.25);
}