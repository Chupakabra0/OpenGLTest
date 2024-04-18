#pragma once
#include "ApplicationConfig/ApplicationConfig.hpp"
#include "RendererInstance/RendererInstance.hpp"
#include "ImguiWrapper/ImguiWrapper.hpp"
#include "WindowInstance/WindowInstance.hpp"
#include "CameraInstance/CameraInstance.hpp"
#include "ViewportInstance/ViewportInstance.hpp"
#include "ShaderProgram/ShaderProgram.hpp"
#include "LogLevel/LogLevel.hpp"

#include <unordered_map>

constexpr bool IsDebug() {
    #if defined(_DEBUG)
        return true;
    #else
        return false;
    #endif
}

class ApplicationInstance {
public:
    static constexpr const char* NORMALS_SHADER_STR    = "NORMALS SHADER PROGRAM";
    static constexpr const char* BASIC_MESH_SHADER_STR = "BASIC MESH SHADER";
    static constexpr const char* RED_SHADER_STR        = "RED SHADER";
    static constexpr const char* RGB_SHADER_STR        = "RGB SHADER";
    static constexpr const char* MAGIC_SHADER_STR      = "MAGIC SHADER";

    ApplicationInstance() = delete;

    explicit ApplicationInstance(const ApplicationConfig& applicationConfig);

    ApplicationInstance(const ApplicationInstance&) = delete;

    ApplicationInstance(ApplicationInstance&&) noexcept = default;

    ApplicationInstance& operator=(const ApplicationInstance&) = delete;

    ApplicationInstance& operator=(ApplicationInstance&&) noexcept = default;

    ~ApplicationInstance() noexcept = default;

    void Run();

private:
    void InitMeshGenerator_(const std::shared_ptr<IMeshGenerator>& generator);

    void InitWindow_(int windowHeight, int windowWidth, const std::string& windowName);

    void InitRenderer_();

    void InitImgui_();

    void InitCamera_(
        const glm::vec3& cameraPosition, const glm::vec3& cameraTarget, const glm::vec3& cameraX,
        const glm::vec3& cameraY, const glm::vec3& cameraZ
    );

    void InitViewport_(const glm::vec2& viewportTopLeft, const glm::vec2& viewportBottomRight, float viewportFOV,
        float viewportNearZ, float viewportFarZ);

    void InitMouseButtonCallbacks_();

    void InitMouseMoveCallbacks_();

    void InitMouseScrollCallbacks_();

    void InitKeyPressCallbacks_();

    void InitWindowResizeCallbacks_();

    void InitWindowRefreshCallbacks_();

    void InitLoopCallbacks_();

    void InitCallbacks_();

    void InitShaders_();

    std::unordered_map<std::string, ShaderInstance> CompileShaders_(const std::vector<std::string>& shaderFilepath, ShaderType shaderType);

    RendererInstance* renderer_{};
    ImguiWrapper* imgui_{};
    std::string selectedShaderKey_{};
    std::vector<std::string> shaderKeys_{};
    std::unique_ptr<WindowInstance> window_{};
    std::unique_ptr<CameraInstance> camera_{};
    std::unique_ptr<ViewportInstance> viewport_{};
    std::shared_ptr<IMeshGenerator> meshGenerator_{};
    std::unordered_map<std::string, std::unique_ptr<ShaderProgram>> shaderPrograms_{};
};
