#pragma once
#include "MeshGenerators/MeshGenerator.hpp"
#include "MeshGeneratorFactory/IMeshGeneratorFactory.hpp"

#include <glm/gtc/constants.hpp>

#include <string>
#include <memory>

struct ApplicationConfig {
public:
    int         WINDOW_HEIGHT                           = 1920;
    int         WINDOW_WIDTH                            = 1080;
    std::string WINDOW_NAME                             = "Default";
    glm::vec3   CAMERA_POSITION                         = glm::zero<glm::vec3>();
    glm::vec3   CAMERA_TARGET                           = glm::one<glm::vec3>();
    glm::vec3   CAMERA_AXIS_X                           = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3   CAMERA_AXIS_Y                           = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3   CAMERA_AXIS_Z                           = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec2   VIEWPORT_TOP_LEFT                       = glm::zero<glm::vec2>();
    glm::vec2   VIEWPORT_BOTTOM_RIGHT                   = glm::vec2(1080.0f, 1920.0f);
    float       VIEWPORT_FOV                            = 90.0f;
    float       VIEWPORT_NEAR_Z                         = 0.1f;
    float       VIEWPORT_FAR_Z                          = 1.0f;
    glm::vec3   MATERIAL_AMBIENT                        = glm::vec3(0.25, 0.148, 0.06475);
    glm::vec3   MATERIAL_DIFFUSE                        = glm::vec3(0.4, 0.2368, 0.1036);
    glm::vec3   MATERIAL_SPECULAR                       = glm::vec3(0.774597, 0.458561, 0.200621);
    //glm::vec3   MATERIAL_AMBIENT                           = glm::vec3(0.05375, 0.05, 0.06625);
    //glm::vec3   MATERIAL_DIFFUSE                           = glm::vec3(0.18275, 0.17, 0.22525);
    //glm::vec3   MATERIAL_SPECULAR                          = glm::vec3(0.332741, 0.328634, 0.346435);
    float       MATERIAL_SHININESS                      = 25.6f;
    //float       MATERIAL_SHININESS                      = 38.4f;
    std::shared_ptr<IMeshGeneratorFactory> MESH_FACTORY = nullptr;
    std::shared_ptr<IMeshGenerator> MESH_GENERATOR      = nullptr;
};
