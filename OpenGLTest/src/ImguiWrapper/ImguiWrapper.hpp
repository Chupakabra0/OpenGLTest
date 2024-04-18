#pragma once
#include "BindableDataObject/BindableDataObject.hpp"
#include "WindowInstance/WindowInstance.hpp"

#include <imgui.h>

class ImguiWrapper : public BindableDataObject {
public:
    ImguiWrapper() = delete;

    ImguiWrapper(const ImguiWrapper&) = delete;

    ImguiWrapper(ImguiWrapper&&) noexcept = default;

    ImguiWrapper& operator=(ImguiWrapper&) = delete;

    ImguiWrapper& operator=(ImguiWrapper&&) noexcept = default;

    static ImguiWrapper& GetInstance(WindowInstance& window);

    ~ImguiWrapper() override;

    void Bind() override;

    void Unbind() override;

    ImGuiIO* GetIO() const;

private:
    ImGuiIO* io_;

    explicit ImguiWrapper(WindowInstance& window);

    void ConstructorHelper_(WindowInstance& window);

    void DestroyHelper_();

    void CorrectImguiIni_();
};
