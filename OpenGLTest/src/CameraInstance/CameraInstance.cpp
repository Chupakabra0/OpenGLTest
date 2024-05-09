#include "CameraInstance/CameraInstance.hpp"

#include "ApplicationConfig/ApplicationConfig.hpp"

CameraInstance::CameraInstance(
    const glm::vec3& origin, const glm::vec3& target,
    const glm::vec3& x, const glm::vec3& y, const glm::vec3& z
)
    : x_(x), y_(y), z_(z), origin_(origin), target_(target) {

}

const glm::vec3 CameraInstance::GetX() const {
    return this->x_;
}

void CameraInstance::SetX(const glm::vec3& x) {
    this->x_ = x;
}

const glm::vec3 CameraInstance::GetY() const {
    return this->y_;
}

void CameraInstance::SetY(const glm::vec3& y) {
    this->y_ = y;
}

const glm::vec3 CameraInstance::GetZ() const {
    return this->z_;
}

void CameraInstance::SetZ(const glm::vec3& z) {
    this->z_ = z;
}

glm::vec3 CameraInstance::GetOrigin() const {
    return this->t_ * (this->target_ - this->origin_) + this->origin_;
}

void CameraInstance::SetOrigin(const glm::vec3& origin) {
    this->origin_ = origin;
}

glm::vec3 CameraInstance::GetTarget() const {
    return this->target_;
}

void CameraInstance::SetTarget(const glm::vec3& target) {
    this->target_ = target;
}

float CameraInstance::GetDistanceToTarget() const {
    return glm::length(this->target_ - this->origin_);
}

float CameraInstance::GetDistanceMult() const {
    return this->t_;
}

void CameraInstance::SetDistanceMult(float t) {
    //this->origin_ = this->target_ - d * this->z_;
    this->t_ = t > 1.0f ? 1.0f : (t < -1.0f ? -1.0f : t);
}

void CameraInstance::IncreaseDistanceMult() {
    this->SetDistanceMult(this->t_ + 0.05f);
}

void CameraInstance::DecreaseDistanceMult() {
    this->SetDistanceMult(this->t_ - 0.05f);
}

void CameraInstance::Arcball(float u, float v, float viewportHeight, float viewportWidth) {
    const glm::vec4 position(this->origin_, 1);
    const glm::vec4 pivot(this->target_, 1);

    const float deltaAngleX = glm::two_pi<float>() / viewportHeight;
    float deltaAngleY = glm::pi<float>() / viewportWidth;

    float xAngle = -u * deltaAngleX;
    float yAngle = -v * deltaAngleY;

    float cosAngle = glm::dot(this->target_ - this->origin_, this->y_);
    if (cosAngle * glm::sign(deltaAngleY) > 0.99f) {
        deltaAngleY = 0.0f;
    }

    this->RotateCamera(this->target_, glm::vec3(yAngle, xAngle, 0.0f));
}

void CameraInstance::RotateCamera(const glm::vec3& point, const glm::vec3& rotate) {
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

void CameraInstance::MoveCamera(const glm::vec3& delta) {
    this->origin_ += glm::vec3(
        glm::mat4(
            glm::vec4(this->x_, 0.0f),
            glm::vec4(this->y_, 0.0f),
            glm::vec4(this->z_, 0.0f),
            glm::vec4(0.0, 0.0, 0.0, 1.0f)
        ) * glm::vec4(delta, 1.0f)
    );
}

void CameraInstance::MoveTarget(const glm::vec3& delta) {
    this->target_ += glm::vec3(
        glm::mat4(
            glm::vec4(this->x_, 0.0f),
            glm::vec4(this->y_, 0.0f),
            glm::vec4(this->z_, 0.0f),
            glm::vec4(0.0, 0.0, 0.0, 1.0f)
        ) * glm::vec4(delta, 1.0f)
    );
}

void CameraInstance::Pan(float u, float v, float sensivity) {
    this->pan_ *= glm::translate(sensivity * glm::vec3(u, -v, 0.0f));
}

glm::mat4 CameraInstance::CalcViewMatrix() const {
    return this->pan_ * glm::lookAt(
        glm::vec3(glm::vec4(this->GetOrigin(), 1.0f)),
        glm::vec3(glm::vec4(this->target_, 1.0f)),
        glm::vec3(glm::vec4(this->y_, 0.0f))
    );
}
