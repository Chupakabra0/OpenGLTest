#pragma once
#include "BindableDataObject/BindableDataObject.hpp"
#include "WindowInstance/WindowInstance.hpp"
#include "ImguiWrapper/IImguiElement.hpp"

#include <imgui.h>

using UniqueImguiIo = std::unique_ptr<ImGuiIO, decltype([](ImGuiIO*) {})>;

class ImguiWrapper : public BindableDataObject {
public:
    explicit ImguiWrapper(WindowInstance& window, const std::string& title, float x, float y, float xPivot = 0.0f, float yPivot = 0.0f);

    ImguiWrapper(const ImguiWrapper&) = delete;

    ImguiWrapper(ImguiWrapper&&) noexcept = default;

    ImguiWrapper& operator=(ImguiWrapper&) = delete;

    ImguiWrapper& operator=(ImguiWrapper&&) noexcept = default;

    ~ImguiWrapper() override;

    void Bind() override;

    void Unbind() override;

    const ImGuiIO* GetIO() const;

    ImGuiIO* GetIO();

    void DrawAll();

    void AddElement(const std::shared_ptr<IImguiElement>& uiElement);

private:
    std::vector<std::shared_ptr<IImguiElement>> elements_{};
    std::string title_{};
    UniqueImguiIo io_{};
    float x_{};
    float y_{};
    float xPivot_{};
    float yPivot_{};

    void ConstructorHelper_(WindowInstance& window);

    void DestroyHelper_();

    void CorrectImguiIni_();

    void BeginDrawingWindow_();

    void EndDrawingWindow_();
};
