#pragma once
#include <iostream>
#include <format>
#include <regex>

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_sinks.h"

#include "VertexBufferObject.hpp"
#include "VertexArrayObject.hpp"
#include "ShaderProgram.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Viewport.hpp"
#include "LogLevel.hpp"
#include "ApplicationConfig.hpp"

#include "TextureLoader/TextureLoaderSTB.hpp"

#include "ImguiWrapper.hpp"

#include "MeshGenerators/ParallelepipedGenerator.hpp"
#include "MeshGenerators/UVSphereGenerator.hpp"
#include "MeshGenerators/IcosahedronGenerator.hpp"
#include "MeshGenerators/ConeGenerator.hpp"
#include "MeshGenerators/CylinderGenerator.hpp"
#include "MeshGenerators/TorusGenerator.hpp"
#include "MeshGenerators/IcosphereGenerator.hpp"

inline constexpr bool IsDebug() {
    #if defined(_DEBUG)
        return true;
    #else
        return false;
    #endif
}

class Application {
public:
    static constexpr const char* NORMALS_SHADER_STR    = "NORMALS SHADER PROGRAM";
    static constexpr const char* BASIC_MESH_SHADER_STR = "BASIC MESH SHADER";
    static constexpr const char* RED_SHADER_STR        = "RED SHADER";
    static constexpr const char* RGB_SHADER_STR        = "RGB SHADER";
    static constexpr const char* MAGIC_SHADER_STR      = "MAGIC SHADER";

    Application() = delete;

    explicit Application(const ApplicationConfig& applicationConfig) {
        SPDLOG_INFO("Mesh generator initialization started");
        
        this->InitMeshGenerator_(applicationConfig.MESH_GENERATOR);

        SPDLOG_INFO("Mesh generator initialization started");
        SPDLOG_INFO("Window initialization started");

        this->InitWindow_(applicationConfig.WINDOW_HEIGHT, applicationConfig.WINDOW_WIDTH, applicationConfig.WINDOW_NAME);

        SPDLOG_INFO("Window initialization ended");
        SPDLOG_INFO("Renderer initialization started");

        this->InitRenderer_();

        SPDLOG_INFO("Renderer initialization ended");
        SPDLOG_INFO("ImGUI context initialization started");

        this->InitImgui_();

        SPDLOG_INFO("ImGUI context initialization ended");
        SPDLOG_INFO("Camera initialization started");

        this->InitCamera_(
            applicationConfig.CAMERA_POSITION, applicationConfig.CAMERA_TARGET,
            applicationConfig.CAMERA_AXIS_X, applicationConfig.CAMERA_AXIS_Y,
            applicationConfig.CAMERA_AXIS_Z
        );

        SPDLOG_INFO("Camera initialization ended");
        SPDLOG_INFO("Viewport initialization started");

        this->InitViewport_(
            applicationConfig.VIEWPORT_TOP_LEFT, applicationConfig.VIEWPORT_BOTTOM_RIGHT,
            applicationConfig.VIEWPORT_FOV, applicationConfig.VIEWPORT_NEAR_Z, applicationConfig.VIEWPORT_FAR_Z
        );
        
        SPDLOG_INFO("Viewport initialization ended");
        SPDLOG_INFO("Callbacks initialization started");

        this->InitCallbacks_();

        SPDLOG_INFO("Callbacks initialization ended");
        SPDLOG_INFO("Shaders initialization started");

        this->InitShaders_();

        SPDLOG_INFO("Shaders initialization ended");
    }

    Application(const Application&) = delete;

    Application(Application&&) noexcept = default;

    Application& operator=(const Application&) = delete;

    Application& operator=(Application&&) noexcept = default;

    ~Application() noexcept = default;

    void Run() {
        const glm::vec4 backgroundColor = glm::vec4(125.0f, 0.0f, 255.0f, 255.0f);

        SPDLOG_INFO("Mesh generation started");

        MeshClass mesh = this->meshGenerator_->GenerateMesh();

        SPDLOG_INFO("Mesh generation ended");
        SPDLOG_INFO("IBO & VBO generation started");

        IndexBufferObject* ibo = new IndexBufferObject(mesh.GenerateIBO());
        VertexArrayObject vao  = mesh.GenerateVAO(ibo);

        SPDLOG_INFO("IBO & VBO generation ended");
        SPDLOG_INFO("Render loop started");

        while (!this->window_->ShouldWindowClose()) {
            const float timeInSeconds = static_cast<float>(glfwGetTime());
            const int hours           = static_cast<int>(timeInSeconds) / 3600;
            const int minutes         = (static_cast<int>(timeInSeconds) % 3600) / 60;
            const int seconds         = static_cast<int>(timeInSeconds) % 60;
            const int milliseconds    = static_cast<int>(timeInSeconds * 1000) % 1000;

            static ImVec4 clear_color {
                backgroundColor.r / 255.0f,
                backgroundColor.g / 255.0f,
                backgroundColor.b / 255.0f,
                backgroundColor.a / 255.0f
            };
            static float viewPos[] {
                this->camera_->GetOrigin().x,
                this->camera_->GetOrigin().y,
                this->camera_->GetOrigin().z
            };
            static float viewRotate[]{ 0.0f, 0.0f, 0.0f };
            static bool isFlatShading{};
            static bool isDrawNormals{};

            this->renderer_->ClearScreen(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

            const glm::mat4 modelMatrix      = glm::identity<glm::mat4>();
            const glm::mat4 viewMatrix       = this->camera_->CalcViewMatrix();
            const glm::mat4 projectionMatrix = this->viewport_->CalcPerspectiveMatrix();

            this->shaderPrograms_[Application::NORMALS_SHADER_STR]->SetUniformMatrix("u_proj", projectionMatrix);
            this->shaderPrograms_[Application::NORMALS_SHADER_STR]->SetUniformMatrix("u_view", viewMatrix);
            this->shaderPrograms_[Application::NORMALS_SHADER_STR]->SetUniformMatrix("u_model", modelMatrix);

            this->shaderPrograms_[this->selectedShaderKey_]->SetUniformPairFloat(
                "u_resolution",
                static_cast<float>(this->window_->GetWidth()), static_cast<float>(this->window_->GetHeight())
            );
            this->shaderPrograms_[this->selectedShaderKey_]->SetUniformMatrix("u_proj", projectionMatrix);
            this->shaderPrograms_[this->selectedShaderKey_]->SetUniformMatrix("u_view", viewMatrix);
            this->shaderPrograms_[this->selectedShaderKey_]->SetUniformMatrix("u_model", modelMatrix);
            this->shaderPrograms_[this->selectedShaderKey_]->SetUniformInt("u_isFlat", isFlatShading);
            this->shaderPrograms_[this->selectedShaderKey_]->SetUniformFloat("u_time", timeInSeconds);

            this->renderer_->DrawIndecies(vao, *this->shaderPrograms_[this->selectedShaderKey_]);
            if (isDrawNormals) {
                this->renderer_->DrawIndecies(vao, *this->shaderPrograms_[Application::NORMALS_SHADER_STR]);
            }

            this->imgui_->Bind();

            const ImVec2 center{ImGui::GetMainViewport()->GetCenter().x, 0.0f};
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            ImGui::Begin("Hello, world!");
            ImGui::Text("Background color:");
            ImGui::ColorEdit3("Clear color", reinterpret_cast<float*>(&clear_color));
            ImGui::Text("Display settings:");
            ImGui::Checkbox("Flat shading", &isFlatShading);
            ImGui::SameLine();
            ImGui::Checkbox("Draw normals", &isDrawNormals);
            if (ImGui::BeginCombo("Shaders", this->selectedShaderKey_.c_str())) {
                for (int i = 0; i < this->shaderKeys_.size(); ++i) {
                    const bool isSelected = (this->selectedShaderKey_ == this->shaderKeys_[i]);

                    if (ImGui::Selectable(this->shaderKeys_[i].c_str(), isSelected)) {
                        this->selectedShaderKey_ = this->shaderKeys_[i];
                    }

                    if (isSelected) {
                        ImGui::SetItemDefaultFocus();
                    }
                }

                ImGui::EndCombo();
            }
            ImGui::Text("Display info:");
            ImGui::Text(std::format("Field of view: {:.2f} degrees", glm::degrees(this->viewport_->GetFieldOfView())).c_str());
            ImGui::Text("Application data:");
            ImGui::Text(std::format("Application average {:.0f} FPS", ImGui::GetIO().Framerate).c_str());
            ImGui::Text(std::format("Application time: {:02d}:{:02d}:{:02d}:{:02d}", hours, minutes, seconds, milliseconds).c_str());
            ImGui::End();

            this->imgui_->Unbind();

            this->window_->PollEvents();
            this->window_->SwapBuffers();
        }

        SPDLOG_INFO("Render loop ended");
    }

private:
    void InitMeshGenerator_(const std::shared_ptr<MeshGenerator>& generator) {
        if (generator == nullptr) {
            throw std::runtime_error("Mesh generator is null");
        }

        this->meshGenerator_ = generator;
    }

    void InitWindow_(int windowHeight, int windowWidth, const std::string& windowName) {
        this->window_ = std::make_unique<Window>(windowHeight, windowWidth, windowName);
    }

    void InitRenderer_() {
        this->renderer_ = &Renderer::GetInstance();
    }

    void InitImgui_() {
        this->imgui_ = &ImguiWrapper::GetInstance(*this->window_);
    }

    void InitCamera_(const glm::vec3& cameraPosition, const glm::vec3& cameraTarget, const glm::vec3& cameraX,
        const glm::vec3& cameraY, const glm::vec3& cameraZ) {
        this->camera_ = std::make_unique<Camera>(cameraPosition, cameraTarget, cameraX, cameraY, cameraZ);
    }

    void InitViewport_(const glm::vec2& viewportTopLeft, const glm::vec2& viewportBottomRight, float viewportFOV,
        float viewportNearZ, float viewportFarZ) {
        this->viewport_ = std::make_unique<Viewport>(
            static_cast<int>(viewportTopLeft.x), static_cast<int>(viewportTopLeft.y),
            static_cast<int>(viewportBottomRight.x), static_cast<int>(viewportBottomRight.y),
            glm::radians(viewportFOV), viewportNearZ, viewportFarZ
        );
    }

    void InitMouseButtonCallbacks_() {
        const auto mouseButtonCallback = std::make_shared<Window::MouseClickCallback>(
            [this](Window& window, Mouse::Button button, ControlAction action, ControlMods mods, double xpos, double ypos) {
                if (this->imgui_->GetIO()->WantCaptureMouse) {
                    return;
                }

                if (button == Mouse::Button::LEFT || button == Mouse::Button::RIGHT) {
                    if (action == ControlAction::PRESS) {
                        window.UpdateCursorPosition();
                        window.SetMouseClicked(button);
                        SPDLOG_DEBUG(
                            "{} mouse pressed at ({}, {})",
                            button == Mouse::Button::LEFT ? "Left" : button == Mouse::Button::RIGHT ? "Right" : "",
                            window.GetCurrCursorPos().first, window.GetCurrCursorPos().second
                        );
                    }
                }
            },
            std::make_shared<Window::MouseClickCallback>(
                [this](Window& window, Mouse::Button button, ControlAction action, ControlMods mods, double xpos, double ypos) {
                    if (this->imgui_->GetIO()->WantCaptureMouse) {
                        return;
                    }

                    if (button == Mouse::Button::LEFT || button == Mouse::Button::RIGHT) {
                        if (action == ControlAction::RELEASE) {
                            window.ResetCursorPosition();
                            window.UpdateCursorPosition();
                            window.SetMouseUnclicked(button);
                            SPDLOG_DEBUG(
                                "{} mouse released at ({}, {})",
                                button == Mouse::Button::LEFT ? "Left" : button == Mouse::Button::RIGHT ? "Right" : "",
                                window.GetCurrCursorPos().first, window.GetCurrCursorPos().second
                            );
                        }
                    }
                }
            )
        );

        this->window_->SetMouseClickCallback(mouseButtonCallback);
    }

    void InitMouseMoveCallbacks_() {
        const auto mouseMoveCallback = std::make_shared<Window::MouseMoveCallback>(
            [this](Window& window, double xpos, double ypos) {
                if (this->imgui_->GetIO()->WantCaptureMouse) {
                    return;
                }

                if (window.IsMouseClicked(Mouse::Button::LEFT)) {
                    window.UpdateCursorPosition();

                    auto [x1, y1] = window.GetPrevCursorPos();
                    auto [x2, y2] = window.GetCurrCursorPos();

                    SPDLOG_DEBUG(
                        "Left mouse moved at ({}, {})",
                        window.GetCurrCursorPos().first, window.GetCurrCursorPos().second
                    );

                    this->camera_->Pan(static_cast<float>(x2 - x1), static_cast<float>(y2 - y1), 1.0f);

                    SPDLOG_DEBUG(
                        "Camera panning with u = {}, v = {}, s = {})",
                        static_cast<float>(x2 - x1), static_cast<float>(y2 - y1), 1.0f
                    );
                }
            },
            std::make_shared<Window::MouseMoveCallback>(
                [this](Window& window, double xpos, double ypos) {
                    if (this->imgui_->GetIO()->WantCaptureMouse) {
                        return;
                    }

                    if (window.IsMouseClicked(Mouse::Button::RIGHT)) {
                        window.UpdateCursorPosition();

                        const float RADIUS = 1.0f;

                        auto [x1, y1] = window.GetPrevCursorPos();
                        auto [x2, y2] = window.GetCurrCursorPos();

                        SPDLOG_DEBUG(
                            "Right mouse moved at ({}, {})",
                            window.GetCurrCursorPos().first, window.GetCurrCursorPos().second
                        );

                        this->camera_->Arcball(
                            static_cast<float>(x2 - x1),
                            static_cast<float>(y2 - y1),
                            static_cast<float>(window.GetHeight()),
                            static_cast<float>(window.GetWidth())
                        );

                        SPDLOG_DEBUG(
                            "Camera arcball with u = {}, v = {}, viewportH = {}, viewportW = {})",
                            static_cast<float>(x2 - x1), static_cast<float>(y2 - y1),
                            static_cast<float>(window.GetHeight()), static_cast<float>(window.GetWidth())
                        );
                    }
                }
            )
        );

        this->window_->SetMouseMoveCallback(mouseMoveCallback);
    }

    void InitMouseScrollCallbacks_() {
        const auto mouseScrollCallback = std::make_shared<Window::MouseScrollCallback>(
            [this](Window& window, double xpos, double ypos) {
                constexpr float fieldOfViewStep = 3.0f;
                if (this->imgui_->GetIO()->WantCaptureMouse) {
                    return;
                }

                SPDLOG_DEBUG("Mouse scrolled ({}, {})", xpos, ypos);

                float newFov = glm::radians(glm::degrees(this->viewport_->GetFieldOfView()) + (ypos > 0 ? -fieldOfViewStep : fieldOfViewStep));

                if (isFloatGreater(newFov, 0.0f) && isFloatLess(newFov, glm::pi<float>())) {
                    this->viewport_->SetFieldOfView(newFov);

                    SPDLOG_DEBUG("Set camera FOV: {}", newFov);
                }
                else {
                    SPDLOG_DEBUG("Camera FOV didn't change: {}", this->viewport_->GetFieldOfView());
                }
            }
        );

        this->window_->SetMouseScrollCallback(mouseScrollCallback);
    }

    void InitKeyPressCallbacks_() {
        const auto keyPressCallback = std::make_shared<Window::KeyPressCallback>(
            [](Window& window, Keyboard::Key key, int scancode, ControlAction action, ControlMods mods) {
                if (key == Keyboard::Key::W) {
                    if (action == ControlAction::PRESS) {
                        window.SetKeyPressed(key);
                        SPDLOG_DEBUG("Key W pressed");
                    }
                    else if (action == ControlAction::RELEASE) {
                        window.SetKeyUnpressed(key);
                        SPDLOG_DEBUG("Key W released");
                    }
                }
            },
            std::make_shared<Window::KeyPressCallback>(
                [](Window& window, Keyboard::Key key, int scancode, ControlAction action, ControlMods mods) {
                    if (key == Keyboard::Key::S) {
                        if (action == ControlAction::PRESS) {
                            window.SetKeyPressed(key);
                            SPDLOG_DEBUG("Key S pressed");
                        }
                        else if (action == ControlAction::RELEASE) {
                            window.SetKeyUnpressed(key);
                            SPDLOG_DEBUG("Key S released");
                        }
                    }
                },
                std::make_shared<Window::KeyPressCallback>(
                    [](Window& window, Keyboard::Key key, int scancode, ControlAction action, ControlMods mods) {
                        if (key == Keyboard::Key::D) {
                            if (action == ControlAction::PRESS) {
                                window.SetKeyPressed(key);
                                SPDLOG_DEBUG("Key D pressed");
                            }
                            else if (action == ControlAction::RELEASE) {
                                window.SetKeyUnpressed(key);
                                SPDLOG_DEBUG("Key D released");
                            }
                        }
                    },
                    std::make_shared<Window::KeyPressCallback>(
                        [](Window& window, Keyboard::Key key, int scancode, ControlAction action, ControlMods mods) {
                            if (key == Keyboard::Key::A) {
                                if (action == ControlAction::PRESS) {
                                    window.SetKeyPressed(key);
                                    SPDLOG_DEBUG("Key A pressed");
                                }
                                else if (action == ControlAction::RELEASE) {
                                    window.SetKeyUnpressed(key);
                                    SPDLOG_DEBUG("Key A released");
                                }
                            }
                        }
                    )
                )
            )
        );

        this->window_->SetKeyPressCallback(keyPressCallback);
    }

    void InitWindowResizeCallbacks_() {
        const auto windowResizeCallback = std::make_shared<Window::WindowResizeCallback>(
            [this](Window& window, int width, int height) {
                this->viewport_->SetBottomX(width);
                this->viewport_->SetBottomY(height);
                this->viewport_->UpdateViewport();
                SPDLOG_DEBUG("Window resized {} x {}", width, height);
            }
        );

        this->window_->SetResizeCallback(windowResizeCallback);
    }

    void InitWindowRefreshCallbacks_() {
        const auto refreshCallback = std::make_shared<Window::WindowRefreshCallback>(
            [](Window&) {
                SPDLOG_DEBUG("Window refreshed");
            }
        );

        this->window_->SetRefreshCallback(refreshCallback);
    }

    void InitLoopCallbacks_() {
        const auto loopCallback = std::make_shared<Window::LoopCallback>(
            [this](Window& window) {
                if (window.IsKeyPressed(Keyboard::Key::W)) {
                    SPDLOG_DEBUG("Key W repeated");

                    const float speed = 1.0f;

                    this->camera_->MoveCamera(glm::vec3(0.0f, -speed, 0.0f));
                    SPDLOG_DEBUG("Camera origin moved ({}, {}, {})", 0.0f, -speed, 0.0f);

                    this->camera_->MoveTarget(glm::vec3(0.0f, -speed, 0.0f));
                    SPDLOG_DEBUG("Camera target moved ({}, {}, {})", 0.0f, -speed, 0.0f);
                }
            },
            std::make_shared<Window::LoopCallback>(
                [this](Window& window) {
                    if (window.IsKeyPressed(Keyboard::Key::S)) {
                        SPDLOG_DEBUG("Key S repeated");

                        const float speed = 1.0f;

                        this->camera_->MoveCamera(glm::vec3(0.0f, speed, 0.0f));
                        SPDLOG_DEBUG("Camera origin moved ({}, {}, {})", 0.0f, speed, 0.0f);

                        this->camera_->MoveTarget(glm::vec3(0.0f, speed, 0.0f));
                        SPDLOG_DEBUG("Camera target moved ({}, {}, {})", 0.0f, speed, 0.0f);
                    }
                },
                std::make_shared<Window::LoopCallback>(
                    [this](Window& window) {
                        if (window.IsKeyPressed(Keyboard::Key::D)) {
                            SPDLOG_DEBUG("Key D repeated");

                            const float speed = 1.0f;

                            this->camera_->MoveCamera(glm::vec3(-speed, 0.0f, 0.0f));
                            SPDLOG_DEBUG("Camera origin moved ({}, {}, {})", -speed, 0.0f, 0.0f);

                            this->camera_->MoveTarget(glm::vec3(-speed, 0.0f, 0.0f));
                            SPDLOG_DEBUG("Camera target moved ({}, {}, {})", -speed, 0.0f, 0.0f);
                        }
                    },
                    std::make_shared<Window::LoopCallback>(
                        [this](Window& window) {
                            if (window.IsKeyPressed(Keyboard::Key::A)) {
                                SPDLOG_DEBUG("Key A repeated");

                                const float speed = 1.0f;

                                this->camera_->MoveCamera(glm::vec3(speed, 0.0f, 0.0f));
                                SPDLOG_DEBUG("Camera origin moved ({}, {}, {})", speed, 0.0f, 0.0f);

                                this->camera_->MoveTarget(glm::vec3(speed, 0.0f, 0.0f));
                                SPDLOG_DEBUG("Camera target moved ({}, {}, {})", speed, 0.0f, 0.0f);
                            }
                        }
                    )
                )
            )
        );

        this->window_->SetLoopCallback(loopCallback);
    }

    void InitCallbacks_() {
        SPDLOG_INFO("Mouse button callbacks initialization started");

        this->InitMouseButtonCallbacks_();

        SPDLOG_INFO("Mouse button callbacks initialization ended");
        SPDLOG_INFO("Mouse move callbacks initialization started");

        this->InitMouseMoveCallbacks_();
        
        SPDLOG_INFO("Mouse move callbacks initialization ended");
        SPDLOG_INFO("Mouse scroll callbacks initialization started");

        this->InitMouseScrollCallbacks_();

        SPDLOG_INFO("Mouse scroll callbacks initialization ended");
        SPDLOG_INFO("Key press callbacks initialization started");

        this->InitKeyPressCallbacks_();

        SPDLOG_INFO("Key press callbacks initialization ended");
        SPDLOG_INFO("Window resize callbacks initialization started");

        this->InitWindowResizeCallbacks_();

        SPDLOG_INFO("Window resize callbacks initialization ended");
        SPDLOG_INFO("Window refresh callbacks initialization started");

        this->InitWindowRefreshCallbacks_();

        SPDLOG_INFO("Window refresh callbacks initialization ended");
        SPDLOG_INFO("Loop callbacks initialization started");

        this->InitLoopCallbacks_();
        
        SPDLOG_INFO("Loop callbacks initialization ended");
    }

    void InitShaders_() {
        const static std::vector<std::string> vertexShaderData {
            "shaders\\BasicShader.vert"
        };

        const static std::vector<std::string> fragmentShaderData {
            "shaders\\BasicShader.frag",
            "shaders\\NormalVisualization.frag",
            "shaders\\RedBlueGreen.frag",
            "shaders\\MagicShader.frag",
            "shaders\\RedShader.frag"
        };

        const static std::vector<std::string> geomeryShaderData {
            "shaders\\BasicShader.geom"
        };

        auto vertexShaders   = this->CompileShaders_(vertexShaderData, ShaderType::VERTEX_SHADER);
        auto fragmentShaders = this->CompileShaders_(fragmentShaderData, ShaderType::FRAGMENT_SHADER);
        auto geomeryShaders  = this->CompileShaders_(geomeryShaderData, ShaderType::GEOMETRY_SHADER);

        // Creating shader programs
        this->shaderPrograms_.emplace(Application::BASIC_MESH_SHADER_STR, std::make_unique<ShaderProgram>(vertexShaders.at("BasicShader"), fragmentShaders.at("NormalVisualization")));
        this->shaderPrograms_.emplace(Application::RED_SHADER_STR, std::make_unique<ShaderProgram>(vertexShaders.at("BasicShader"), fragmentShaders.at("RedShader")));
        this->shaderPrograms_.emplace(Application::RGB_SHADER_STR, std::make_unique<ShaderProgram>(vertexShaders.at("BasicShader"), fragmentShaders.at("RedBlueGreen")));
        this->shaderPrograms_.emplace(Application::MAGIC_SHADER_STR, std::make_unique<ShaderProgram>(vertexShaders.at("BasicShader"), fragmentShaders.at("MagicShader")));
        this->shaderPrograms_.emplace(Application::NORMALS_SHADER_STR, std::make_unique<ShaderProgram>(vertexShaders.at("BasicShader"), fragmentShaders.at("RedShader"), geomeryShaders.at("BasicShader")));

        for (auto& [key, _] : this->shaderPrograms_) {
            if (key == Application::NORMALS_SHADER_STR) {
                continue;
            }

            this->shaderKeys_.emplace_back(key);
        }

        this->selectedShaderKey_ = this->shaderKeys_.front();
    }

    std::unordered_map<std::string, Shader> CompileShaders_(const std::vector<std::string>& shaderFilepath, ShaderType shaderType) {
        std::unordered_map<std::string, Shader> shaders{};

        const auto getShaderName = [](const std::string& filepath) {
            static const std::regex pattern("(\\\\|/)(.+)\\.(frag|geom|vert)");
            static std::smatch match{};
            std::regex_search(filepath, match, pattern);

            // 2 is for filename position
            return match[2].str();
        };

        for (const auto& filepath : shaderFilepath) {
            SPDLOG_DEBUG("Shader {} compilation started", filepath);
            shaders.emplace(getShaderName(filepath), std::move(Shader(filepath, shaderType)));
            SPDLOG_DEBUG("Shader {} compilation succeed", filepath);
        }

        return shaders;
    }

    Renderer* renderer_{};
    ImguiWrapper* imgui_{};
    std::string selectedShaderKey_{};
    std::vector<std::string> shaderKeys_{};
    std::unique_ptr<Window> window_{};
    std::unique_ptr<Camera> camera_{};
    std::unique_ptr<Viewport> viewport_{};
    std::shared_ptr<MeshGenerator> meshGenerator_{};
    std::unordered_map<std::string, std::unique_ptr<ShaderProgram>> shaderPrograms_{};
};
