#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

struct Quaternion {
public:
    float cosine{};
    glm::vec3 axis{0.0f, 0.0f, 1.0f};
};

class Camera {
public:
    Camera() = delete;

    explicit Camera(const glm::vec3& origin, const glm::vec3& target, const glm::vec3& x, const glm::vec3& y, const glm::vec3 z)
        : x_(x), y_(y), z_(z), origin_(origin), target_(target) {

    }

    Camera(const Camera&) = default;

    Camera(Camera&&) noexcept = default;

    Camera& operator=(const Camera&) = default;

    Camera& operator=(Camera&&) noexcept = default;

    ~Camera() = default;

    const glm::vec3 GetX() const {
        return this->x_;
    }

    void SetX(const glm::vec3& x) {
        this->x_ = x;
    }

    const glm::vec3 GetY() const {
        return this->y_;
    }

    void SetY(const glm::vec3& y) {
        this->y_ = y;
    }

    const glm::vec3 GetZ() const {
        return this->z_;
    }

    void SetZ(const glm::vec3& z) {
        this->z_ = z;
    }

    const glm::vec3 GetOrigin() const {
        return this->origin_;
    }

    void SetOrigin(const glm::vec3& origin) {
        this->origin_ = origin;
    }

    const glm::vec3 GetTarget() const {
        return this->target_;
    }

    void SetTarget(const glm::vec3& target) {
        this->target_ = target;
    }

    float GetDistanceToTarget() const {
        return glm::length(this->target_ - this->origin_);
    }

    void SetDistanceToTarget(float d) {
        this->origin_ = this->target_ - d * this->z_;
    }

    void Arcball(float x1, float y1, float x2, float y2) {
        const glm::vec4 position(this->origin_, 1);
        const glm::vec4 pivot(this->target_, 1);

        constexpr float deltaAngleX = glm::two_pi<float>() / 1280.0f;
        float deltaAngleY           = glm::pi<float>() / 720.0f;

        float xAngle = (x1 - x2) * deltaAngleX;
        float yAngle = (y1 - y2) * deltaAngleY;

        float cosAngle = glm::dot(this->target_ - this->origin_, this->y_);
        if (cosAngle * glm::sign(deltaAngleY) > 0.99f) {
            deltaAngleY = 0.0f;
        }

        this->RotateCamera(this->target_, glm::vec3(yAngle, xAngle, 0.0f));
    }

    void RotateCamera(const glm::vec3& point, const glm::vec3& rotate) {
        glm::vec4 cameraPosition = glm::translate(-point) * glm::vec4(this->origin_, 1.0f);
        glm::vec4 cameraTarget   = glm::translate(-point) * glm::vec4(this->target_, 1.0f);
        glm::vec4 cameraRight    = glm::vec4(this->x_, 0.0f);
        glm::vec4 cameraUp       = glm::vec4(this->y_, 0.0f);
        glm::vec4 cameraForward  = glm::vec4(this->z_, 0.0f);

        cameraPosition = glm::rotate(rotate.z, glm::vec3(this->z_)) * cameraPosition;
        cameraTarget   = glm::rotate(rotate.z, glm::vec3(this->z_)) * cameraTarget;
        cameraUp       = glm::rotate(rotate.z, glm::vec3(this->z_)) * cameraUp;
        cameraRight    = glm::rotate(rotate.z, glm::vec3(this->z_)) * cameraRight;

        cameraPosition = glm::rotate(rotate.y, glm::vec3(this->y_)) * cameraPosition;
        cameraTarget   = glm::rotate(rotate.y, glm::vec3(this->y_)) * cameraTarget;
        cameraRight    = glm::rotate(rotate.y, glm::vec3(this->y_)) * cameraRight;
        cameraForward  = glm::rotate(rotate.y, glm::vec3(this->y_)) * cameraForward;

        cameraPosition = glm::rotate(rotate.x, glm::vec3(this->x_)) * cameraPosition;
        cameraTarget   = glm::rotate(rotate.x, glm::vec3(this->x_)) * cameraTarget;
        cameraUp       = glm::rotate(rotate.x, glm::vec3(this->x_)) * cameraUp;
        cameraForward  = glm::rotate(rotate.x, glm::vec3(this->x_)) * cameraForward;

        this->x_      = cameraRight;
        this->y_      = cameraUp;
        this->z_      = cameraForward;
        this->origin_ = glm::translate(point) * cameraPosition;
        this->target_ = glm::translate(point) * cameraTarget;
    }

    void MoveCamera(const glm::vec3& delta) {
        this->origin_ += delta;
    }

    void Pan(float u, float v, float sensivity) {
        this->pan_ *= glm::translate(-sensivity * glm::vec3(-u, v, 0.0f));
    }

    glm::mat4 GetViewMatrix() const {
        return this->pan_ * glm::lookAt(
            glm::vec3(glm::vec4(this->origin_, 1.0f)),
            glm::vec3(glm::vec4(this->target_, 1.0f)),
            glm::vec3(glm::vec4(this->y_, 0.0f))
        );
    }

private:
    glm::vec3 x_{};
    glm::vec3 y_{};
    glm::vec3 z_{};
    glm::vec3 origin_{};
    glm::vec3 target_{};
    glm::mat4 pan_{glm::identity<glm::mat4>()};
    glm::mat4 view_{glm::identity<glm::mat4>()};
};
