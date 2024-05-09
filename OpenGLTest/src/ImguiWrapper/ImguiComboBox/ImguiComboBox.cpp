#include "ImguiWrapper/ImguiComboBox/ImguiComboBox.hpp"

#include <imgui.h>

#include <format>

std::string ImguiComboBox::GetLabel() const {
    return this->label_;
}

void ImguiComboBox::SetLabel(const std::string& label) {
    this->label_ = label;
}

const std::string& ImguiComboBox::GetSelectedValue() const {
    return this->values_.at(this->selectedIndex_);
}

int ImguiComboBox::GetSelectedIndex() const {
    return this->selectedIndex_;
}

const std::vector<std::string>& ImguiComboBox::GetValues() const {
    return this->values_;
}

void ImguiComboBox::SetValues(const std::vector<std::string>& values) {
    this->values_ = values;
}

void ImguiComboBox::Draw() {
    if (this->selectedIndex_ == -1) {
        return;
    }

    const std::string label = std::format("{}##{}", this->label_, reinterpret_cast<unsigned long long>(this));

    if (ImGui::BeginCombo(label.c_str(), this->values_.at(this->selectedIndex_).c_str())) {
        for (int i = 0; i < this->values_.size(); ++i) {
            const bool isSelected = this->selectedIndex_ == i;

            if (ImGui::Selectable(this->values_.at(i).c_str(), isSelected)) {
                this->selectedIndex_ = i;
            }

            if (isSelected) {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }

    this->selectedValue_.get() = this->values_.at(this->selectedIndex_);
}
