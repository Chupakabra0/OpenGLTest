#pragma once
#include "ImguiWrapper/IImguiElement.hpp"

#include <string>
#include <vector>

class ImguiComboBox : public IImguiElement {
public:
    ImguiComboBox() = delete;

    template<class... Args>
    explicit ImguiComboBox(const std::string label, std::string& selectedValue, Args... args)
        : label_(label), selectedValue_(selectedValue) {
        (this->values_.emplace_back(args), ...);
        this->selectedIndex_ = this->values_.empty() ? -1 : 0;
    }

    explicit ImguiComboBox(const std::string label, std::string& selectedValue, const std::vector<std::string>& values)
        : values_(values), label_(label), selectedValue_(selectedValue) {
        this->selectedIndex_ = this->values_.empty() ? -1 : 0;
    }

    ImguiComboBox(const ImguiComboBox&) = default;

    ImguiComboBox(ImguiComboBox&&) noexcept = default;

    ImguiComboBox& operator=(const ImguiComboBox&) = default;

    ImguiComboBox& operator=(ImguiComboBox&&) noexcept = default;

    ~ImguiComboBox() override = default;

    std::string GetLabel() const;

    void SetLabel(const std::string& label);

    const std::string& GetSelectedValue() const;

    int GetSelectedIndex() const;

    const std::vector<std::string>& GetValues() const;

    void SetValues(const std::vector<std::string>& values);

    void Draw() override;

private:
    std::vector<std::string> values_{};
    std::string label_{};
    std::reference_wrapper<std::string> selectedValue_;
    int selectedIndex_{};
};
