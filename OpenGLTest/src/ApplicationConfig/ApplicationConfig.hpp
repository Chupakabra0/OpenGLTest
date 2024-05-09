#pragma once
#include "MeshGeneratorFactory/MaterialMeshGeneratorFactory/MaterialMeshGeneratorFactory.hpp"
#include "MeshGenerators/GenericMeshGenerators/CircleGenerator/CircleGenerator.hpp"
#include "MeshGenerators/GenericMeshGenerators/ConeGenerator/ConeGenerator.hpp"
#include "MeshGenerators/GenericMeshGenerators/CylinderGenerator/CylinderGenerator.hpp"
#include "MeshGenerators/GenericMeshGenerators/EllipseGenerator/EllipseGenerator.hpp"
#include "MeshGenerators/GenericMeshGenerators/IcosahedronGenerator/IcosahedronGenerator.hpp"
#include "MeshGenerators/GenericMeshGenerators/IcosphereGenerator/IcosphereGenerator.hpp"
#include "MeshGenerators/GenericMeshGenerators/ParallelepipedGenerator/ParallelepipedGenerator.hpp"
#include "MeshGenerators/GenericMeshGenerators/RectangleGenerator/RectangleGenerator.hpp"
#include "MeshGenerators/GenericMeshGenerators/TorusGenerator/TorusGenerator.hpp"
#include "MeshGenerators/GenericMeshGenerators/UVSphereGenerator/UVSphereGenerator.hpp"
#include "NlohmannUtils/NlohmannUtils.hpp"

#include <glm/gtc/constants.hpp>
#include <nlohmann/json.hpp>

#include <string>
#include <memory>

struct ApplicationConfig {
public:
    int         WINDOW_HEIGHT                           = 1920;
    int         WINDOW_WIDTH                            = 1080;
    glm::vec3   WINDOW_BACKGROUND                       = glm::zero<glm::vec3>();
    std::string WINDOW_NAME                             = "Default";
    glm::vec3   CAMERA_POSITION                         = glm::zero<glm::vec3>();
    glm::vec3   CAMERA_TARGET                           = glm::one<glm::vec3>();
    glm::vec3   CAMERA_AXIS_X                           = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3   CAMERA_AXIS_Y                           = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3   CAMERA_AXIS_Z                           = glm::vec3(0.0f, 0.0f, -1.0f);
    float       VIEWPORT_FOV                            = 90.0f;
    float       VIEWPORT_NEAR_Z                         = 0.1f;
    float       VIEWPORT_FAR_Z                          = 1.0f;
    glm::vec3   MATERIAL_AMBIENT                        = glm::vec3(1.0f);
    glm::vec3   MATERIAL_DIFFUSE                        = glm::vec3(1.0f);
    glm::vec3   MATERIAL_SPECULAR                       = glm::vec3(1.0f);
    float       MATERIAL_SHININESS                      = 1.0f;
    std::shared_ptr<IMeshGeneratorFactory> MESH_FACTORY = nullptr;
    std::shared_ptr<IMeshGenerator> MESH_GENERATOR      = nullptr;

    friend void from_json(const nlohmann::json& json, ApplicationConfig& config) {
        json.at("WINDOW_HEIGHT").get_to(config.WINDOW_HEIGHT);
        json.at("WINDOW_WIDTH").get_to(config.WINDOW_WIDTH);
        json.at("WINDOW_BACKGROUND").get_to(config.WINDOW_BACKGROUND);
        json.at("WINDOW_NAME").get_to(config.WINDOW_NAME);
        json.at("CAMERA_POSITION").get_to(config.CAMERA_POSITION);
        json.at("CAMERA_TARGET").get_to(config.CAMERA_TARGET);
        json.at("CAMERA_AXIS_X").get_to(config.CAMERA_AXIS_X);
        json.at("CAMERA_AXIS_Y").get_to(config.CAMERA_AXIS_Y);
        json.at("CAMERA_AXIS_Z").get_to(config.CAMERA_AXIS_Z);
        json.at("VIEWPORT_FOV").get_to(config.VIEWPORT_FOV);
        json.at("VIEWPORT_NEAR_Z").get_to(config.VIEWPORT_NEAR_Z);
        json.at("VIEWPORT_FAR_Z").get_to(config.VIEWPORT_FAR_Z);
        json.at("MATERIAL_AMBIENT").get_to(config.MATERIAL_AMBIENT);
        json.at("MATERIAL_DIFFUSE").get_to(config.MATERIAL_DIFFUSE);
        json.at("MATERIAL_DIFFUSE").get_to(config.MATERIAL_DIFFUSE);
        json.at("MATERIAL_SHININESS").get_to(config.MATERIAL_SHININESS);

        config.MESH_FACTORY = std::make_shared<MaterialMeshGeneratorFactory>(
            MaterialInstance {
                .ambient   = config.MATERIAL_AMBIENT,
                .diffuse   = config.MATERIAL_DIFFUSE,
                .specular  = config.MATERIAL_SPECULAR,
                .shininess = config.MATERIAL_SHININESS
            }
        );

        std::string meshName = json.at("MESH_NAME").get<std::string>();
        std::ranges::transform(meshName, meshName.begin(), toupper);

        static const std::unordered_map<std::string, std::function<std::shared_ptr<IMeshGenerator>()>> meshGeneratorsMap {
            std::make_pair("CIRCLE", [&json]() -> std::shared_ptr<IMeshGenerator> {
                return std::make_shared<CircleGenerator>(
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("RADIUS").get<float>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("SEGMENTS").get<int>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("ORIGIN").get<glm::vec3>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("COLOR").get<glm::vec3>()
                );
            }),
            std::make_pair("CONE", [&json]() -> std::shared_ptr<IMeshGenerator> {
                return std::make_shared<ConeGenerator>(
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("HEIGHT").get<float>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("RADIUS").get<float>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("SEGMENTS").get<int>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("SLICES").get<int>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("ORIGIN").get<glm::vec3>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("COLOR").get<glm::vec3>()
                );
            }),
            std::make_pair("CYLINDER", [&json]() -> std::shared_ptr<IMeshGenerator> {
                return std::make_shared<CylinderGenerator>(
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("HEIGHT").get<float>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("RADIUS").get<float>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("SEGMENTS").get<int>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("SLICES").get<int>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("ORIGIN").get<glm::vec3>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("COLOR").get<glm::vec3>()
                );
            }),
            std::make_pair("ELLIPSE", [&json]() -> std::shared_ptr<IMeshGenerator> {
                return std::make_shared<EllipseGenerator>(
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("A").get<float>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("B").get<float>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("SEGMENTS").get<int>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("ORIGIN").get<glm::vec3>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("COLOR").get<glm::vec3>()
                );
            }),
            std::make_pair("ICOSAHEDRON", [&json]() -> std::shared_ptr<IMeshGenerator> {
                return std::make_shared<IcosahedronGenerator>(
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("RADIUS").get<float>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("ORIGIN").get<glm::vec3>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("COLOR").get<glm::vec3>()
                );
            }),
            std::make_pair("ICOSPHERE", [&json]() -> std::shared_ptr<IMeshGenerator> {
                return std::make_shared<IcosphereGenerator>(
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("RADIUS").get<float>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("ITERATIONS").get<int>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("ORIGIN").get<glm::vec3>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("COLOR").get<glm::vec3>()
                );
            }),
            std::make_pair("PARALLELEPIPED", [&json]() -> std::shared_ptr<IMeshGenerator> {
                return std::make_shared<ParallelepipedGenerator>(
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("HEIGHT").get<float>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("WIDTH").get<float>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("DEPTH").get<float>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("ORIGIN").get<glm::vec3>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("COLOR").get<glm::vec3>()
                );
            }),
            std::make_pair("RECTANGLE", [&json]() -> std::shared_ptr<IMeshGenerator> {
                return std::make_shared<RectangleGenerator>(
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("HEIGHT").get<float>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("WIDTH").get<float>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("ORIGIN").get<glm::vec3>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("COLOR").get<glm::vec3>()
                );
            }),
            std::make_pair("TORUS", [&json]() -> std::shared_ptr<IMeshGenerator> {
                return std::make_shared<TorusGenerator>(
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("INNER_RADIUS").get<float>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("OUTER_RADIUS").get<float>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("SLICES").get<int>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("LOOPS").get<int>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("ORIGIN").get<glm::vec3>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("COLOR").get<glm::vec3>()
                );
            }),
            std::make_pair("UV-SPHERE", [&json]() -> std::shared_ptr<IMeshGenerator> {
                return std::make_shared<UVSphereGenerator>(
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("RADIUS").get<float>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("SLICES").get<int>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("STACKS").get<int>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("ORIGIN").get<glm::vec3>(),
                    json.at("MESH_PARAMS").get<nlohmann::json>().at("COLOR").get<glm::vec3>()
                );
            }),
        };

        config.MESH_GENERATOR = meshGeneratorsMap.contains(meshName) ? meshGeneratorsMap.at(meshName)() : nullptr;
    }
};
