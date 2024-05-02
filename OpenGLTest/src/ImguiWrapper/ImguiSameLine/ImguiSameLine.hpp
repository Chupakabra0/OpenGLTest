#pragma once
#include "ImguiWrapper/IImguiElement.hpp"

class ImguiSameLine : public IImguiElement {
public:
    explicit ImguiSameLine() = default;

    ImguiSameLine(const ImguiSameLine&) = default;

    ImguiSameLine(ImguiSameLine&&) noexcept = default;

    ImguiSameLine& operator=(const ImguiSameLine&) = default;

    ImguiSameLine& operator=(ImguiSameLine&&) noexcept = default;

    ~ImguiSameLine() override = default;

    void Draw() override;
};