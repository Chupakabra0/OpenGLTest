#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>

//struct Quaternion {
//public:
//    float cosine{};
//    glm::vec3 axis{0.0f, 0.0f, 1.0f};
//};

class CameraInstance {
public:
    CameraInstance() = delete;

    explicit CameraInstance(const glm::vec3& origin, const glm::vec3& target, const glm::vec3& x, const glm::vec3& y, const glm::vec3 z);

    CameraInstance(const CameraInstance&) = default;

    CameraInstance(CameraInstance&&) noexcept = default;

    CameraInstance& operator=(const CameraInstance&) = default;

    CameraInstance& operator=(CameraInstance&&) noexcept = default;

    ~CameraInstance() = default;

    const glm::vec3 GetX() const;

    void SetX(const glm::vec3& x);

    const glm::vec3 GetY() const;

    void SetY(const glm::vec3& y);

    const glm::vec3 GetZ() const;

    void SetZ(const glm::vec3& z);

    const glm::vec3 GetOrigin() const;

    void SetOrigin(const glm::vec3& origin);

    const glm::vec3 GetTarget() const;

    void SetTarget(const glm::vec3& target);

    float GetDistanceToTarget() const;

    void SetDistanceToTarget(float d);

    void Arcball(float u, float v, float viewportHeight, float viewportWidth);

    void RotateCamera(const glm::vec3& point, const glm::vec3& rotate);

    void MoveCamera(const glm::vec3& delta);

    void MoveTarget(const glm::vec3& delta);

    void Pan(float u, float v, float sensivity);

    glm::mat4 CalcViewMatrix() const;

private:
    glm::vec3 x_{};
    glm::vec3 y_{};
    glm::vec3 z_{};
    glm::vec3 origin_{};
    glm::vec3 target_{};
    glm::mat4 pan_{glm::identity<glm::mat4>()};
    glm::mat4 view_{glm::identity<glm::mat4>()};
};
