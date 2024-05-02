#include "MeshGenerators/MeshGenerator.hpp"

MeshGenerator::MeshGenerator(const glm::vec3& origin, const glm::vec3& color)
    : origin_(origin), color_(color) {

}

const glm::vec3& MeshGenerator::GetOrigin() const {
    return this->origin_;
}

void MeshGenerator::SetOrigin(const glm::vec3& origin) {
    this->origin_ = origin;
}

const glm::vec3& MeshGenerator::GetColor() const {
    return this->color_;
}

void MeshGenerator::SetColor(const glm::vec3& color) {
    this->color_ = color;
}
