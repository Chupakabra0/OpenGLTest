#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

#include <iostream>
#include <vector>
#include <format>

#include "VertexBufferObject.hpp"
#include "VertexArrayObject.hpp"
#include "ShaderProgram.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Viewport.hpp"

#include "TextureLoader/TextureLoaderCV.hpp"
#include "TextureLoader/TextureLoaderSTB.hpp"

#include "ImguiWrapper.hpp"

#include "MeshGenerators/ParallelepipedGenerator.hpp"
#include "MeshGenerators/UVSphereGenerator.hpp"
#include "MeshGenerators/IcosahedronGenerator.hpp"
#include "MeshGenerators/ConeGenerator.hpp"

int main(int argc, char** argv) {
    try {
        // Create window context
        constexpr int windowHeight{720};
        constexpr int windowWidth{1280};

        // Init window & GLFW
        Window window{windowHeight, windowWidth, "OpenGL Test"};

        // Init imgui
        ImguiWrapper& imgui = ImguiWrapper::GetInstance(window);

        // GLAD (or GLEW, whatever) init
        Renderer& renderer = Renderer::GetInstance();

        // Checking Open GL version
        std::cout << std::format("OpenGL version: {}\n", renderer.GetVersionStr());

        // Determining positions, colors etc
        constexpr float rgbLimit{255.0f};
        const glm::vec4 backgroundColor{125.0f, 0.0f, 255.0f, 255.0f};
        const glm::vec4 foregroundColor{175.0f, 60.0f, 75.0f, 255.0f};

        // Mesh generate
        const glm::vec3 origin{0.0f, 0.0f, 0.0f};
        const float size{150.0f};
        const int segments{10};
        const int slices{10};
        UVSphereGenerator gener(size, segments, slices, origin, glm::vec3(0.0));
        MeshClass mesh{gener.GenerateMesh()};

        // Ibo/vao init
        IndexBufferObject* ibo = new IndexBufferObject(mesh.GenerateIBO());
        VertexArrayObject vao  = mesh.GenerateVAO(ibo);

        // Create texture
        //std::shared_ptr<ITextureLoader> textureLoader = std::make_shared<TextureLoaderSTB>();
        //const int textureSlot{0};
        //Texture texture{"resources\\textures\\paper-sheet.png", textureSlot, textureLoader};
        //DataObjectGuard textureGuard{texture};

        // MVP matrix
        glm::mat4 modelMatrix{glm::identity<glm::mat4>()};
        glm::mat4 viewMatrix{glm::identity<glm::mat4>()};
        glm::mat4 projectionMatrix{glm::identity<glm::mat4>()};

        // Camera
        Camera camera(
            glm::vec3(origin.x, origin.y, 400.0f),
            glm::vec3(origin.x, origin.y, origin.z),
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, -1.0f)
        );

        // Viewport
        const float fieldOfViewStep    = 3.0f;
        const float fieldOfViewDegrees = 90.0f;
        Viewport viewport(
            0, 0, window.GetWidth(), window.GetHeight(),
            glm::radians(fieldOfViewDegrees), 0.1f, 500.0f
        );

        // Window callbacks generate
        const auto mouseButtonCallback = std::make_shared<Window::MouseClickCallback>(
            [&imgui](Window& window, Mouse::Button button, ControlAction action, ControlMods mods, double xpos, double ypos) {
                if (imgui.GetIO()->WantCaptureMouse) {
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
                [&imgui](Window& window, Mouse::Button button, ControlAction action, ControlMods mods, double xpos, double ypos) {
                    if (imgui.GetIO()->WantCaptureMouse) {
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

        const auto mouseMoveCallback = std::make_shared<Window::MouseMoveCallback>(
            [&camera, &imgui](Window& window, double xpos, double ypos) {
                if (imgui.GetIO()->WantCaptureMouse) {
                    return;
                }

                if (window.IsMouseClicked(Mouse::Button::LEFT)) {
                    window.UpdateCursorPosition();

                    auto [x1, y1] = window.GetPrevCursorPos();
                    auto [x2, y2] = window.GetCurrCursorPos();

                    camera.Pan(static_cast<float>(x2 - x1), static_cast<float>(y2 - y1), 1.0f);
                }
            },
            std::make_shared<Window::MouseMoveCallback>(
                [&camera, &imgui](Window& window, double xpos, double ypos) {
                    if (imgui.GetIO()->WantCaptureMouse) {
                        return;
                    }

                    if (window.IsMouseClicked(Mouse::Button::RIGHT)) {
                        window.UpdateCursorPosition();

                        const float RADIUS = 1.0f;

                        auto [x1, y1] = window.GetPrevCursorPos();
                        auto [x2, y2] = window.GetCurrCursorPos();

                        camera.Arcball(
                            static_cast<float>(x2 - x1),
                            static_cast<float>(y2 - y1),
                            static_cast<float>(window.GetHeight()),
                            static_cast<float>(window.GetWidth())
                        );
                    }
                }
            )
        );

        const auto mouseScrollCallback = std::make_shared<Window::MouseScrollCallback>(
            [&viewport, &imgui, &fieldOfViewStep](Window& window, double xpos, double ypos) {
                if (imgui.GetIO()->WantCaptureMouse) {
                    return;
                }

                viewport.SetFieldOfView(
                    glm::radians(
                        glm::degrees(viewport.GetFieldOfView()) + (ypos > 0 ? -fieldOfViewStep : fieldOfViewStep)
                    )
                );
            }
        );

        const auto windowResizeCallback = std::make_shared<Window::WindowResizeCallback>(
            [&viewport](Window& window, int width, int height) {
                viewport.SetBottomX(width);
                viewport.SetBottomY(height);
                viewport.UpdateViewport();

                std::cout << std::format("Window resized to {} x {}\n", width, height);
            }
        );

        const auto keyPressCallback = std::make_shared<Window::KeyPressCallback>(
            [&camera](Window& window, Keyboard::Key key, int scancode, ControlAction action, ControlMods mods) {
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
                [&camera](Window& window, Keyboard::Key key, int scancode, ControlAction action, ControlMods mods) {
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
                    [&camera](Window& window, Keyboard::Key key, int scancode, ControlAction action, ControlMods mods) {
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
                        [&camera](Window& window, Keyboard::Key key, int scancode, ControlAction action, ControlMods mods) {
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

        const auto loopCallback = std::make_shared<Window::LoopCallback>(
            [&camera](Window& window) {
                if (window.IsKeyPressed(Keyboard::Key::W)) {
                    const float speed = 1.0f;

                    camera.MoveCamera(glm::vec3(0.0f, -speed, 0.0f));
                    camera.MoveTarget(glm::vec3(0.0f, -speed, 0.0f));
                }
            },
            std::make_shared<Window::LoopCallback>(
                [&camera](Window& window) {
                    if (window.IsKeyPressed(Keyboard::Key::S)) {
                        const float speed = 1.0f;

                        camera.MoveCamera(glm::vec3(0.0f, speed, 0.0f));
                        camera.MoveTarget(glm::vec3(0.0f, speed, 0.0f));
                    }
                },
                std::make_shared<Window::LoopCallback>(
                    [&camera](Window& window) {
                        if (window.IsKeyPressed(Keyboard::Key::D)) {
                            const float speed = 1.0f;

                            camera.MoveCamera(glm::vec3(-speed, 0.0f, 0.0f));
                            camera.MoveTarget(glm::vec3(-speed, 0.0f, 0.0f));
                        }
                    },
                    std::make_shared<Window::LoopCallback>(
                        [&camera](Window& window) {
                            if (window.IsKeyPressed(Keyboard::Key::A)) {
                                const float speed = 1.0f;

                                camera.MoveCamera(glm::vec3(speed, 0.0f, 0.0f));
                                camera.MoveTarget(glm::vec3(speed, 0.0f, 0.0f));
                            }
                        }
                    )
                )
            )
        );

        const auto refreshCallback = std::make_shared<Window::WindowRefreshCallback>();

        // Window callbacks settings
        window.SetMouseClickCallback(mouseButtonCallback);
        window.SetMouseMoveCallback(mouseMoveCallback);
        window.SetMouseScrollCallback(mouseScrollCallback);
        window.SetResizeCallback(windowResizeCallback);
        window.SetKeyPressCallback(keyPressCallback);
        window.SetLoopCallback(loopCallback);
        window.SetRefreshCallback(refreshCallback);

        // Creating shaders
        Shader basicVertexShader{"shaders\\BasicShader.vert", ShaderType::VERTEX_SHADER};
        Shader basicFragmentShader{"shaders\\BasicShader.frag", ShaderType::FRAGMENT_SHADER};
        Shader normalVisualizationFragmentShader{"shaders\\NormalVisualization.frag", ShaderType::FRAGMENT_SHADER};
        Shader redBlueGreenFragmentShader{"shaders\\RedBlueGreen.frag", ShaderType::FRAGMENT_SHADER};
        Shader magicFragmentShader{"shaders\\MagicShader.frag", ShaderType::FRAGMENT_SHADER};
        Shader redFragmentShader{"shaders\\RedShader.frag", ShaderType::FRAGMENT_SHADER};
        Shader basicGeometryShader{"shaders\\BasicShader.geom", ShaderType::GEOMETRY_SHADER};

        // Creating shader programs
        ShaderProgram normalsShaderProgram{basicVertexShader, redFragmentShader, basicGeometryShader};
        ShaderProgram meshShaderProgram{basicVertexShader, normalVisualizationFragmentShader};

        // Main loop
        while (!window.ShouldWindowClose()) {
            const float timeInSeconds = static_cast<float>(glfwGetTime());

            const int hours        = static_cast<int>(timeInSeconds) / 3600;
            const int minutes      = (static_cast<int>(timeInSeconds) % 3600) / 60;
            const int seconds      = static_cast<int>(timeInSeconds) % 60;
            const int milliseconds = static_cast<int>(timeInSeconds * 1000) % 1000;

            static ImVec4 clear_color{
                backgroundColor.r / rgbLimit,
                backgroundColor.g / rgbLimit,
                backgroundColor.b / rgbLimit,
                backgroundColor.a / rgbLimit
            };
            static float viewPos[]{ origin.x, origin.y, 400.0f };
            static float viewRotate[]{ 0.0f, 0.0f, 0.0f };
            static bool isFlatShading{};
            static bool isDrawNormals{};

            renderer.ClearScreen(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

            //const auto tempModelMatrix = modelMatrix;

            //for (int i = 0; i < 1; ++i) {
                //if (i > 0) {
                //    modelMatrix *=
                //        glm::translate(origin) *
                //        glm::scale(glm::vec3(1.0f / glm::sqrt(2.0f), 1.0f / glm::sqrt(2.0f), 1.0f)) *
                //        glm::rotate(
                //            glm::radians((i % 2 == 0 ? 1.0f : -1.0f) * (45.0f + static_cast<float>(timeInSeconds) * glm::sqrt(2.0f) * static_cast<float>(15 - i))),
                //            glm::vec3(0.0f, 0.0f, 1.0f)
                //        ) *
                //        glm::translate(-origin + glm::vec3(0.0f, 0.0f, 0.001f * i));
                //}

                //camera.SetX(glm::vec3(1.0f, 0.0f, 0.0f));
                //camera.SetY(glm::vec3(0.0f, 1.0f, 0.0f));
                //camera.SetZ(glm::vec3(0.0f, 0.0f, -1.0f));
                //camera.SetOrigin(glm::vec3(viewPos[0], viewPos[1], viewPos[2]));

                //camera.RotateCamera(origin, glm::vec3(glm::radians(viewRotate[0]), glm::radians(viewRotate[1]), glm::radians(viewRotate[2])));

                viewMatrix = camera.CalcViewMatrix();

                projectionMatrix = viewport.CalcPerspectiveMatrix();

                normalsShaderProgram.SetUniformMatrix("u_proj", projectionMatrix);
                normalsShaderProgram.SetUniformMatrix("u_view", viewMatrix);
                normalsShaderProgram.SetUniformMatrix("u_model", modelMatrix);

                meshShaderProgram.SetUniformPairFloat("u_resolution", static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()));
                meshShaderProgram.SetUniformMatrix("u_proj", projectionMatrix);
                meshShaderProgram.SetUniformMatrix("u_view", viewMatrix);
                meshShaderProgram.SetUniformMatrix("u_model", modelMatrix);
                meshShaderProgram.SetUniformInt("u_isFlat", isFlatShading);

                if (isDrawNormals) {
                    renderer.DrawIndecies(vao, normalsShaderProgram);
                }
                
                renderer.DrawIndecies(vao, meshShaderProgram);
            //}

            //modelMatrix = tempModelMatrix;

            meshShaderProgram.SetUniformFloat("u_time", timeInSeconds);

            imgui.Bind();

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
            ImGui::Text(std::format("Field of view: {:.2f} degrees", glm::degrees(viewport.GetFieldOfView())).c_str());
            ImGui::Text("Application data:");
            ImGui::Text(std::format("Application average {:.0f} FPS", ImGui::GetIO().Framerate).c_str());
            ImGui::Text(std::format("Application time: {:02d}:{:02d}:{:02d}:{:02d}", hours, minutes, seconds, milliseconds).c_str());
            ImGui::End();

            imgui.Unbind();

            window.PollEvents();
            window.SwapBuffers();
        }
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
