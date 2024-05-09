#pragma once

#include "ImguiWrapper/IImguiElement.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <string>

#include "imgui.h"

template<class Vec>
class ImguiSlider : public IImguiElement {
public:
    ImguiSlider() = delete;

    explicit ImguiSlider(const std::string& label, Vec& vector, float min, float max)
        : label_(label), vector_(vector), min_(min), max_(max) {
        if constexpr (typeid(Vec) == typeid(float)) {
            this->vectorArray_[0] = vector;
        }
        else if constexpr (typeid(Vec) == typeid(glm::vec2)) {
            this->vectorArray_[0]  = vector.x;
            this->vectorArray_[1]  = vector.y;
        }
        else if constexpr (typeid(Vec) == typeid(glm::vec3)) {
            this->vectorArray_[0] = vector.x;
            this->vectorArray_[1] = vector.y;
            this->vectorArray_[2] = vector.z;
        }
        else if constexpr (typeid(Vec) == typeid(glm::vec4)) {
            this->vectorArray_[0] = vector.x;
            this->vectorArray_[1] = vector.y;
            this->vectorArray_[2] = vector.z;
            this->vectorArray_[3] = vector.w;
        }
    }

    ImguiSlider(const ImguiSlider&) = default;

    ImguiSlider(ImguiSlider&&) noexcept = default;

    ImguiSlider& operator=(const ImguiSlider&) = default;

    ImguiSlider& operator=(ImguiSlider&&) noexcept = default;

    ~ImguiSlider() override = default;

    std::string GetLabel() const {
        return this->label_;
    }

    void SetLabel(const std::string& label) {
        this->label_ = label;
    }

    float GetMin() const {
        return this->min_;
    }

    void SetMin(float min) {
        this->min_ = min;
    }

    float GetMax() const {
        return this->max_;
    }

    void SetMax(float max) {
        this->max_ = max;
    }

    const Vec& GetVector() const {
        return this->vector_;
    }

    void Draw() override {
        constexpr ImGuiSliderFlags flag = ImGuiSliderFlags_AlwaysClamp;
        constexpr const char* format = "%.3f";

        if constexpr (typeid(Vec) == typeid(float)) {
            ImGui::SliderFloat(this->label_.c_str(), this->vectorArray_, this->min_, this->max_, format, flag);
            this->vector_.get() = *this->vectorArray_;
        }
        else if constexpr (typeid(Vec) == typeid(glm::vec2)) {
            ImGui::SliderFloat2(this->label_.c_str(), this->vectorArray_, this->min_, this->max_, format, flag);
            this->vector_.get().x  = this->vectorArray_[0];
            this->vector_.get().y  = this->vectorArray_[1];
        }
        else if constexpr (typeid(Vec) == typeid(glm::vec3)) {
            ImGui::SliderFloat3(this->label_.c_str(), this->vectorArray_, this->min_, this->max_, format, flag);
            this->vector_.get().x = this->vectorArray_[0];
            this->vector_.get().y = this->vectorArray_[1];
            this->vector_.get().z = this->vectorArray_[2];
        }
        else if constexpr (typeid(Vec) == typeid(glm::vec4)) {
            ImGui::SliderFloat3(this->label_.c_str(), this->vectorArray_, this->min_, this->max_, format, flag);
            this->vector_.get().x = this->vectorArray_[0];
            this->vector_.get().y = this->vectorArray_[1];
            this->vector_.get().z = this->vectorArray_[2];
            this->vector_.get().w = this->vectorArray_[3];
        }
    }

private:
    std::string label_{};
    std::reference_wrapper<Vec> vector_;
    float vectorArray_[4]{};
    float min_{};
    float max_{};
};
