#pragma once
#include "ImguiWrapper/IImguiElement.hpp"

#include <string>

class ImguiCheckBox  : public IImguiElement {
public:
    ImguiCheckBox() = delete;

    explicit ImguiCheckBox(const std::string& label, bool& isActive);

    ImguiCheckBox(const ImguiCheckBox&) = default;

    ImguiCheckBox(ImguiCheckBox&&) noexcept = default;

    ImguiCheckBox& operator=(const ImguiCheckBox&) = default;

    ImguiCheckBox& operator=(ImguiCheckBox&&) noexcept = default;

    ~ImguiCheckBox() override = default;

    void Draw() override;

    std::string GetLabel() const;

    void SetLabel(const std::string& label);

    bool IsActive() const;

private:
    std::string label_{};
    std::reference_wrapper<bool> isActive_;
};
