#version 460 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 smoothNormal;
// layout(location = 3) in vec2 vertexTexture;
// layout(location = 4) in vec4 clippedNormal;
layout(location = 3) in vec3 vertexMaterialAmbient;
layout(location = 4) in vec3 vertexMaterialDiffuse;
layout(location = 5) in vec3 vertexMaterialSpecular;
layout(location = 6) in float vertexMaterialShininess;
layout(location = 7) in vec3 fragmentWorldPosition;
layout(location = 8) in mat4 worldMatrix;

uniform bool u_is_flat;
uniform bool u_is_phong_specular;
uniform vec3 u_camera_position;

uniform bool u_directional_is_enabled;
uniform bool u_directional_is_ambient;
uniform bool u_directional_is_diffuse;
uniform bool u_directional_is_specular;
uniform vec3 u_directional_light_direction;
uniform vec3 u_directional_light_ambient_color;
uniform vec3 u_directional_light_diffuse_color;
uniform vec3 u_directional_light_specular_color;
uniform float u_directional_light_ambient_intensity;
uniform float u_directional_light_diffuse_intensity;
uniform float u_directional_light_specular_intensity;

uniform bool u_point_is_enabled;
uniform bool u_point_is_ambient;
uniform bool u_point_is_diffuse;
uniform bool u_point_is_specular;
uniform vec3 u_point_light_position;
uniform vec3 u_point_light_ambient_color;
uniform vec3 u_point_light_diffuse_color;
uniform vec3 u_point_light_specular_color;
uniform float u_point_light_constant_attenuation;
uniform float u_point_light_linear_attenuation;
uniform float u_point_light_quadratic_attenuation;
uniform float u_point_light_ambient_intensity;
uniform float u_point_light_diffuse_intensity;
uniform float u_point_light_specular_intensity;

uniform bool u_spot_is_enabled;
uniform bool u_spot_is_ambient;
uniform bool u_spot_is_diffuse;
uniform bool u_spot_is_specular;
uniform vec3 u_spot_light_position;
uniform vec3 u_spot_light_direction;
uniform vec3 u_spot_light_ambient_color;
uniform vec3 u_spot_light_diffuse_color;
uniform vec3 u_spot_light_specular_color;
uniform float u_spot_light_constant_attenuation;
uniform float u_spot_light_linear_attenuation;
uniform float u_spot_light_quadratic_attenuation;
uniform float u_spot_light_inner_cutoff;
uniform float u_spot_light_outer_cutoff;
uniform float u_spot_light_exponent;
uniform float u_spot_light_ambient_intensity;
uniform float u_spot_light_diffuse_intensity;
uniform float u_spot_light_specular_intensity;

float saturate(float value) {
    return clamp(value, 0.0, 1.0);
}

float getSpecularStrength(vec3 n, vec3 l, vec3 v) {
    return u_is_phong_specular ?
        pow(saturate(dot(normalize(v), normalize(reflect(normalize(-l), normalize(n))))), vertexMaterialShininess) :
        pow(saturate(dot(normalize(n), normalize(l + v))), vertexMaterialShininess);
}

vec3 calcDirectionalLighting(vec3 normal) {
    // AMBIENT
    vec3 ambientComponent = vec3(0.0);
    if (u_directional_is_ambient) {
        vec3 ambientColor = u_directional_light_ambient_color;
        ambientComponent  = u_directional_light_ambient_intensity * ambientColor * vertexMaterialAmbient;
    }

    // DIFFUSE
    vec3 diffuseComponent = vec3(0.0);
    vec3 reverseLightDir  = normalize(-u_directional_light_direction);
    if (u_directional_is_diffuse) {
        vec3 diffuseColor   = u_directional_light_diffuse_color;
        float diffuseFactor = saturate(dot(reverseLightDir, normal));
        diffuseComponent    = u_directional_light_diffuse_intensity * diffuseFactor * diffuseColor * vertexMaterialDiffuse;
    }

    // SPECULAR
    vec3 specularComponent = vec3(0.0);
    if (u_directional_is_specular) {
        vec3 specularColor   = u_directional_light_specular_color;
        vec3 viewDirection   = normalize(u_camera_position - fragmentWorldPosition);
        float diffuseFactor  = saturate(dot(reverseLightDir, normal));
        float specularFactor = diffuseFactor == 0.0 ? 0.0 : getSpecularStrength(normal, reverseLightDir, viewDirection);
        specularComponent    = u_directional_light_specular_intensity * specularFactor * specularColor * vertexMaterialSpecular;
    }

    return ambientComponent + diffuseComponent + specularComponent; 
}

vec3 calcPointLighting(vec3 normal) {
    float lightDistance     = length(u_point_light_position - fragmentWorldPosition);
    float attenuationFactor = 1.0 / (u_point_light_constant_attenuation + u_point_light_linear_attenuation * lightDistance + u_point_light_quadratic_attenuation * pow(lightDistance, 2.0));

    // AMBIENT
    vec3 ambientComponent = vec3(0.0);
    if (u_point_is_ambient) {
        vec3 ambientColor = u_point_light_ambient_color;
        ambientComponent  = u_point_light_ambient_intensity * ambientColor * vertexMaterialAmbient;
    }

    // DIFFUSE
    vec3 diffuseComponent = vec3(0.0);
    vec3 reverseLightDir  = normalize(u_point_light_position - fragmentWorldPosition);
    if (u_point_is_diffuse) {
        vec3 diffuseColor   = u_point_light_diffuse_color;
        float diffuseFactor = saturate(dot(reverseLightDir, normal));
        diffuseComponent    = attenuationFactor * u_point_light_diffuse_intensity * diffuseFactor * diffuseColor * vertexMaterialDiffuse;
    }

    // SPECULAR
    vec3 specularComponent = vec3(0.0);
    if (u_point_is_specular) {
        vec3 specularColor   = u_point_light_specular_color;
        vec3 viewDirection   = normalize(u_camera_position - fragmentWorldPosition);
        float diffuseFactor  = saturate(dot(reverseLightDir, normal));
        float specularFactor = diffuseFactor == 0.0 ? 0.0 : getSpecularStrength(normal, reverseLightDir, viewDirection);
        specularComponent    = attenuationFactor * u_point_light_specular_intensity * specularFactor * specularColor * vertexMaterialSpecular;
    }

    return ambientComponent + diffuseComponent + specularComponent; 
}

vec3 calcSpotLighting(vec3 normal) {
    vec3 positionToLight = u_spot_light_position - fragmentWorldPosition;
    float lightDistance  = length(positionToLight);
    positionToLight      = normalize(positionToLight);

    float attenuationFactor = 1.0 / (u_spot_light_constant_attenuation + u_spot_light_linear_attenuation * lightDistance + u_spot_light_quadratic_attenuation * pow(lightDistance, 2.0)); 

    vec3 ambientComponent  = vec3(0.0);
    if (u_spot_is_ambient) {
        vec3 ambientColor = u_spot_light_ambient_color;
        ambientComponent  =  u_spot_light_ambient_intensity * ambientColor * vertexMaterialAmbient;
    }

    float thetaCos = dot(normalize(positionToLight), normalize(-u_spot_light_direction));
    float outerCos = cos(u_spot_light_outer_cutoff);
    float innerCos = cos(u_spot_light_inner_cutoff);

    if (thetaCos > outerCos)  {   
        if (innerCos > outerCos) {    
            float epsilon      = innerCos - outerCos;
            attenuationFactor *= pow(saturate((thetaCos - outerCos) / epsilon), u_spot_light_exponent); 
        }
        
        // do lighting calculations
        vec3 diffuseComponent  = vec3(0.0);
        if (u_spot_is_diffuse) {
            vec3 diffuseColor  = u_spot_light_diffuse_color;
            float diffuseFactor = saturate(dot(normalize(positionToLight), normalize(normal)));
            diffuseComponent = attenuationFactor * diffuseFactor * u_spot_light_diffuse_intensity * diffuseColor * vertexMaterialDiffuse;
        }

        vec3 specularComponent = vec3(0.0);
        if (u_spot_is_specular) {
            vec3 specularColor   = u_spot_light_specular_color;
            vec3 viewDirection   = normalize(u_camera_position - fragmentWorldPosition);
            // vec3 reflection      = reflect(normalize(-positionToLight), normalize(normal));
            float diffuseFactor  = saturate(dot(normalize(positionToLight), normalize(normal)));
            float specularFactor = diffuseFactor == 0.0 ? 0.0 : getSpecularStrength(normal, positionToLight, viewDirection);
            specularComponent    = attenuationFactor * specularFactor * u_spot_light_specular_intensity * specularColor * vertexMaterialSpecular;
        }

        return ambientComponent + diffuseComponent + specularComponent;
    }
    else { 
        // else, use ambient light so scene isn't completely dark outside the spotlight.
        return ambientComponent;
    }
}

void main() {
    // Calculate flat normal
    vec3 flatNormal = normalize(cross(dFdx(vertexPosition.xyz), dFdy(vertexPosition.xyz)));
    if (!gl_FrontFacing) {
        flatNormal = -flatNormal;
    }

    vec3 localNormal = u_is_flat ? flatNormal : smoothNormal;
    vec3 worldNormal = vec3(worldMatrix * vec4(localNormal, 0.0));

    vec3 directional = vec3(0.0);
    if (u_directional_is_enabled) {
        directional = calcDirectionalLighting(localNormal);
    }

    vec3 point = vec3(0.0);
    if (u_point_is_enabled) {
        point = calcPointLighting(worldNormal);
    }

    vec3 specular = vec3(0.0);
    if (u_spot_is_enabled) {
        specular = calcSpotLighting(worldNormal);
    }

    vec3 lightingColor = clamp(directional + point + specular, 0.0, 1.0);
    vec3 finalColor    = lightingColor * vertexColor;

    gl_FragColor = vec4(finalColor, 1.0);
}

// void main() {
//     // Calculate flat normal
//     vec3 flatNormal = normalize(cross(dFdx(vertexPosition.xyz), dFdy(vertexPosition.xyz)));
//     if (!gl_FrontFacing) {
//         flatNormal = -flatNormal;
//     }

//     vec3 normal = u_is_flat ? flatNormal : smoothNormal;

//     // DIRECTIONAL LIGHTING

//     // Ambient lighting
//     vec3 ambientDirectionalColor = u_directional_light_ambient;
//     vec3 ambientDirectionalFinal = ambientDirectionalColor * vertexMaterialAmbient;

//     // Diffuse lighting
//     vec3 diffuseDirectionalColor     = u_directional_light_diffuse;
//     vec3 lightDirectionalDirection   = normalize(-u_directional_light_direction);
//     float diffuseDirectionalStrength = saturate(dot(normal, lightDirectionalDirection));
//     vec3 diffuseDirectionalFinal     = diffuseDirectionalStrength * diffuseDirectionalColor * vertexMaterialDiffuse;

//     // Specular lighting
//     vec3 specularDirectionalColor     = u_directional_light_specular;
//     vec3 viewDirectionalDirection     = normalize(u_camera_position - fragmentPosition);
//     float specularDirectionalStrength = getSpecularStrength(normal, lightDirectionalDirection, viewDirectionalDirection);
//     vec3 specularDirectionalFinal     = specularDirectionalStrength * specularDirectionalColor * vertexMaterialSpecular;

//     // Declaration of the result variable
//     vec3 lightingColor = vec3(0.0);

//     if (u_directional_is_enabled) {
//         if (u_directional_is_ambient) {
//             lightingColor += ambientDirectionalFinal;
//         }
//         if (u_directional_is_diffuse) {
//             lightingColor += diffuseDirectionalFinal;
//         }
//         if (u_directional_is_specular) {
//             lightingColor += specularDirectionalFinal;
//         }
//     }

//     // POINT LIGHTING

//     float distancePoint            = length(fragmentPosition - u_point_light_position);
//     float distancePointCoefficient = u_point_light_constant_attenuation + u_point_light_linear_attenuation * distancePoint + u_point_light_quadratic_attenuation * pow(distancePoint, 2.0);

//     // Ambient lighting
//     vec3 ambientPointColor = u_point_light_ambient;
//     vec3 ambientPointFinal = ambientPointColor / distancePointCoefficient * vertexMaterialAmbient;

//     // Diffuse lighting
//     vec3 diffusePointColor         = u_point_light_diffuse;
//     vec3 lightPointDirection       = normalize(u_point_light_position - fragmentPosition);
//     float diffusePointStrength     = saturate(dot(normal, lightPointDirection));
//     vec3 diffusePointFinal         = distancePointCoefficient != 0.0 ?
//         diffusePointStrength / distancePointCoefficient * diffusePointColor * vertexMaterialDiffuse :
//         vec3(0.0);

//     // Specular lighting
//     vec3 specularPointColor     = u_point_light_specular;
//     vec3 viewPointDirection     = normalize(u_camera_position - fragmentPosition);
//     float specularPointStrength = getSpecularStrength(normal, lightPointDirection, viewPointDirection);
//     vec3 specularPointFinal     = distancePointCoefficient != 0.0 ? 
//         specularPointStrength / distancePointCoefficient  * specularPointColor * vertexMaterialSpecular :
//         vec3(0.0);

//     if (u_point_is_enabled) {
//         if (u_point_is_ambient) {
//             lightingColor += ambientPointFinal;
//         }
//         if (u_point_is_diffuse) {
//             lightingColor += diffusePointFinal;
//         }
//         if (u_point_is_specular) {
//             lightingColor += specularPointFinal;
//         }
//     }

//     // SPOTLIGHT LIGHTING

//     float theta = dot(normalize(-u_spot_light_direction), normalize(u_spot_light_position - fragmentPosition));

//     if (theta > cos(u_spot_light_cutoff)) {
//         float distanceSpot            = length(u_spot_light_position - fragmentPosition);
//         float distanceSpotCoefficient = u_spot_light_constant_attenuation + u_spot_light_linear_attenuation * distanceSpot + u_spot_light_quadratic_attenuation * pow(distanceSpot, 2.0);
        
//         // Ambient lighting
//         vec3 ambientSpotColor = u_spot_light_ambient;
//         vec3 ambientSpotFinal = ambientSpotColor * vertexMaterialAmbient;

//         // Diffuse lighting
//         vec3 diffuseSpotColor     = u_spot_light_diffuse;
//         vec3 lightSpotDirection   = normalize(-u_spot_light_direction);
//         float diffuseSpotStrength = saturate(dot(normal, lightSpotDirection));
//         vec3 diffuseSpotFinal     = pow(diffuseSpotStrength, 1.0) / distanceSpotCoefficient * diffuseSpotColor * vertexMaterialDiffuse;

//         // Specular lighting
//         vec3 specularSpotColor     = u_spot_light_specular;
//         vec3 viewSpotDirection     = normalize(u_camera_position - fragmentPosition);
//         float specularSpotStrength = getSpecularStrength(normal, lightSpotDirection, viewSpotDirection);
//         vec3 specularSpotFinal     = pow(specularSpotStrength, 1.0)  / distanceSpotCoefficient * specularSpotColor * vertexMaterialSpecular;

//         if (u_spot_is_enabled) {
//             if (u_spot_is_ambient) {
//                 lightingColor += ambientSpotFinal;
//             }
//             if (u_spot_is_diffuse) {
//                 lightingColor += diffuseSpotFinal;
//             }
//             if (u_spot_is_specular) {
//                 lightingColor += specularSpotFinal;
//             }
//         }
//     }

//     vec3 finalColor = lightingColor * vertexColor;

//     gl_FragColor = vec4(finalColor, 1.0);
// }
