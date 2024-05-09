#pragma once
#include "ApplicationConfig/ApplicationConfig.hpp"
#include "RendererInstance/RendererInstance.hpp"
#include "ImguiWrapper/ImguiWrapper.hpp"
#include "WindowInstance/WindowInstance.hpp"
#include "CameraInstance/CameraInstance.hpp"
#include "ViewportInstance/ViewportInstance.hpp"
#include "ShaderProgram/ShaderProgram.hpp"
#include "LightInstance/LightInstance.hpp"
#include "LogLevel/LogLevel.hpp"

#include <unordered_map>

#include "MaterialInstance/MaterialInstance.h"

constexpr bool IsDebug() {
    #if defined(_DEBUG)
        return true;
    #else
        return false;
    #endif
}

struct Time {
public:
    float totalTimeInSeconds{};
    size_t hours{};
    size_t minutes{};
    size_t seconds{};
    size_t milliseconds{};
};

struct DirectionalLightParams {
public:
    glm::vec3 lightDirection = glm::vec3(1.0f);
    glm::vec3 ambient        = glm::vec3(1.0f);
    glm::vec3 diffuse        = glm::vec3(1.0f);
    glm::vec3 specular       = glm::vec3(1.0f);
    float ambientIntensity   = 1.0f;
    float diffuseIntensity   = 1.0f;
    float specularIntensity  = 1.0f;
    bool isAmbient           = true;
    bool isDiffuse           = true;
    bool isSpecular          = true;
    bool isEnable            = false;
};

struct PointLightParams {
public:
    glm::vec3 lightPosition    = glm::vec3(-10.0f);
    glm::vec3 ambient          = glm::vec3(1.0f);
    glm::vec3 diffuse          = glm::vec3(1.0f);
    glm::vec3 specular         = glm::vec3(1.0f);
    float constantAttenuation  = 1.0f;
    float linearAttenuation    = 0.0f;
    float quadraticAttenuation = 0.0f;
    float ambientIntensity     = 1.0f;
    float diffuseIntensity     = 1.0f;
    float specularIntensity    = 1.0f;
    bool isAmbient             = true;
    bool isDiffuse             = true;
    bool isSpecular            = true;
    bool isEnable              = false;
};

struct SpotLightParams {
public:
    glm::vec3 lightDirection   = glm::vec3(1.0f);
    glm::vec3 lightPosition    = glm::vec3(-10.0f);
    glm::vec3 ambient          = glm::vec3(1.0f);
    glm::vec3 diffuse          = glm::vec3(1.0f);
    glm::vec3 specular         = glm::vec3(1.0f);
    float constantAttenuation  = 1.0f;
    float linearAttenuation    = 0.0f;
    float quadraticAttenuation = 0.0f;
    float innerCutoff          = glm::half_pi<float>();
    float outerCutoff          = glm::half_pi<float>();
    float exponent             = 1.0f;
    float ambientIntensity     = 1.0f;
    float diffuseIntensity     = 1.0f;
    float specularIntensity    = 1.0f;
    bool isAmbient             = true;
    bool isDiffuse             = true;
    bool isSpecular            = true;
    bool isEnable              = false;
};

class ApplicationInstance {
public:
    static constexpr const char* NORMALS_SHADER_STR       = "NORMALS SHADER PROGRAM";
    static constexpr const char* BASIC_MESH_SHADER_STR    = "BASIC MESH SHADER";
    static constexpr const char* RED_SHADER_STR           = "RED SHADER";
    static constexpr const char* RGB_SHADER_STR           = "RGB SHADER";
    static constexpr const char* MAGIC_SHADER_STR         = "MAGIC SHADER";
    static constexpr const char* LIGHTING_STR             = "LIGHTING";

    ApplicationInstance() = delete;

    explicit ApplicationInstance(const ApplicationConfig& applicationConfig);

    ApplicationInstance(const ApplicationInstance&) = delete;

    ApplicationInstance(ApplicationInstance&&) noexcept = default;

    ApplicationInstance& operator=(const ApplicationInstance&) = delete;

    ApplicationInstance& operator=(ApplicationInstance&&) noexcept = default;

    ~ApplicationInstance() noexcept = default;

    void Run();

private:
    void InitMeshGenerator_(const std::shared_ptr<IMeshGenerator>& meshGenerator, const MaterialInstance& material);

    void InitWindow_(int windowHeight, int windowWidth, const std::string& windowName);

    void InitRenderer_();

    void InitImgui_();

    void InitCamera_(
        const glm::vec3& cameraPosition, const glm::vec3& cameraTarget, const glm::vec3& cameraX,
        const glm::vec3& cameraY, const glm::vec3& cameraZ
    );

    void InitViewport_(
        const glm::vec2& viewportTopLeft, const glm::vec2& viewportBottomRight, float viewportFOV,
        float viewportNearZ, float viewportFarZ
    );

    void InitMouseButtonCallbacks_();

    void InitMouseMoveCallbacks_();

    void InitMouseScrollCallbacks_();

    void InitKeyPressCallbacks_();

    void InitWindowResizeCallbacks_();

    void InitWindowRefreshCallbacks_();

    void InitLoopCallbacks_();

    void InitCallbacks_();

    void InitShaders_();

    void InitLighting_();

    void UpdateDirectionalLight_();

    void UpdatePointLight_();

    void UpdateSpotLight_();

    void UpdateTime_();

    std::unordered_map<std::string, ShaderInstance> CompileShaders_(const std::vector<std::string>& shaderFilepath, ShaderType shaderType);

    RendererInstance* renderer_{};
    std::unique_ptr<ImguiWrapper> imgui_{};
    std::string selectedShaderKey_{};
    std::vector<std::string> shaderKeys_{};
    std::unique_ptr<WindowInstance> window_{};
    std::unique_ptr<CameraInstance> camera_{};
    std::unique_ptr<ViewportInstance> viewport_{};
    std::shared_ptr<IMeshGenerator> meshGenerator_{};
    std::unordered_map<std::string, std::unique_ptr<ShaderProgram>> shaderPrograms_{};
    std::unordered_map<std::string, std::unique_ptr<LightInstance>> lights_{};
    DirectionalLightParams directionalLightParams_{};
    PointLightParams pointLightParams_{};
    SpotLightParams spotLightParams_{};
    Time applicationTime_{};
    glm::vec3 backgroundColor_{};
    float fovRadians_     = glm::radians(45.0f);
    bool isFlatShading_   = false;
    bool isDrawNormals_   = false;
    bool isPhongSpecular_ = true;
};
