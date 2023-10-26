#pragma once
#include "DataObject.hpp"
#include "Window.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class ImguiWrapper : public BindableDataObject {
public:
    ImguiWrapper() = delete;

    ImguiWrapper(const ImguiWrapper&) = delete;

    ImguiWrapper(ImguiWrapper&&) noexcept = default;

    ImguiWrapper& operator=(ImguiWrapper&) = delete;

    ImguiWrapper& operator=(ImguiWrapper&&) noexcept = default;

    static ImguiWrapper& GetInstance(Window& window) {
        static ImguiWrapper imgui{window};
        return imgui;
    }

    ~ImguiWrapper() override {
        this->DestroyHelper_();
    }

    void Bind() override;

    void Unbind() override;

    ImGuiIO* GetIO() const {
        return this->io_;
    }

private:
    ImGuiIO* io_;

    explicit ImguiWrapper(Window& window) {
        this->ConstructorHelper_(window);
    }

    void ConstructorHelper_(Window& window);

    void DestroyHelper_();

    void CorrectImguiIni_();
};

