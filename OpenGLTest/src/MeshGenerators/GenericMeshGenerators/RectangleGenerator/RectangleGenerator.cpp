#include "MeshGenerators/GenericMeshGenerators/RectangleGenerator/RectangleGenerator.hpp"
#include "MeshInstance/MeshInstance.hpp"

RectangleGenerator::RectangleGenerator(float height, float width, const glm::vec3& origin, const glm::vec3& color)
    : MeshGenerator(origin, color), height_(height), width_(width) {

}

std::shared_ptr<IMeshInstance> RectangleGenerator::GenerateMesh() {
    std::vector<glm::vec3> positions{};
    std::vector<glm::vec3> colors{};
    std::vector<glm::vec3> normals{};
    std::vector<glm::vec3> textures{};

    const float halfHeight = this->height_ / 2.0f;
    const float halfWidth  = this->width_ / 2.0f;

    const glm::vec4 a = glm::vec4(this->origin_.x - halfWidth, this->origin_.y - halfHeight, this->origin_.z, 1.0f);
    const glm::vec4 b = glm::vec4(this->origin_.x - halfWidth, this->origin_.y + halfHeight, this->origin_.z, 1.0f);
    const glm::vec4 c = glm::vec4(this->origin_.x + halfWidth, this->origin_.y + halfHeight, this->origin_.z, 1.0f);
    const glm::vec4 d = glm::vec4(this->origin_.x + halfWidth, this->origin_.y - halfHeight, this->origin_.z, 1.0f);

    positions.emplace_back(a);
    positions.emplace_back(b);
    positions.emplace_back(c);
    positions.emplace_back(d);

    const std::vector<unsigned> indecies{
        0u, 3u, 1u, // first face
        1u, 3u, 2u, // second face
    };

    return std::make_shared<MeshInstance>(
        positions,
        std::vector(positions.size(), this->color_),
        std::vector(positions.size(), glm::vec3(0.0f, 0.0f, 1.0f)),
        std::vector(positions.size(), glm::zero<glm::vec3>()),      // TODO: texture coords
        indecies
    );
}

float RectangleGenerator::GetHeight() const {
    return this->height_;
}

void RectangleGenerator::SetHeight(float height) {
    this->height_ = height;
}

float RectangleGenerator::GetWidth() const {
    return this->width_;
}

void RectangleGenerator::SetWidth(float width) {
    this->width_ = width;
}
