#pragma once
#include <unordered_map>

class MouseInstance {
public:
    enum class Button : short {
        LEFT         = 0,
        RIGHT        = 1,
        MIDDLE       = 2,
        ADDITIONAL_1 = 3,
        ADDITIONAL_2 = 4,
        ADDITIONAL_3 = 5,
        ADDITIONAL_4 = 6,
        ADDITIONAL_5 = 7
    };

    explicit MouseInstance() = default;

    MouseInstance(const MouseInstance&) = default;

    MouseInstance(MouseInstance&&) noexcept = default;

    MouseInstance& operator=(const MouseInstance&) = default;

    MouseInstance& operator=(MouseInstance&&) noexcept = default;

    ~MouseInstance() = default;

    void PushNewPos(double x, double y);

    std::pair<double, double> GetCurrPos() const;

    std::pair<double, double> GetPrevPos() const;

    void SetClicked(MouseInstance::Button button);

    void SetUnclicked(MouseInstance::Button button);

    bool IsClicked(MouseInstance::Button button) const;

private:
    double mousePositionX2_{};
    double mousePositionY2_{};
    double mousePositionX1_{};
    double mousePositionY1_{};
    std::unordered_map<MouseInstance::Button, bool> isMouseClicked_{};
};

inline int ConvertMouseButtonToCode(MouseInstance::Button button) {
    return static_cast<int>(button);
}

inline MouseInstance::Button ConvertCodeToMouseButton(int buttonCode) {
    return static_cast<MouseInstance::Button>(buttonCode);
}
