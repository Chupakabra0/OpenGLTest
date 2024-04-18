#include "ViewportInstance/ViewportInstance.hpp"

#include <glad.h>

#include <stdexcept>

ViewportInstance::ViewportInstance(int topX, int topY, int bottomX, int bottomY, float radiansFieldOfView,
                                   float zNear, float zFar)
    : radiansFieldOfView_(radiansFieldOfView), zNear_(zNear), zFar_(zFar) {
    this->ConstructorHelper_(topX, topY, bottomX, bottomY);
}

int ViewportInstance::GetTopX() const {
    return this->topX_;
}

void ViewportInstance::SetTopX(int x) {
    if (!this->ValidateSize_(x, this->topY_, this->bottomX_, this->bottomY_)) {
        throw std::runtime_error("Error: setting top x value makes negative viewport size is invalid");
    }

    this->topX_ = x;
}

int ViewportInstance::GetTopY() const {
    return this->topY_;
}

void ViewportInstance::SetTopY(int y) {
    if (!this->ValidateSize_(this->topX_, y, this->bottomX_, this->bottomY_)) {
        throw std::runtime_error("Error: setting top y value makes negative viewport size is invalid");
    }

    this->topY_ = y;
}

int ViewportInstance::GetBottomX() const {
    return this->bottomX_;
}

void ViewportInstance::SetBottomX(int x) {
    if (!this->ValidateSize_(this->topX_, this->topY_, x, this->bottomY_)) {
        throw std::runtime_error("Error: setting bottom x value makes negative viewport size is invalid");
    }

    this->bottomX_ = x;
}

int ViewportInstance::GetBottomY() const {
    return this->bottomY_;
}

void ViewportInstance::SetBottomY(int y) {
    if (!this->ValidateSize_(this->topX_, this->topY_, this->bottomX_, y)) {
        throw std::runtime_error("Error: setting bottom y value makes negative viewport size is invalid");
    }

    this->bottomY_ = y;
}

float ViewportInstance::GetFieldOfView() const {
    return this->radiansFieldOfView_;
}

void ViewportInstance::SetFieldOfView(float fieldOfView) {
    this->radiansFieldOfView_ = fieldOfView;
}

float ViewportInstance::GetZNear() const {
    return this->zNear_;
}

void ViewportInstance::SetZNear(float zNear) {
    this->zNear_ = zNear;
}

float ViewportInstance::GetZFar() const {
    return this->zFar_;
}

void ViewportInstance::SetZFar(float zFar) {
    this->zFar_ = zFar;
}

int ViewportInstance::GetHeight() const{
    return this->bottomY_ - this->topY_;
}

int ViewportInstance::GetWidth() const {
    return this->bottomX_ - this->topX_;
}

void ViewportInstance::UpdateViewport() {
    if (this->GetWidth() != 0 && this->GetHeight() != 0) {
        glViewport(0, 0, this->GetWidth(), this->GetHeight());
    }
}

glm::mat4 ViewportInstance::CalcPerspectiveMatrix() const {
    if (this->GetHeight() == 0 || this->GetWidth() == 0) {
        return glm::identity<glm::mat4>();
    }

    return glm::perspective(
        this->radiansFieldOfView_,
        static_cast<float>(this->GetWidth()) / static_cast<float>(this->GetHeight()),
        this->zNear_, this->zFar_
    );
}

void ViewportInstance::ConstructorHelper_(int topX, int topY, int bottomX, int bottomY) {
    if (!this->ValidateSize_(topX, topY, bottomX, bottomY)) {
        throw std::runtime_error("Error: negative viewport size is invalid");
    }

    this->topX_    = topX;
    this->topY_    = topY;
    this->bottomX_ = bottomX;
    this->bottomY_ = bottomY;
}

bool ViewportInstance::ValidateSize_(int topX, int topY, int bottomX, int bottomY) {
    return bottomX - topX >= 0 && bottomY - topY >= 0;
}
