#pragma once
#include "ImguiWrapper/IImguiElement.hpp"

#include <glm/vec3.hpp>

#include <string>

class ImguiColorPicker : public IImguiElement {
public:
    ImguiColorPicker() = delete;

    explicit ImguiColorPicker(const std::string& label, glm::vec3& color);

    ImguiColorPicker(const ImguiColorPicker&) = default;

    ImguiColorPicker(ImguiColorPicker&&) noexcept = default;

    ImguiColorPicker& operator=(const ImguiColorPicker&) = default;

    ImguiColorPicker& operator=(ImguiColorPicker&&) noexcept = default;

    ~ImguiColorPicker() override = default;

    std::string GetLabel() const;

    void SetLabel(const std::string& label);

    const glm::vec3& GetColor() const;

    void Draw() override;

private:
    std::string label_{};
    std::reference_wrapper<glm::vec3> color_;
    float colorArray_[3]{};
};
