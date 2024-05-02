#pragma once

struct IImguiElement {
public:
    explicit IImguiElement() = default;

    IImguiElement(const IImguiElement&) = default;

    IImguiElement(IImguiElement&&) noexcept = default;

    IImguiElement& operator=(const IImguiElement&) = default;

    IImguiElement& operator=(IImguiElement&&) noexcept = default;

    virtual ~IImguiElement() = default;

    virtual void Draw() = 0;
};
