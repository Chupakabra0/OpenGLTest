#pragma once
#include <iostream>
#include <format>

#include "VertexBufferObject.hpp"
#include "VertexArrayObject.hpp"
#include "ShaderProgram.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Viewport.hpp"

#include "TextureLoader/TextureLoaderSTB.hpp"

#include "ImguiWrapper.hpp"

#include "MeshGenerators/ParallelepipedGenerator.hpp"
#include "MeshGenerators/UVSphereGenerator.hpp"
#include "MeshGenerators/IcosahedronGenerator.hpp"
#include "MeshGenerators/ConeGenerator.hpp"

struct ApplicationConfig {
public:
    int         WINDOW_HEIGHT         = 1920;
    int         WINDOW_WIDTH          = 1080;
    std::string WINDOW_NAME           = "Default";
    glm::vec3   CAMERA_POSITION       = glm::zero<glm::vec3>();
    glm::vec3   CAMERA_TARGET         = glm::one<glm::vec3>();
    glm::vec3   CAMERA_AXIS_X         = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3   CAMERA_AXIS_Y         = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3   CAMERA_AXIS_Z         = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec2   VIEWPORT_TOP_LEFT     = glm::zero<glm::vec2>();
    glm::vec2   VIEWPORT_BOTTOM_RIGHT = glm::vec2(1080.0f, 1920.0f);
    float       VIEWPORT_FOV          = 90.0f;
    float       VIEWPORT_NEAR_Z       = 0.1f;
    float       VIEWPORT_FAR_Z        = 1.0f;
};

class Application {
public:
    static constexpr const char* NORMALS_SHADER_STR = "NORMALS_SHADER_PROGRAM";
    static constexpr const char* MESH_SHADER_STR    = "MESH_SHADER_PROGRAM";

    Application() = delete;

    explicit Application(const ApplicationConfig& applicationConfig, const std::shared_ptr<MeshGenerator>& meshGenerator)
        : meshGenerator_(meshGenerator) {
        this->InitWindow_(applicationConfig.WINDOW_HEIGHT, applicationConfig.WINDOW_WIDTH, applicationConfig.WINDOW_NAME);
        this->InitRenderer_();
        this->InitImgui_();
        this->InitCamera_(
            applicationConfig.CAMERA_POSITION, applicationConfig.CAMERA_TARGET,
            applicationConfig.CAMERA_AXIS_X, applicationConfig.CAMERA_AXIS_Y,
            applicationConfig.CAMERA_AXIS_Z
        );
        this->InitViewport_(
            applicationConfig.VIEWPORT_TOP_LEFT, applicationConfig.VIEWPORT_BOTTOM_RIGHT,
            applicationConfig.VIEWPORT_FOV, applicationConfig.VIEWPORT_NEAR_Z, applicationConfig.VIEWPORT_FAR_Z
        );
        this->InitCallbacks_();
        this->InitShaders_();
    }

    Application(const Application&) = delete;

    Application(Application&&) noexcept = default;

    Application& operator=(const Application&) = delete;

    Application& operator=(Application&&) noexcept = default;

    ~Application() noexcept = default;

    void Run() {
        const glm::vec4 backgroundColor = glm::vec4(125.0f, 0.0f, 255.0f, 255.0f);

        MeshClass mesh         = this->meshGenerator_->GenerateMesh();
        IndexBufferObject* ibo = new IndexBufferObject(mesh.GenerateIBO());
        VertexArrayObject vao  = mesh.GenerateVAO(ibo);

        glm::mat4 modelMatrix      = glm::identity<glm::mat4>();
        glm::mat4 viewMatrix       = glm::identity<glm::mat4>();
        glm::mat4 projectionMatrix = glm::identity<glm::mat4>();

        while (!this->window_->ShouldWindowClose()) {
            const float timeInSeconds = static_cast<float>(glfwGetTime());

            const int hours        = static_cast<int>(timeInSeconds) / 3600;
            const int minutes      = (static_cast<int>(timeInSeconds) % 3600) / 60;
            const int seconds      = static_cast<int>(timeInSeconds) % 60;
            const int milliseconds = static_cast<int>(timeInSeconds * 1000) % 1000;

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

            viewMatrix       = this->camera_->CalcViewMatrix();
            projectionMatrix = this->viewport_->CalcPerspectiveMatrix();

            this->shaderPrograms_[Application::NORMALS_SHADER_STR]->SetUniformMatrix("u_proj", projectionMatrix);
            this->shaderPrograms_[Application::NORMALS_SHADER_STR]->SetUniformMatrix("u_view", viewMatrix);
            this->shaderPrograms_[Application::NORMALS_SHADER_STR]->SetUniformMatrix("u_model", modelMatrix);

            this->shaderPrograms_[Application::MESH_SHADER_STR]->SetUniformPairFloat("u_resolution",
                static_cast<float>(this->window_->GetWidth()), static_cast<float>(this->window_->GetHeight())
            );
            this->shaderPrograms_[Application::MESH_SHADER_STR]->SetUniformMatrix("u_proj", projectionMatrix);
            this->shaderPrograms_[Application::MESH_SHADER_STR]->SetUniformMatrix("u_view", viewMatrix);
            this->shaderPrograms_[Application::MESH_SHADER_STR]->SetUniformMatrix("u_model", modelMatrix);
            this->shaderPrograms_[Application::MESH_SHADER_STR]->SetUniformInt("u_isFlat", isFlatShading);
            this->shaderPrograms_[Application::MESH_SHADER_STR]->SetUniformFloat("u_time", timeInSeconds);

            this->renderer_->DrawIndecies(vao, *this->shaderPrograms_[Application::MESH_SHADER_STR]);
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
    }

private:
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
            viewportFOV, viewportNearZ, viewportFarZ
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
                            window.SetMouseUnclicked(button);
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

                    this->camera_->Pan(static_cast<float>(x2 - x1), static_cast<float>(y2 - y1), 1.0f);
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

                        this->camera_->Arcball(
                            static_cast<float>(x2 - x1),
                            static_cast<float>(y2 - y1),
                            static_cast<float>(window.GetHeight()),
                            static_cast<float>(window.GetWidth())
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

                this->viewport_->SetFieldOfView(
                    glm::radians(
                        glm::degrees(this->viewport_->GetFieldOfView()) + (ypos > 0 ? -fieldOfViewStep : fieldOfViewStep)
                    )
                );
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
                    }
                    else if (action == ControlAction::RELEASE) {
                        window.SetKeyUnpressed(key);
                    }
                }
            },
            std::make_shared<Window::KeyPressCallback>(
                [](Window& window, Keyboard::Key key, int scancode, ControlAction action, ControlMods mods) {
                    if (key == Keyboard::Key::S) {
                        if (action == ControlAction::PRESS) {
                            window.SetKeyPressed(key);
                        }
                        else if (action == ControlAction::RELEASE) {
                            window.SetKeyUnpressed(key);
                        }
                    }
                },
                std::make_shared<Window::KeyPressCallback>(
                    [](Window& window, Keyboard::Key key, int scancode, ControlAction action, ControlMods mods) {
                        if (key == Keyboard::Key::D) {
                            if (action == ControlAction::PRESS) {
                                window.SetKeyPressed(key);
                            }
                            else if (action == ControlAction::RELEASE) {
                                window.SetKeyUnpressed(key);
                            }
                        }
                    },
                    std::make_shared<Window::KeyPressCallback>(
                        [](Window& window, Keyboard::Key key, int scancode, ControlAction action, ControlMods mods) {
                            if (key == Keyboard::Key::A) {
                                if (action == ControlAction::PRESS) {
                                    window.SetKeyPressed(key);
                                }
                                else if (action == ControlAction::RELEASE) {
                                    window.SetKeyUnpressed(key);
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
            }
        );

        this->window_->SetResizeCallback(windowResizeCallback);
    }

    void InitWindowRefreshCallbacks_() {
        const auto refreshCallback = std::make_shared<Window::WindowRefreshCallback>();

        this->window_->SetRefreshCallback(refreshCallback);
    }

    void InitLoopCallbacks_() {
        const auto loopCallback = std::make_shared<Window::LoopCallback>(
            [this](Window& window) {
                if (window.IsKeyPressed(Keyboard::Key::W)) {
                    const float speed = 1.0f;

                    this->camera_->MoveCamera(glm::vec3(0.0f, -speed, 0.0f));
                    this->camera_->MoveTarget(glm::vec3(0.0f, -speed, 0.0f));
                }
            },
            std::make_shared<Window::LoopCallback>(
                [this](Window& window) {
                    if (window.IsKeyPressed(Keyboard::Key::S)) {
                        const float speed = 1.0f;

                        this->camera_->MoveCamera(glm::vec3(0.0f, speed, 0.0f));
                        this->camera_->MoveTarget(glm::vec3(0.0f, speed, 0.0f));
                    }
                },
                std::make_shared<Window::LoopCallback>(
                    [this](Window& window) {
                        if (window.IsKeyPressed(Keyboard::Key::D)) {
                            const float speed = 1.0f;

                            this->camera_->MoveCamera(glm::vec3(-speed, 0.0f, 0.0f));
                            this->camera_->MoveTarget(glm::vec3(-speed, 0.0f, 0.0f));
                        }
                    },
                    std::make_shared<Window::LoopCallback>(
                        [this](Window& window) {
                            if (window.IsKeyPressed(Keyboard::Key::A)) {
                                const float speed = 1.0f;

                                this->camera_->MoveCamera(glm::vec3(speed, 0.0f, 0.0f));
                                this->camera_->MoveTarget(glm::vec3(speed, 0.0f, 0.0f));
                            }
                        }
                    )
                )
            )
        );

        this->window_->SetLoopCallback(loopCallback);
    }

    void InitCallbacks_() {
        this->InitMouseButtonCallbacks_();
        this->InitMouseMoveCallbacks_();
        this->InitMouseScrollCallbacks_();
        this->InitKeyPressCallbacks_();
        this->InitWindowResizeCallbacks_();
        this->InitWindowRefreshCallbacks_();
        this->InitLoopCallbacks_();
    }

    void InitShaders_() {
        // Creating shaders
        Shader basicVertexShader{ "shaders\\BasicShader.vert", ShaderType::VERTEX_SHADER };
        Shader basicFragmentShader{ "shaders\\BasicShader.frag", ShaderType::FRAGMENT_SHADER };
        Shader normalVisualizationFragmentShader{ "shaders\\NormalVisualization.frag", ShaderType::FRAGMENT_SHADER };
        Shader redBlueGreenFragmentShader{ "shaders\\RedBlueGreen.frag", ShaderType::FRAGMENT_SHADER };
        Shader magicFragmentShader{ "shaders\\MagicShader.frag", ShaderType::FRAGMENT_SHADER };
        Shader redFragmentShader{ "shaders\\RedShader.frag", ShaderType::FRAGMENT_SHADER };
        Shader basicGeometryShader{ "shaders\\BasicShader.geom", ShaderType::GEOMETRY_SHADER };

        // Creating shader programs
        this->shaderPrograms_.emplace(Application::NORMALS_SHADER_STR, std::make_unique<ShaderProgram>(basicVertexShader, redFragmentShader, basicGeometryShader));
        this->shaderPrograms_.emplace(Application::MESH_SHADER_STR, std::make_unique<ShaderProgram>(basicVertexShader, normalVisualizationFragmentShader));
    }

    Renderer* renderer_{};
    ImguiWrapper* imgui_{};
    std::unique_ptr<Window> window_{};
    std::unique_ptr<Camera> camera_{};
    std::unique_ptr<Viewport> viewport_{};
    std::shared_ptr<MeshGenerator> meshGenerator_{};
    std::unordered_map<std::string, std::unique_ptr<ShaderProgram>> shaderPrograms_{};
};
