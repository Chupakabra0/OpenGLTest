#include "MouseInstance/MouseInstance.hpp"

void MouseInstance::PushNewPos(double x, double y) {
    this->mousePositionX2_ = this->mousePositionX1_;
    this->mousePositionY2_ = this->mousePositionY1_;

    this->mousePositionX1_ = x;
    this->mousePositionY1_ = y;
}

std::pair<double, double> MouseInstance::GetCurrPos() const {
    return std::make_pair(this->mousePositionX1_, this->mousePositionY1_);
}

std::pair<double, double> MouseInstance::GetPrevPos() const {
    return std::make_pair(this->mousePositionX2_, this->mousePositionY2_);
}

void MouseInstance::SetClicked(MouseInstance::Button button) {
    this->isMouseClicked_[button] = true;
}

void MouseInstance::SetUnclicked(MouseInstance::Button button) {
    this->isMouseClicked_[button] = false;
}

bool MouseInstance::IsClicked(MouseInstance::Button button) const {
    const auto find = this->isMouseClicked_.find(button);

    return find != this->isMouseClicked_.end() ?
        find->second :
        false;
}
