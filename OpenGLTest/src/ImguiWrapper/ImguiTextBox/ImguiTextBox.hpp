#pragma once
#include "ImguiWrapper/IImguiElement.hpp"

#include <imgui.h>

#include <string>

template<class... Args>
class ImguiTextBox : public IImguiElement {
public:
    ImguiTextBox() = delete;

    explicit ImguiTextBox(const std::string& fmt, Args... args)
        :  args_(args...), fmt_(fmt) {
        
    }

    ImguiTextBox(const ImguiTextBox&) = default;

    ImguiTextBox(ImguiTextBox&&) noexcept = default;

    ImguiTextBox& operator=(const ImguiTextBox&) = default;

    ImguiTextBox& operator=(ImguiTextBox&&) noexcept = default;

    ~ImguiTextBox() override = default;

    std::string GetFmt() const {
        return this->fmt_;
    }

    void SetFmt(const std::string& fmt) {
        this->fmt_ = fmt;
    }

    void Draw() override {
        std::apply(ImGui::Text, std::tuple_cat(std::make_tuple(this->fmt_.c_str()), this->args_));
    }

private:
    std::tuple<Args...> args_{};
    std::string fmt_{};
};
