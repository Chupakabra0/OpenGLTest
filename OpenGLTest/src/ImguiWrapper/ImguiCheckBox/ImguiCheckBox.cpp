#include "ImguiWrapper/ImguiCheckBox/ImguiCheckBox.hpp"

#include <imgui.h>

#include <format>

ImguiCheckBox::ImguiCheckBox(const std::string& label, bool& isActive)
    : label_(label), isActive_(isActive) {
        
}

void ImguiCheckBox::Draw() {
    const std::string label = std::format("{}##{}", this->label_, reinterpret_cast<unsigned long long>(this));

    ImGui::Checkbox(label.c_str(), &this->isActive_.get());
}

std::string ImguiCheckBox::GetLabel() const {
    return this->label_;
}

void ImguiCheckBox::SetLabel(const std::string& label) {
    this->label_ = label;
}

bool ImguiCheckBox::IsActive() const {
    return this->isActive_.get();
}
