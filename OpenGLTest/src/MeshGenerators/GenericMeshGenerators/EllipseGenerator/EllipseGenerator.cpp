#include "MeshGenerators/GenericMeshGenerators/EllipseGenerator/EllipseGenerator.hpp"
#include "MeshInstance/MeshInstance.hpp"

EllipseGenerator::EllipseGenerator(float a, float b, int segments, const glm::vec3& origin, const glm::vec3& color)
    : MeshGenerator(origin, color), a_(a), b_(b), segments_(segments) {

}

std::shared_ptr<IMeshInstance> EllipseGenerator::GenerateMesh() {
    std::vector<glm::vec3> positions{};

    positions.push_back(this->origin_);

    for (int i = 0; i < this->segments_; ++i) {
        const float phi = static_cast<float>(i) * glm::two_pi<float>() / static_cast<float>(this->segments_);

        positions.push_back(
            this->origin_ + glm::vec3(
                this->a_ * glm::cos(phi),
                this->b_ * glm::sin(phi),
                0.0f
            )
        );
    }

    std::vector<unsigned> indecies{};
    for (int i = 1; i <= this->segments_; ++i) {
        indecies.push_back(0u);
        indecies.push_back(static_cast<unsigned>(i));

        if (i < this->segments_) {
            indecies.push_back(static_cast<unsigned>(i) + 1u);
        }
        else {
            indecies.push_back(1u);
        }
    }

    return std::make_shared<MeshInstance>(
        positions,
        std::vector(positions.size(), this->color_),
        std::vector(positions.size(), glm::vec3(0.0f, 0.0f, 1.0f)),
        std::vector(positions.size(), glm::zero<glm::vec3>()),      // TODO: texture coords
        indecies
    );
}

float EllipseGenerator::GetA() const {
    return this->a_;
}

void EllipseGenerator::SetA(float a) {
    this->a_ = a;
}

float EllipseGenerator::GetB() const {
    return this->b_;
}

void EllipseGenerator::SetB(float b) {
    this->b_ = b;
}

int EllipseGenerator::GetSegments() const {
    return this->segments_;
}

void EllipseGenerator::SetSegments(int segments) {
    this->segments_ = segments_;
}
