#pragma once
#include "glad/glad.h"
#include "Camera.hpp"

#include <memory>
#include <stdexcept>

class Viewport {
public:
    Viewport() = delete;

    explicit Viewport(int topX, int topY, int bottomX, int bottomY,
        float radiansFieldOfView, float zNear, float zFar)
        : radiansFieldOfView_(radiansFieldOfView), zNear_(zNear), zFar_(zFar) {
        this->ConstructorHelper_(topX, topY, bottomX, bottomY);
    }

    Viewport(const Viewport&) = default;

    Viewport(Viewport&&) noexcept = default;

    Viewport& operator=(const Viewport&) = default;

    Viewport& operator=(Viewport&&) noexcept = default;

    ~Viewport() = default;

    int GetTopX() const {
        return this->topX_;
    }

    void SetTopX(int x) {
        if (!this->ValidateSize_(x, this->topY_, this->bottomX_, this->bottomY_)) {
            throw std::runtime_error("Error: setting top x value makes negative viewport size is invalid");
        }

        this->topX_ = x;
    }

    int GetTopY() const {
        return this->topY_;
    }

    void SetTopY(int y) {
        if (!this->ValidateSize_(this->topX_, y, this->bottomX_, this->bottomY_)) {
            throw std::runtime_error("Error: setting top y value makes negative viewport size is invalid");
        }

        this->topY_ = y;
    }

    int GetBottomX() const {
        return this->bottomX_;
    }

    void SetBottomX(int x) {
        if (!this->ValidateSize_(this->topX_, this->topY_, x, this->bottomY_)) {
            throw std::runtime_error("Error: setting bottom x value makes negative viewport size is invalid");
        }

        this->bottomX_ = x;
    }

    int GetBottomY() const {
        return this->bottomY_;
    }

    void SetBottomY(int y) {
        if (!this->ValidateSize_(this->topX_, this->topY_, this->bottomX_, y)) {
            throw std::runtime_error("Error: setting bottom y value makes negative viewport size is invalid");
        }

        this->bottomY_ = y;
    }

    float GetFieldOfView() const {
        return this->radiansFieldOfView_;
    }

    void SetFieldOfView(float fieldOfView) {
        this->radiansFieldOfView_ = fieldOfView;
    }

    float GetZNear() const {
        return this->zNear_;
    }

    void SetZNear(float zNear) {
        this->zNear_ = zNear;
    }

    float GetZFar() const {
        return this->zFar_;
    }

    void SetZFar(float zFar) {
        this->zFar_ = zFar;
    }

    int GetHeight() const {
        return this->bottomY_ - this->topY_;
    }

    int GetWidth() const {
        return this->bottomX_ - this->topX_;
    }

    void UpdateViewport() {
        glViewport(0, 0, this->GetWidth(), this->GetHeight());
    }

    glm::mat4 CalcPerspectiveMatrix() const {
        return glm::perspective(this->radiansFieldOfView_,
            static_cast<float>(this->GetWidth()) / static_cast<float>(this->GetHeight()),
            this->zNear_,
            this->zFar_
        );
    }

private:
    int topX_{};
    int topY_{};
    int bottomX_{};
    int bottomY_{};
    float radiansFieldOfView_{};
    float zNear_{};
    float zFar_{};

    void ConstructorHelper_(int topX, int topY, int bottomX, int bottomY) {
        if (!this->ValidateSize_(topX, topY, bottomX, bottomY)) {
            throw std::runtime_error("Error: negative viewport size is invalid");
        }

        this->topX_    = topX;
        this->topY_    = topY;
        this->bottomX_ = bottomX;
        this->bottomY_ = bottomY;
    }

    bool ValidateSize_(int topX, int topY, int bottomX, int bottomY) {
        return bottomX - topX > 0 && bottomY - topY > 0;
    }
};
