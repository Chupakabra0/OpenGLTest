#include "ApplicationInstance/ApplicationInstance.hpp"
#include "ImguiWrapper/ImguiCheckBox/ImguiCheckBox.hpp"
#include "ImguiWrapper/ImguiColorPicker/ImguiColorPicker.hpp"
#include "ImguiWrapper/ImguiComboBox/ImguiComboBox.hpp"
#include "ImguiWrapper/ImguiSameLine/ImguiSameLine.hpp"
#include "ImguiWrapper/ImguiSlider/ImguiSlider.hpp"
#include "ImguiWrapper/ImguiTextBox/ImguiTextBox.hpp"
#include "MeshGenerators/MaterialMeshGenerator.hpp"
#include "MeshInstance/MaterialMeshInstance.hpp"

#include <spdlog/spdlog.h>

#include <ranges>
#include <regex>

ApplicationInstance::ApplicationInstance(const ApplicationConfig& applicationConfig)
    : backgroundColor_(applicationConfig.WINDOW_BACKGROUND) {
    SPDLOG_INFO("Mesh generator initialization started");

    this->InitMeshGenerator_(
        applicationConfig.MESH_GENERATOR,
        MaterialInstance(
            applicationConfig.MATERIAL_AMBIENT,
            applicationConfig.MATERIAL_DIFFUSE,
            applicationConfig.MATERIAL_SPECULAR,
            applicationConfig.MATERIAL_SHININESS
        )
    );

    SPDLOG_INFO("Mesh generator initialization started");
    SPDLOG_INFO("Window initialization started");

    this->InitWindow_(applicationConfig.WINDOW_HEIGHT, applicationConfig.WINDOW_WIDTH, applicationConfig.WINDOW_NAME);

    SPDLOG_INFO("Window initialization ended");
    SPDLOG_INFO("Renderer initialization started");

    this->InitRenderer_();

    SPDLOG_INFO("Renderer initialization ended");
    SPDLOG_INFO("Camera initialization started");

    this->InitCamera_(
        applicationConfig.CAMERA_POSITION, applicationConfig.CAMERA_TARGET,
        applicationConfig.CAMERA_AXIS_X, applicationConfig.CAMERA_AXIS_Y,
        applicationConfig.CAMERA_AXIS_Z
    );

    SPDLOG_INFO("Camera initialization ended");
    SPDLOG_INFO("Viewport initialization started");

    this->InitViewport_(
        glm::vec2(applicationConfig.WINDOW_WIDTH / 3.0f, 0.0f),
        glm::vec2(applicationConfig.WINDOW_WIDTH, applicationConfig.WINDOW_HEIGHT),
        applicationConfig.VIEWPORT_FOV, applicationConfig.VIEWPORT_NEAR_Z, applicationConfig.VIEWPORT_FAR_Z
    );

    SPDLOG_INFO("Viewport initialization ended");
    SPDLOG_INFO("Callbacks initialization started");

    this->InitCallbacks_();

    SPDLOG_INFO("Callbacks initialization ended");
    SPDLOG_INFO("Shaders initialization started");

    this->InitShaders_();

    SPDLOG_INFO("Shaders initialization ended");

    SPDLOG_INFO("Lighting initialization started");

    this->InitLighting_();

    SPDLOG_INFO("Lighting initialization ended");
    SPDLOG_INFO("ImGUI context initialization started");

    this->InitImgui_();

    SPDLOG_INFO("ImGUI context initialization ended");
}

void ApplicationInstance::Run() {
    SPDLOG_INFO("Mesh generation started");

    std::shared_ptr<IMeshInstance> mesh = this->meshGenerator_->GenerateMesh();

    SPDLOG_INFO("Mesh generation ended");
    SPDLOG_INFO("IBO & VBO generation started");

    IndexBufferObject* ibo = new IndexBufferObject(mesh->GenerateIBO());
    VertexArrayObject vao = mesh->GenerateVAO(ibo);

    SPDLOG_INFO("IBO & VBO generation ended");
    SPDLOG_INFO("Render loop started");

    while (!this->window_->ShouldWindowClose()) {
        this->UpdateTime_();
        this->viewport_->UpdateViewport();

        this->renderer_->ClearScreen(this->backgroundColor_.r, this->backgroundColor_.g, this->backgroundColor_.b);

        const glm::mat4 modelMatrix = glm::identity<glm::mat4>();
        const glm::mat4 viewMatrix = this->camera_->CalcViewMatrix();
        const glm::mat4 projectionMatrix = this->viewport_->CalcPerspectiveMatrix();

        this->fovRadians_ = this->viewport_->GetFieldOfView();

        this->shaderPrograms_[ApplicationInstance::NORMALS_SHADER_STR]->SetUniformMatrix("u_proj", projectionMatrix);
        this->shaderPrograms_[ApplicationInstance::NORMALS_SHADER_STR]->SetUniformMatrix("u_view", viewMatrix);
        this->shaderPrograms_[ApplicationInstance::NORMALS_SHADER_STR]->SetUniformMatrix("u_model", modelMatrix);

        this->shaderPrograms_[this->selectedShaderKey_]->SetUniformPairFloat(
            "u_resolution",
            static_cast<float>(this->window_->GetWidth()), static_cast<float>(this->window_->GetHeight())
        );
        this->shaderPrograms_[this->selectedShaderKey_]->SetUniformMatrix("u_proj", projectionMatrix);
        this->shaderPrograms_[this->selectedShaderKey_]->SetUniformMatrix("u_view", viewMatrix);
        this->shaderPrograms_[this->selectedShaderKey_]->SetUniformMatrix("u_model", modelMatrix);
        this->shaderPrograms_[this->selectedShaderKey_]->SetUniformFloat("u_time", this->applicationTime_.totalTimeInSeconds);

        this->shaderPrograms_[this->selectedShaderKey_]->SetUniformInt("u_is_flat", this->isFlatShading_);
        this->shaderPrograms_[this->selectedShaderKey_]->SetUniformInt("u_is_phong_specular", this->isPhongSpecular_);
        this->shaderPrograms_[this->selectedShaderKey_]->SetUniformVector("u_camera_position", this->camera_->GetOrigin());

        this->UpdateDirectionalLight_();
        this->UpdatePointLight_();
        this->UpdateSpotLight_();

        this->renderer_->DrawIndecies(vao, *this->shaderPrograms_[this->selectedShaderKey_]);
        if (this->isDrawNormals_) {
            this->renderer_->DrawIndecies(vao, *this->shaderPrograms_[ApplicationInstance::NORMALS_SHADER_STR]);
        }

        this->imgui_->DrawAll();

        this->window_->PollEvents();
        this->window_->SwapBuffers();
    }

    SPDLOG_INFO("Render loop ended");
}

void ApplicationInstance::InitMeshGenerator_(const std::shared_ptr<IMeshGenerator>& meshGenerator, const MaterialInstance& material) {
    if (meshGenerator == nullptr) {
        throw std::runtime_error("Mesh generator is null");
    }

    this->meshGenerator_ = std::make_shared<MaterialMeshGenerator>(meshGenerator, material);
}

void ApplicationInstance::InitWindow_(int windowHeight, int windowWidth, const std::string& windowName) {
    this->window_ = std::make_unique<WindowInstance>(windowHeight, windowWidth, windowName);
}

void ApplicationInstance::InitRenderer_() {
    this->renderer_ = &RendererInstance::GetInstance();
}

void ApplicationInstance::InitImgui_() {
    this->imgui_ = std::make_unique<ImguiWrapper>(*this->window_, "OpenGL Test", 0.0, 0.0);

    this->imgui_->AddElement(std::make_shared<ImguiTextBox<>>("Background color"));
    this->imgui_->AddElement(std::make_shared<ImguiColorPicker>("Clear color", this->backgroundColor_));

    this->imgui_->AddElement(std::make_shared<ImguiTextBox<>>("Display settings:"));
    this->imgui_->AddElement(std::make_shared<ImguiCheckBox>("Flat shading", this->isFlatShading_));
    this->imgui_->AddElement(std::make_shared<ImguiSameLine>());
    this->imgui_->AddElement(std::make_shared<ImguiCheckBox>("Draw normals", this->isDrawNormals_));
    this->imgui_->AddElement(std::make_shared<ImguiSameLine>());
    this->imgui_->AddElement(std::make_shared<ImguiCheckBox>("Phong specular", this->isPhongSpecular_));

    this->imgui_->AddElement(std::make_shared<ImguiTextBox<>>("Directional light:"));
    this->imgui_->AddElement(std::make_shared<ImguiCheckBox>("Enable light", this->directionalLightParams_.isEnable));
    this->imgui_->AddElement(
        std::make_shared<ImguiSlider<glm::vec3>>(
            "Direction",
            this->directionalLightParams_.lightDirection, -1.0f, 1.0f
        )
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiColorPicker>("Ambient", this->directionalLightParams_.ambient)
    );
    this->imgui_->AddElement(std::make_shared<ImguiSameLine>());
    this->imgui_->AddElement(
        std::make_shared<ImguiCheckBox>("Ambient", this->directionalLightParams_.isAmbient)
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiColorPicker>("Diffuse", this->directionalLightParams_.diffuse)
    );
    this->imgui_->AddElement(std::make_shared<ImguiSameLine>());
    this->imgui_->AddElement(
        std::make_shared<ImguiCheckBox>("Diffuse", this->directionalLightParams_.isDiffuse)
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiColorPicker>("Specular", this->directionalLightParams_.specular)
    );
    this->imgui_->AddElement(std::make_shared<ImguiSameLine>());
    this->imgui_->AddElement(
        std::make_shared<ImguiCheckBox>("Specular", this->directionalLightParams_.isSpecular)
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiSlider<float>>(
            "Ambient Intensity",
            this->directionalLightParams_.ambientIntensity, 0.0, 1.0
        )
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiSlider<float>>(
            "Diffuse Intensity",
            this->directionalLightParams_.diffuseIntensity, 0.0, 1.0
        )
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiSlider<float>>(
            "Specular Intensity",
            this->directionalLightParams_.specularIntensity, 0.0, 1.0
        )
    );

    this->imgui_->AddElement(std::make_shared<ImguiTextBox<>>("Point light:"));
    this->imgui_->AddElement(
        std::make_shared<ImguiCheckBox>(
            "Enable light",
            this->pointLightParams_.isEnable
        )
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiSlider<glm::vec3>>(
            "Position",
            this->pointLightParams_.lightPosition, -10.0f, 10.0f
        )
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiColorPicker>("Ambient", this->pointLightParams_.ambient)
    );
    this->imgui_->AddElement(std::make_shared<ImguiSameLine>());
    this->imgui_->AddElement(
        std::make_shared<ImguiCheckBox>("Ambient", this->pointLightParams_.isAmbient)
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiColorPicker>("Diffuse", this->pointLightParams_.diffuse)
    );
    this->imgui_->AddElement(std::make_shared<ImguiSameLine>());
    this->imgui_->AddElement(
        std::make_shared<ImguiCheckBox>("Diffuse", this->pointLightParams_.isDiffuse)
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiColorPicker>("Specular", this->pointLightParams_.specular)
    );
    this->imgui_->AddElement(std::make_shared<ImguiSameLine>());
    this->imgui_->AddElement(
        std::make_shared<ImguiCheckBox>("Specular", this->pointLightParams_.isSpecular)
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiSlider<float>>("Constant attenuation", this->pointLightParams_.constantAttenuation, 0.0f, 1.0f)
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiSlider<float>>("Linear attenuation", this->pointLightParams_.linearAttenuation, 0.0f, 1.0f)
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiSlider<float>>("Quadratic attenuation", this->pointLightParams_.quadraticAttenuation, 0.0f, 1.0f)
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiSlider<float>>(
            "Ambient Intensity",
            this->pointLightParams_.ambientIntensity, 0.0, 1.0
        )
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiSlider<float>>(
            "Diffuse Intensity",
            this->pointLightParams_.diffuseIntensity, 0.0, 1.0
        )
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiSlider<float>>(
            "Specular Intensity",
            this->pointLightParams_.specularIntensity, 0.0, 1.0
        )
    );

    this->imgui_->AddElement(std::make_shared<ImguiTextBox<>>("Spot light:"));
    this->imgui_->AddElement(std::make_shared<ImguiCheckBox>("Enable light", this->spotLightParams_.isEnable));
    this->imgui_->AddElement(
        std::make_shared<ImguiSlider<glm::vec3>>(
            "Position",
            this->spotLightParams_.lightPosition, -10.0f, 10.0f
        )
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiSlider<glm::vec3>>(
            "Direction",
            this->spotLightParams_.lightDirection, -1.0f, 1.0f
        )
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiColorPicker>("Ambient", this->spotLightParams_.ambient)
    );
    this->imgui_->AddElement(std::make_shared<ImguiSameLine>());
    this->imgui_->AddElement(
        std::make_shared<ImguiCheckBox>("Ambient", this->spotLightParams_.isAmbient)
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiColorPicker>("Diffuse", this->spotLightParams_.diffuse)
    );
    this->imgui_->AddElement(std::make_shared<ImguiSameLine>());
    this->imgui_->AddElement(
        std::make_shared<ImguiCheckBox>("Diffuse", this->spotLightParams_.isDiffuse)
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiColorPicker>("Specular", this->spotLightParams_.specular)
    );
    this->imgui_->AddElement(std::make_shared<ImguiSameLine>());
    this->imgui_->AddElement(
        std::make_shared<ImguiCheckBox>("Specular", this->spotLightParams_.isSpecular)
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiSlider<float>>(
            "Constant attenuation",
            this->spotLightParams_.constantAttenuation, 0.0f, 1.0f
        )
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiSlider<float>>(
            "Linear attenuation",
            this->spotLightParams_.linearAttenuation, 0.0f, 1.0f
        )
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiSlider<float>>(
            "Quadratic attenuation",
            this->spotLightParams_.quadraticAttenuation, 0.0f, 1.0f
        )
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiSlider<float>>(
            "Inner Cutoff",
            this->spotLightParams_.innerCutoff, 0.0f, glm::half_pi<float>()
        )
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiSlider<float>>(
            "Outer Cutoff",
            this->spotLightParams_.outerCutoff, 0.0f, glm::half_pi<float>()
        )
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiSlider<float>>(
            "Exponent",
            this->spotLightParams_.exponent, 0.0f, 128.0f
        )
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiSlider<float>>(
            "Ambient Intensity",
            this->spotLightParams_.ambientIntensity, 0.0, 1.0
        )
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiSlider<float>>(
            "Diffuse Intensity",
            this->spotLightParams_.diffuseIntensity, 0.0, 1.0
        )
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiSlider<float>>(
            "Specular Intensity",
            this->spotLightParams_.specularIntensity, 0.0, 1.0
        )
    );

    this->imgui_->AddElement(
        std::make_shared<ImguiTextBox<float&>>(
            "Application average %.0f FPS",
            std::ref(ImGui::GetIO().Framerate)
        )
    );
    this->imgui_->AddElement(
        std::make_shared<ImguiTextBox<size_t&, size_t&, size_t&, size_t&>>(
            "Application time: %02d:%02d:%02d:%02d",
            std::ref(this->applicationTime_.hours),
            std::ref(this->applicationTime_.minutes),
            std::ref(this->applicationTime_.seconds),
            std::ref(this->applicationTime_.milliseconds)
        )
    );
}

void ApplicationInstance::InitCamera_(
    const glm::vec3& cameraPosition, const glm::vec3& cameraTarget,
    const glm::vec3& cameraX, const glm::vec3& cameraY, const glm::vec3& cameraZ) {
    this->camera_ = std::make_unique<CameraInstance>(cameraPosition, cameraTarget, cameraX, cameraY, cameraZ);
}

void ApplicationInstance::InitViewport_(
    const glm::vec2& viewportTopLeft, const glm::vec2& viewportBottomRight,
    float viewportFOV, float viewportNearZ, float viewportFarZ) {
    this->viewport_ = std::make_unique<ViewportInstance>(
        static_cast<int>(viewportTopLeft.x), static_cast<int>(viewportTopLeft.y),
        static_cast<int>(viewportBottomRight.x), static_cast<int>(viewportBottomRight.y),
        glm::radians(viewportFOV), viewportNearZ, viewportFarZ
    );
}

void ApplicationInstance::InitMouseButtonCallbacks_() {
    const auto mouseButtonCallback = std::make_shared<WindowInstance::MouseClickCallback>(
        [this](WindowInstance& window, MouseInstance::Button button, ControlAction action, ControlMods mods, double xpos, double ypos) {
            if (this->imgui_->GetIO()->WantCaptureMouse) {
                return;
            }

            if (button == MouseInstance::Button::LEFT || button == MouseInstance::Button::RIGHT) {
                if (action == ControlAction::PRESS) {
                    window.UpdateCursorPosition();
                    window.SetMouseClicked(button);
                    SPDLOG_DEBUG(
                        "{} mouse pressed at ({}, {})",
                        button == MouseInstance::Button::LEFT ? "Left" : button == MouseInstance::Button::RIGHT ? "Right" : "",
                        window.GetCurrCursorPos().first, window.GetCurrCursorPos().second
                    );
                }
            }
        },
        std::make_shared<WindowInstance::MouseClickCallback>(
            [this](WindowInstance& window, MouseInstance::Button button, ControlAction action, ControlMods mods, double xpos, double ypos) {
                if (this->imgui_->GetIO()->WantCaptureMouse) {
                    return;
                }

                if (button == MouseInstance::Button::LEFT || button == MouseInstance::Button::RIGHT) {
                    if (action == ControlAction::RELEASE) {
                        window.ResetCursorPosition();
                        window.UpdateCursorPosition();
                        window.SetMouseUnclicked(button);
                        SPDLOG_DEBUG(
                            "{} mouse released at ({}, {})",
                            button == MouseInstance::Button::LEFT ? "Left" : button == MouseInstance::Button::RIGHT ? "Right" : "",
                            window.GetCurrCursorPos().first, window.GetCurrCursorPos().second
                        );
                    }
                }
            }
        )
    );

    this->window_->SetMouseClickCallback(mouseButtonCallback);
}

void ApplicationInstance::InitMouseMoveCallbacks_() {
    const auto mouseMoveCallback = std::make_shared<WindowInstance::MouseMoveCallback>(
        [this](WindowInstance& window, double xpos, double ypos) {
            if (this->imgui_->GetIO()->WantCaptureMouse) {
                return;
            }

            if (window.IsMouseClicked(MouseInstance::Button::LEFT)) {
                window.UpdateCursorPosition();

                auto [x1, y1] = window.GetPrevCursorPos();
                auto [x2, y2] = window.GetCurrCursorPos();

                SPDLOG_DEBUG(
                    "Left mouse moved at ({}, {})",
                    window.GetCurrCursorPos().first, window.GetCurrCursorPos().second
                );

                this->camera_->Pan(static_cast<float>(x2 - x1), static_cast<float>(y2 - y1), 0.01f);

                SPDLOG_DEBUG(
                    "Camera panning with u = {}, v = {}, s = {})",
                    static_cast<float>(x2 - x1), static_cast<float>(y2 - y1), 0.01f
                );
            }
        },
        std::make_shared<WindowInstance::MouseMoveCallback>(
            [this](WindowInstance& window, double xpos, double ypos) {
                if (this->imgui_->GetIO()->WantCaptureMouse) {
                    return;
                }

                if (window.IsMouseClicked(MouseInstance::Button::RIGHT)) {
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

void ApplicationInstance::InitMouseScrollCallbacks_() {
    const auto mouseScrollCallback = std::make_shared<WindowInstance::MouseScrollCallback>(
        [this](WindowInstance& window, double xpos, double ypos) {
            //constexpr float fieldOfViewStep = 3.0f;
            if (this->imgui_->GetIO()->WantCaptureMouse) {
                return;
            }

            SPDLOG_DEBUG("Mouse scrolled ({}, {})", xpos, ypos);

            if (ypos < 0.0) {
                this->camera_->DecreaseDistanceMult();
            }
            else {
                this->camera_->IncreaseDistanceMult();
            }

            //float newFov = glm::radians(glm::degrees(this->viewport_->GetFieldOfView()) + (ypos > 0 ? -fieldOfViewStep : fieldOfViewStep));

            //if (isFloatGreater(newFov, 0.0f) && isFloatLess(newFov, glm::pi<float>())) {
            //    this->viewport_->SetFieldOfView(newFov);

            //    SPDLOG_DEBUG("Set camera FOV: {}", newFov);
            //}
            //else {
            //    SPDLOG_DEBUG("Camera FOV didn't change: {}", this->viewport_->GetFieldOfView());
            //}
        }
    );

    this->window_->SetMouseScrollCallback(mouseScrollCallback);
}

void ApplicationInstance::InitKeyPressCallbacks_() {
    const auto keyPressCallback = std::make_shared<WindowInstance::KeyPressCallback>(
        [](WindowInstance& window, KeyboardInstance::Key key, int scancode, ControlAction action, ControlMods mods) {
            if (key == KeyboardInstance::Key::W) {
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
        std::make_shared<WindowInstance::KeyPressCallback>(
            [](WindowInstance& window, KeyboardInstance::Key key, int scancode, ControlAction action, ControlMods mods) {
                if (key == KeyboardInstance::Key::S) {
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
            std::make_shared<WindowInstance::KeyPressCallback>(
                [](WindowInstance& window, KeyboardInstance::Key key, int scancode, ControlAction action, ControlMods mods) {
                    if (key == KeyboardInstance::Key::D) {
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
                std::make_shared<WindowInstance::KeyPressCallback>(
                    [](WindowInstance& window, KeyboardInstance::Key key, int scancode, ControlAction action, ControlMods mods) {
                        if (key == KeyboardInstance::Key::A) {
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

void ApplicationInstance::InitWindowResizeCallbacks_() {
    const auto windowResizeCallback = std::make_shared<WindowInstance::WindowResizeCallback>(
        [this](WindowInstance& window, int width, int height) {
            this->viewport_->SetBottomX(width);
            this->viewport_->SetBottomY(height);
            this->viewport_->UpdateViewport();
            SPDLOG_DEBUG("Window resized {} x {}", width, height);
        }
    );

    this->window_->SetResizeCallback(windowResizeCallback);
}

void ApplicationInstance::InitWindowRefreshCallbacks_() {
    const auto refreshCallback = std::make_shared<WindowInstance::WindowRefreshCallback>(
        [](WindowInstance&) {
            SPDLOG_DEBUG("Window refreshed");
        }
    );

    this->window_->SetRefreshCallback(refreshCallback);
}

void ApplicationInstance::InitLoopCallbacks_() {
    const auto loopCallback = std::make_shared<WindowInstance::LoopCallback>(
        [this](WindowInstance& window) {
            if (window.IsKeyPressed(KeyboardInstance::Key::W)) {
                SPDLOG_DEBUG("Key W repeated");

                const float speed = 0.01f;

                this->camera_->MoveCamera(glm::vec3(0.0f, -speed, 0.0f));
                SPDLOG_DEBUG("Camera origin moved ({}, {}, {})", 0.0f, -speed, 0.0f);

                this->camera_->MoveTarget(glm::vec3(0.0f, -speed, 0.0f));
                SPDLOG_DEBUG("Camera target moved ({}, {}, {})", 0.0f, -speed, 0.0f);
            }
        },
        std::make_shared<WindowInstance::LoopCallback>(
            [this](WindowInstance& window) {
                if (window.IsKeyPressed(KeyboardInstance::Key::S)) {
                    SPDLOG_DEBUG("Key S repeated");

                    const float speed = 0.01f;

                    this->camera_->MoveCamera(glm::vec3(0.0f, speed, 0.0f));
                    SPDLOG_DEBUG("Camera origin moved ({}, {}, {})", 0.0f, speed, 0.0f);

                    this->camera_->MoveTarget(glm::vec3(0.0f, speed, 0.0f));
                    SPDLOG_DEBUG("Camera target moved ({}, {}, {})", 0.0f, speed, 0.0f);
                }
            },
            std::make_shared<WindowInstance::LoopCallback>(
                [this](WindowInstance& window) {
                    if (window.IsKeyPressed(KeyboardInstance::Key::D)) {
                        SPDLOG_DEBUG("Key D repeated");

                        const float speed = 0.01f;

                        this->camera_->MoveCamera(glm::vec3(-speed, 0.0f, 0.0f));
                        SPDLOG_DEBUG("Camera origin moved ({}, {}, {})", -speed, 0.0f, 0.0f);

                        this->camera_->MoveTarget(glm::vec3(-speed, 0.0f, 0.0f));
                        SPDLOG_DEBUG("Camera target moved ({}, {}, {})", -speed, 0.0f, 0.0f);
                    }
                },
                std::make_shared<WindowInstance::LoopCallback>(
                    [this](WindowInstance& window) {
                        if (window.IsKeyPressed(KeyboardInstance::Key::A)) {
                            SPDLOG_DEBUG("Key A repeated");

                            const float speed = 0.01f;

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

void ApplicationInstance::InitCallbacks_() {
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

void ApplicationInstance::InitShaders_() {
    const static std::vector<std::string> vertexShaderData {
        "shaders\\BasicShader.vert",
        "shaders\\PhongLightingShader.vert",
    };

    const static std::vector<std::string> fragmentShaderData {
        "shaders\\BasicShader.frag",
        "shaders\\NormalVisualization.frag",
        "shaders\\RedBlueGreen.frag",
        "shaders\\MagicShader.frag",
        "shaders\\RedShader.frag",
        "shaders\\PhongLightingShader.frag",
    };

    const static std::vector<std::string> geometryShaderData {
        "shaders\\BasicShader.geom"
    };

    auto vertexShaders = this->CompileShaders_(vertexShaderData, ShaderType::VERTEX_SHADER);
    auto fragmentShaders = this->CompileShaders_(fragmentShaderData, ShaderType::FRAGMENT_SHADER);
    auto geometryShaders= this->CompileShaders_(geometryShaderData, ShaderType::GEOMETRY_SHADER);

    // Creating shader programs
    this->shaderPrograms_.emplace(ApplicationInstance::LIGHTING_STR, std::make_unique<ShaderProgram>(vertexShaders.at("PhongLightingShader"), fragmentShaders.at("PhongLightingShader")));
    this->shaderPrograms_.emplace(ApplicationInstance::BASIC_MESH_SHADER_STR, std::make_unique<ShaderProgram>(vertexShaders.at("BasicShader"), fragmentShaders.at("NormalVisualization")));
    this->shaderPrograms_.emplace(ApplicationInstance::RED_SHADER_STR, std::make_unique<ShaderProgram>(vertexShaders.at("BasicShader"), fragmentShaders.at("RedShader")));
    this->shaderPrograms_.emplace(ApplicationInstance::RGB_SHADER_STR, std::make_unique<ShaderProgram>(vertexShaders.at("BasicShader"), fragmentShaders.at("RedBlueGreen")));
    this->shaderPrograms_.emplace(ApplicationInstance::MAGIC_SHADER_STR, std::make_unique<ShaderProgram>(vertexShaders.at("BasicShader"), fragmentShaders.at("MagicShader")));
    this->shaderPrograms_.emplace(ApplicationInstance::NORMALS_SHADER_STR, std::make_unique<ShaderProgram>(vertexShaders.at("BasicShader"), fragmentShaders.at("RedShader"), geometryShaders.at("BasicShader")));

    for (const auto& key : this->shaderPrograms_ | std::views::keys) {
        if (key == ApplicationInstance::NORMALS_SHADER_STR) {
            continue;
        }

        this->shaderKeys_.emplace_back(key);
    }

    this->selectedShaderKey_ = ApplicationInstance::LIGHTING_STR;
}

void ApplicationInstance::InitLighting_() {
    constexpr glm::vec3 directionalLightDirection = glm::vec3(-1.0f, -1.0f, -1.0f);
    constexpr glm::vec3 directionalLightAmbient   = glm::vec3(1.0f, 1.0f, 1.0f);
    constexpr glm::vec3 directionalLightDiffuse   = glm::vec3(1.0f, 1.0f, 1.0f);
    constexpr glm::vec3 directionalLightSpecular  = glm::vec3(1.0f, 1.0f, 1.0f);

    this->lights_.emplace(
        "directional",
        new LightInstance(
            "directional",
            directionalLightDirection,
            directionalLightAmbient,
            directionalLightDiffuse,
            directionalLightSpecular
        )
    );

    constexpr glm::vec3 pointLightPosition         = glm::vec3(100.0f, 100.0f, 100.0f);
    constexpr glm::vec3 pointLightAmbient          = glm::vec3(1.0f, 1.0f, 1.0f);
    constexpr glm::vec3 pointLightDiffuse          = glm::vec3(1.0f, 1.0f, 1.0f);
    constexpr glm::vec3 pointLightSpecular         = glm::vec3(1.0f, 1.0f, 1.0f);
    constexpr float pointLightConstantAttenuation  = 1.0f;
    constexpr float pointLightLinearAttenuation    = 1.0f;
    constexpr float pointLightQuadraticAttenuation = 1.0f;

    this->lights_.emplace(
        "point",
        new LightInstance(
            "point",
            pointLightPosition,
            pointLightAmbient,
            pointLightDiffuse,
            pointLightSpecular,
            pointLightConstantAttenuation,
            pointLightLinearAttenuation,
            pointLightQuadraticAttenuation
        )
    );

    constexpr glm::vec3 spotLightPosition         = glm::vec3(100.0f, 100.0f, 100.0f);
    constexpr glm::vec3 spotLightDirection        = glm::vec3(-1.0f, -1.0f, -1.0f);
    constexpr glm::vec3 spotLightAmbient          = glm::vec3(1.0f, 1.0f, 1.0f);
    constexpr glm::vec3 spotLightDiffuse          = glm::vec3(1.0f, 1.0f, 1.0f);
    constexpr glm::vec3 spotLightSpecular         = glm::vec3(1.0f, 1.0f, 1.0f);
    constexpr float spotLightConstantAttenuation  = 1.0f;
    constexpr float spotLightLinearAttenuation    = 1.0f;
    constexpr float spotLightQuadraticAttenuation = 1.0f;
    constexpr float spotLightExponent             = 1.0f;
    constexpr float spotLightCutoff               = 1.0f;

    this->lights_.emplace(
        "spot",
        new LightInstance(
            "spot",
            spotLightPosition,
            spotLightDirection,
            spotLightAmbient,
            spotLightDiffuse,
            spotLightSpecular,
            spotLightConstantAttenuation,
            spotLightLinearAttenuation,
            spotLightQuadraticAttenuation,
            spotLightCutoff,
            spotLightExponent
        )
    );
}

std::unordered_map<std::string, ShaderInstance> ApplicationInstance::CompileShaders_(const std::vector<std::string>& shaderFilepath, ShaderType shaderType) {
    std::unordered_map<std::string, ShaderInstance> shaders{};

    const auto getShaderName = [](const std::string& filepath) {
        static const std::regex pattern(R"((\\|/)(.+)\.(frag|geom|vert))");
        static std::smatch match{};
        std::regex_search(filepath, match, pattern);

        // 2 is for filename position
        return match[2].str();
    };

    for (const auto& filepath : shaderFilepath) {
        SPDLOG_DEBUG("Shader {} compilation started", filepath);
        shaders.emplace(getShaderName(filepath), std::move(ShaderInstance(filepath, shaderType)));
        SPDLOG_DEBUG("Shader {} compilation succeed", filepath);
    }

    return shaders;
}

void ApplicationInstance::UpdateDirectionalLight_() {
    this->lights_.at("directional")->SetDirection(
        glm::vec3(
            this->directionalLightParams_.lightDirection[0],
            this->directionalLightParams_.lightDirection[1],
            this->directionalLightParams_.lightDirection[2]
        )
    );

    this->lights_.at("directional")->SetAmbient(
        glm::vec3(
            this->directionalLightParams_.ambient[0],
            this->directionalLightParams_.ambient[1],
            this->directionalLightParams_.ambient[2]
        )
    );

    this->lights_.at("directional")->SetDiffuse(
        glm::vec3(
            this->directionalLightParams_.diffuse[0],
            this->directionalLightParams_.diffuse[1],
            this->directionalLightParams_.diffuse[2]
        )
    );

    this->lights_.at("directional")->SetSpecular(
        glm::vec3(
            this->directionalLightParams_.specular[0],
            this->directionalLightParams_.specular[1],
            this->directionalLightParams_.specular[2]
        )
    );

    this->lights_.at("directional")->SetEnable(this->directionalLightParams_.isEnable);
    this->lights_.at("directional")->SetAmbient(this->directionalLightParams_.isAmbient);
    this->lights_.at("directional")->SetDiffuse(this->directionalLightParams_.isDiffuse);
    this->lights_.at("directional")->SetSpecular(this->directionalLightParams_.isSpecular);

    this->lights_.at("directional")->SetAmbientIntensity(this->directionalLightParams_.ambientIntensity);
    this->lights_.at("directional")->SetDiffuseIntensity(this->directionalLightParams_.diffuseIntensity);
    this->lights_.at("directional")->SetSpecularIntensity(this->directionalLightParams_.specularIntensity);

    this->lights_.at("directional")->UpdateLight(*this->shaderPrograms_[this->selectedShaderKey_]);
}

void ApplicationInstance::UpdatePointLight_() {
    this->lights_.at("point")->SetPosition(
        glm::vec3(
            this->pointLightParams_.lightPosition[0],
            this->pointLightParams_.lightPosition[1],
            this->pointLightParams_.lightPosition[2]
        )
    );

    this->lights_.at("point")->SetAmbient(
        glm::vec3(
            this->pointLightParams_.ambient[0],
            this->pointLightParams_.ambient[1],
            this->pointLightParams_.ambient[2]
        )
    );

    this->lights_.at("point")->SetDiffuse(
        glm::vec3(
            this->pointLightParams_.diffuse[0],
            this->pointLightParams_.diffuse[1],
            this->pointLightParams_.diffuse[2]
        )
    );

    this->lights_.at("point")->SetSpecular(
        glm::vec3(
            this->pointLightParams_.specular[0],
            this->pointLightParams_.specular[1],
            this->pointLightParams_.specular[2]
        )
    );

    this->lights_.at("point")->SetConstantAttenuation(this->pointLightParams_.constantAttenuation);
    this->lights_.at("point")->SetLinearAttenuation(this->pointLightParams_.linearAttenuation);
    this->lights_.at("point")->SetQuadraticAttenuation(this->pointLightParams_.quadraticAttenuation);

    this->lights_.at("point")->SetEnable(this->pointLightParams_.isEnable);
    this->lights_.at("point")->SetAmbient(this->pointLightParams_.isAmbient);
    this->lights_.at("point")->SetDiffuse(this->pointLightParams_.isDiffuse);
    this->lights_.at("point")->SetSpecular(this->pointLightParams_.isSpecular);

    this->lights_.at("point")->SetAmbientIntensity(this->pointLightParams_.ambientIntensity);
    this->lights_.at("point")->SetDiffuseIntensity(this->pointLightParams_.diffuseIntensity);
    this->lights_.at("point")->SetSpecularIntensity(this->pointLightParams_.specularIntensity);

    this->lights_.at("point")->UpdateLight(*this->shaderPrograms_[this->selectedShaderKey_]);
}

void ApplicationInstance::UpdateSpotLight_() {
    this->lights_.at("spot")->SetPosition(
        glm::vec3(
            this->spotLightParams_.lightPosition[0],
            this->spotLightParams_.lightPosition[1],
            this->spotLightParams_.lightPosition[2]
        )
    );

    this->lights_.at("spot")->SetDirection(
        glm::vec3(
            this->spotLightParams_.lightDirection[0],
            this->spotLightParams_.lightDirection[1],
            this->spotLightParams_.lightDirection[2]
        )
    );

    this->lights_.at("spot")->SetAmbient(
        glm::vec3(
            this->spotLightParams_.ambient[0],
            this->spotLightParams_.ambient[1],
            this->spotLightParams_.ambient[2]
        )
    );

    this->lights_.at("spot")->SetDiffuse(
        glm::vec3(
            this->spotLightParams_.diffuse[0],
            this->spotLightParams_.diffuse[1],
            this->spotLightParams_.diffuse[2]
        )
    );

    this->lights_.at("spot")->SetSpecular(
        glm::vec3(
            this->spotLightParams_.specular[0],
            this->spotLightParams_.specular[1],
            this->spotLightParams_.specular[2]
        )
    );

    this->lights_.at("spot")->SetConstantAttenuation(this->spotLightParams_.constantAttenuation);
    this->lights_.at("spot")->SetLinearAttenuation(this->spotLightParams_.linearAttenuation);
    this->lights_.at("spot")->SetQuadraticAttenuation(this->spotLightParams_.quadraticAttenuation);
    this->lights_.at("spot")->SetExponent(this->spotLightParams_.exponent);
    this->lights_.at("spot")->SetInnerCutoff(glm::radians(this->spotLightParams_.innerCutoff));
    this->lights_.at("spot")->SetOuterCutoff(glm::radians(this->spotLightParams_.outerCutoff));

    this->lights_.at("spot")->SetEnable(this->spotLightParams_.isEnable);
    this->lights_.at("spot")->SetAmbient(this->spotLightParams_.isAmbient);
    this->lights_.at("spot")->SetDiffuse(this->spotLightParams_.isDiffuse);
    this->lights_.at("spot")->SetSpecular(this->spotLightParams_.isSpecular);

    this->lights_.at("spot")->SetAmbientIntensity(this->spotLightParams_.ambientIntensity);
    this->lights_.at("spot")->SetDiffuseIntensity(this->spotLightParams_.diffuseIntensity);
    this->lights_.at("spot")->SetSpecularIntensity(this->spotLightParams_.specularIntensity);

    this->lights_.at("spot")->UpdateLight(*this->shaderPrograms_[this->selectedShaderKey_]);
}

void ApplicationInstance::UpdateTime_() {
    const float timeInSeconds = static_cast<float>(glfwGetTime());
    const size_t hours        = static_cast<size_t>(timeInSeconds) / 3600;
    const size_t minutes      = (static_cast<size_t>(timeInSeconds) % 3600) / 60;
    const size_t seconds      = static_cast<size_t>(timeInSeconds) % 60;
    const size_t milliseconds = static_cast<size_t>(timeInSeconds * 1000) % 1000;

    this->applicationTime_.totalTimeInSeconds = timeInSeconds;
    this->applicationTime_.hours              = hours;
    this->applicationTime_.minutes            = minutes;
    this->applicationTime_.seconds            = seconds;
    this->applicationTime_.milliseconds       = milliseconds;
}
