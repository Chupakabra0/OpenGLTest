#include "ImguiWrapper/ImguiColorPicker/ImguiColorPicker.hpp"

#include <imgui.h>

ImguiColorPicker::ImguiColorPicker(const std::string& label, glm::vec3& color)
    : label_(label), color_(color) {
    this->colorArray_[0] = this->color_.get().r;
    this->colorArray_[1] = this->color_.get().g;
    this->colorArray_[2] = this->color_.get().b;
}

std::string ImguiColorPicker::GetLabel() const {
    return this->label_;
}

void ImguiColorPicker::SetLabel(const std::string& label) {
    this->label_ = label;
}

const glm::vec3& ImguiColorPicker::GetColor() const {
    return this->color_;
}

void ImguiColorPicker::Draw() {
    ImGui::ColorEdit3(this->label_.c_str(), this->colorArray_, ImGuiColorEditFlags_PickerHueWheel);
    this->color_.get().r = this->colorArray_[0];
    this->color_.get().g = this->colorArray_[1];
    this->color_.get().b = this->colorArray_[2];
}
