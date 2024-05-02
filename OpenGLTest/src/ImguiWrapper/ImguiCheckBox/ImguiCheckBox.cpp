#include "ImguiWrapper/ImguiCheckBox/ImguiCheckBox.hpp"

#include <imgui.h>

ImguiCheckBox::ImguiCheckBox(const std::string& label, bool& isActive)
    : label_(label), isActive_(isActive) {
        
}

void ImguiCheckBox::Draw() {
    ImGui::Checkbox(this->label_.c_str(), &this->isActive_.get());
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
