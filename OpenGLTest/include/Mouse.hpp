#pragma once
#include <unordered_map>

class Mouse {
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

    explicit Mouse() = default;

    Mouse(const Mouse&) = default;

    Mouse(Mouse&&) noexcept = default;

    Mouse& operator=(const Mouse&) = default;

    Mouse& operator=(Mouse&&) noexcept = default;

    ~Mouse() = default;

    void PushNewPos(double x, double y) {
        this->mousePositionX2_ = this->mousePositionX1_;
        this->mousePositionY2_ = this->mousePositionY1_;

        this->mousePositionX1_ = x;
        this->mousePositionY1_ = y;
    }

    std::pair<double, double> GetCurrPos() const {
        return std::make_pair(this->mousePositionX1_, this->mousePositionY1_);
    }

    std::pair<double, double> GetPrevPos() const {
        return std::make_pair(this->mousePositionX2_, this->mousePositionY2_);
    }

    void SetClicked(Mouse::Button button) {
        this->isMouseClicked_[button] = true;
    }

    void SetUnclicked(Mouse::Button button) {
        this->isMouseClicked_[button] = false;
    }

    bool IsClicked(Mouse::Button button) const {
        const auto find = this->isMouseClicked_.find(button);

        return find != this->isMouseClicked_.end() ?
            find->second :
            false;
    }

private:
    double mousePositionX2_{};
    double mousePositionY2_{};
    double mousePositionX1_{};
    double mousePositionY1_{};
    std::unordered_map<Mouse::Button, bool> isMouseClicked_{};
};

inline int ConvertMouseButtonToCode(Mouse::Button button);
inline Mouse::Button ConvertCodeToMouseButton(int buttonCode);

#if defined(CONTROL_GLFW)
    int ConvertMouseButtonToCode(Mouse::Button button) {
        return static_cast<int>(button);
    }

    Mouse::Button ConvertCodeToMouseButton(int buttonCode) {
        return static_cast<Mouse::Button>(buttonCode);
    }
#endif
