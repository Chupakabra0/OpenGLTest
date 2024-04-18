#pragma once
#include "CameraInstance/CameraInstance.hpp"

class ViewportInstance {
public:
    ViewportInstance() = delete;

    explicit ViewportInstance(int topX, int topY, int bottomX, int bottomY,
        float radiansFieldOfView, float zNear, float zFar);

    ViewportInstance(const ViewportInstance&) = default;

    ViewportInstance(ViewportInstance&&) noexcept = default;

    ViewportInstance& operator=(const ViewportInstance&) = default;

    ViewportInstance& operator=(ViewportInstance&&) noexcept = default;

    ~ViewportInstance() = default;

    int GetTopX() const;

    void SetTopX(int x);

    int GetTopY() const;

    void SetTopY(int y);

    int GetBottomX() const;

    void SetBottomX(int x);

    int GetBottomY() const;

    void SetBottomY(int y);

    float GetFieldOfView() const;

    void SetFieldOfView(float fieldOfView);

    float GetZNear() const;

    void SetZNear(float zNear);

    float GetZFar() const;

    void SetZFar(float zFar);

    int GetHeight() const;

    int GetWidth() const;

    void UpdateViewport();

    glm::mat4 CalcPerspectiveMatrix() const;

private:
    int topX_{};
    int topY_{};
    int bottomX_{};
    int bottomY_{};
    float radiansFieldOfView_{};
    float zNear_{};
    float zFar_{};

    void ConstructorHelper_(int topX, int topY, int bottomX, int bottomY);

    bool ValidateSize_(int topX, int topY, int bottomX, int bottomY);
};
