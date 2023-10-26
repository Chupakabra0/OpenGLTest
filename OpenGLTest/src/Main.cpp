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

#include "TextureLoader/TextureLoaderCV.hpp"
#include "TextureLoader/TextureLoaderSTB.hpp"

#include "ImguiWrapper.hpp"

#include "MeshGenerators/ParallelepipedGenerator.hpp"
#include "MeshGenerators/UVSphereGenerator.hpp"
#include "MeshGenerators/IcosahedronGenerator.hpp"
#include "MeshGenerators/ConeGenerator.hpp"
#include <Camera.hpp>

int main(int argc, char** argv) {
    try {
        // Create window context
        constexpr int windowHeight{720};
        constexpr int windowWidth{1280};

        // Init window & GLFW
        Window window {
            windowHeight, windowWidth, "OpenGL Test",
            [](Window& window, int button, int action, int mods, double xpos, double ypos) {
                std::cout << std::format("Click! Button = {}, Action = {}, Mods = {}\n", button, action, mods);
                std::cout << std::format("X: {}, Y: {}\n", xpos, ypos);
            },
            [](Window&, double, double) {
            },
            [](Window& window, int key, int scancode, int action, int mods) {
                std::cout << std::format("Pressed! Key = {}, Scancode = {}, Action = {}, Mods = {}\n", key, scancode, action, mods);
            },
            [](Window& window, double xoffset, double yoffset) {
                std::cout << std::format("Scrolled! X: {}, Y: {}\n", xoffset, yoffset);
            },
            [](Window& window, int width, int height) {
                window.SetWidth(width);
                window.SetHeight(height);

                std::cout << std::format("Window resized to {} x {}\n", width, height);
            }
        };

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

        //const glm::vec3 origin{static_cast<float>(window.GetWidth()) / 2.0f, static_cast<float>(window.GetHeight()) / 2.0f, 0.0f};
        const glm::vec3 origin{0.0f, 0.0f, 0.0f};
        const float size{150.0f};
        const int segments{10};
        const int slices{10};

        //ParallelepipedGenerator gener(
        //    size, size, size,
        //    origin, glm::vec3(0.0, 0.0, 0.0)
        //);
        //IcosahedronGenerator gener(100.0f, origin, glm::vec3(0.0));
        UVSphereGenerator gener(size, segments, slices, origin, glm::vec3(0.0));
        //ConeGenerator gener(300.0f, 100.0f, 100, 1, origin - glm::vec3(0.0f, 150.0f, 0.0f), glm::zero<glm::vec3>());

        MeshClass mesh{gener.GenerateMesh()};

        // Ibo init
        IndexBufferObject* ibo = new IndexBufferObject(mesh.GenerateIBO());
        VertexArrayObject vao  = mesh.GenerateVAO(ibo);

        // Create texture
        std::shared_ptr<ITextureLoader> textureLoader = std::make_shared<TextureLoaderSTB>();
        const int textureSlot{0};
        Texture texture{"resources\\textures\\paper-sheet.png", textureSlot, textureLoader};
        DataObjectGuard textureGuard{texture};

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

        // Window callbacks
        window.SetMouseButtonCallback([&camera, &imgui](Window& window, int button, int action, int mods, double xpos, double ypos) {
            if (imgui.GetIO()->WantCaptureMouse) {
                return;
            }
            
            if (button == GLFW_MOUSE_BUTTON_1 || button == GLFW_MOUSE_BUTTON_2) {
                if (action == 1) {
                    window.UpdateCursorPosition();
                    window.SetMouseClicked(button);
                }
                else if (action == 0) {
                    window.ResetCursorPosition();
                    window.SetMouseUnclicked(button);
                }
            }
        });
        window.SetCursorPosCallback([&camera, &imgui](Window& window, double xpos, double ypos) {
            if (imgui.GetIO()->WantCaptureMouse) {
                return;
            }

            if (window.IsMouseClicked(GLFW_MOUSE_BUTTON_1)) {
                window.UpdateCursorPosition();

                auto [x1, y1] = window.GetPrevCursorPos();
                auto [x2, y2] = window.GetCurrCursorPos();

                camera.Pan(static_cast<float>(x2 - x1), static_cast<float>(y2 - y1), 1.0f);
            }
            else if (window.IsMouseClicked(GLFW_MOUSE_BUTTON_2)) {
                window.UpdateCursorPosition();

                const float RADIUS = 1.0f;

                auto [x1, y1] = window.GetPrevCursorPos();
                auto [x2, y2] = window.GetCurrCursorPos();

                camera.Arcball(static_cast<float>(x1), static_cast<float>(y1), static_cast<float>(x2), static_cast<float>(y2));
            }
        });

        // Creating shader program
        Shader basicVertexShader{"shaders\\BasicShader.vert", ShaderType::VERTEX_SHADER};
        Shader basicFragmentShader{"shaders\\BasicShader.frag", ShaderType::FRAGMENT_SHADER};
        Shader normalVisualizationFragmentShader{"shaders\\NormalVisualization.frag", ShaderType::FRAGMENT_SHADER};
        Shader redBlueGreenFragmentShader{"shaders\\RedBlueGreen.frag", ShaderType::FRAGMENT_SHADER};
        Shader magicFragmentShader{"shaders\\MagicShader.frag", ShaderType::FRAGMENT_SHADER};
        Shader redFragmentShader{"shaders\\RedShader.frag", ShaderType::FRAGMENT_SHADER};
        Shader basicGeometryShader{"shaders\\BasicShader.geom", ShaderType::GEOMETRY_SHADER};

        ShaderProgram normalsShaderProgram{basicVertexShader, redFragmentShader, basicGeometryShader};
        ShaderProgram meshShaderProgram{basicVertexShader, normalVisualizationFragmentShader};
        meshShaderProgram.SetUniformInt("u_texture", textureSlot);

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
            static float fovDegrees{ 90.0f };
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

                viewMatrix = camera.GetViewMatrix();

                projectionMatrix = 
                    glm::perspective(glm::radians(fovDegrees),
                        static_cast<float>(window.GetWidth()) / static_cast<float>(window.GetHeight()),
                        0.1f,
                        10000.0f
                    );

                normalsShaderProgram.SetUniformMatrix("u_proj", projectionMatrix);
                normalsShaderProgram.SetUniformMatrix("u_view", viewMatrix);
                normalsShaderProgram.SetUniformMatrix("u_model", modelMatrix);

                meshShaderProgram.SetUniformPairFloat("u_resolution", static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()));
                meshShaderProgram.SetUniformMatrix("u_proj", projectionMatrix);
                meshShaderProgram.SetUniformMatrix("u_view", viewMatrix);
                meshShaderProgram.SetUniformMatrix("u_model", modelMatrix);
                //meshShaderProgram.SetUniformInt("u_count", i);
                meshShaderProgram.SetUniformInt("u_isFlat", isFlatShading);

                if (isDrawNormals) {
                    renderer.DrawIndecies(vao, normalsShaderProgram);
                }
                
                renderer.DrawIndecies(vao, meshShaderProgram);
            //}

            //modelMatrix = tempModelMatrix;

            meshShaderProgram.SetUniformFloat("u_time", timeInSeconds);

            glViewport(0, 0, window.GetWidth(), window.GetHeight());

            imgui.Bind();

            const ImVec2 center{ImGui::GetMainViewport()->GetCenter().x, 0.0f};
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            ImGui::Begin("Hello, world!");
            ImGui::Text("Background color:");
            ImGui::ColorEdit3("Clear color", reinterpret_cast<float*>(&clear_color));
            //ImGui::SliderFloat3("Camera pos", viewPos, -1000.0f, 1000.0f);
            //ImGui::SliderFloat3("Camera rotate:", viewRotate, -360.0f, 360.0f);
            //ImGui::SliderFloat("FOV Y", &fovDegrees, 0.1f, 90.0f);
            //if (ImGui::Button("Reset", ImVec2(50, 25))) {
            //    viewPos[0] = origin.x;
            //    viewPos[1] = origin.y;
            //    viewPos[2] = 400.0f;

            //    viewRotate[0] = 0.0f;
            //    viewRotate[1] = 0.0f;
            //    viewRotate[2] = 0.0f;

            //    fovDegrees = 90.0f;
            //}
            ImGui::Text("Display settings:");
            ImGui::Checkbox("Flat shading", &isFlatShading);
            ImGui::SameLine();
            ImGui::Checkbox("Draw normals", &isDrawNormals);
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
