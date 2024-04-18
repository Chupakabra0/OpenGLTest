#include "MeshGenerators/GenericMeshGenerators/ParallelepipedGenerator/ParallelepipedGenerator.hpp"
#include "MeshInstance/MeshInstance.hpp"

ParallelepipedGenerator::ParallelepipedGenerator(float height, float width, float depth, const glm::vec3& origin, const glm::vec3& color)
    : MeshGenerator(origin, color), height_(height), width_(width), depth_(depth) {

}

std::shared_ptr<IMeshInstance> ParallelepipedGenerator::GenerateMesh() {
    const float halfHeight = this->height_ / 2.0f;
    const float halfWidth = this->width_ / 2.0f;
    const float halfDepth = this->depth_ / 2.0f;

    std::vector<glm::vec3> positions{};

    positions.push_back(this->origin_ + glm::vec3(-halfWidth, -halfHeight, halfDepth));
    positions.push_back(this->origin_ + glm::vec3(-halfWidth, halfHeight, halfDepth));
    positions.push_back(this->origin_ + glm::vec3(halfWidth, halfHeight, halfDepth));
    positions.push_back(this->origin_ + glm::vec3(halfWidth, -halfHeight, halfDepth));
    positions.push_back(this->origin_ + glm::vec3(-halfWidth, -halfHeight, -halfDepth));
    positions.push_back(this->origin_ + glm::vec3(-halfWidth, halfHeight, -halfDepth));
    positions.push_back(this->origin_ + glm::vec3(halfWidth, halfHeight, -halfDepth));
    positions.push_back(this->origin_ + glm::vec3(halfWidth, -halfHeight, -halfDepth));

    std::vector<glm::vec3> faceNormals{};

    faceNormals.emplace_back(0.0f, 0.0f, 1.0f);
    faceNormals.emplace_back(0.0f, 1.0f, 0.0f);
    faceNormals.emplace_back(0.0f, 0.0f, 0.0f);
    faceNormals.emplace_back(1.0f, 0.0f, 0.0f);
    faceNormals.emplace_back(0.0f, -1.0f, 0.0f);
    faceNormals.emplace_back(-1.0f, 0.0f, 0.0f);
    faceNormals.emplace_back(0.0f, 0.0f, 0.0f);
    faceNormals.emplace_back(0.0f, 0.0f, -1.0f);

    std::vector<glm::vec3> vertexNormals{};

    vertexNormals.emplace_back(-1.0f, -1.0f, 1.0f);
    vertexNormals.emplace_back(-1.0f, 1.0f, 1.0f);
    vertexNormals.emplace_back(1.0f, 1.0f, 1.0f);
    vertexNormals.emplace_back(1.0f, -1.0f, 1.0f);
    vertexNormals.emplace_back(-1.0f, -1.0f, -1.0f);
    vertexNormals.emplace_back(-1.0f, 1.0f, -1.0f);
    vertexNormals.emplace_back(1.0f, 1.0f, -1.0f);
    vertexNormals.emplace_back(1.0f, -1.0f, -1.0f);

    for (auto& vn : vertexNormals) {
        vn = glm::normalize(vn);
    }

    std::vector<unsigned> indecies{};

    indecies.insert(indecies.end(), { 0u, 3u, 2u });
    indecies.insert(indecies.end(), { 0u, 2u, 1u });

    indecies.insert(indecies.end(), { 3u, 7u, 6u });
    indecies.insert(indecies.end(), { 3u, 6u, 2u });

    indecies.insert(indecies.end(), { 7u, 4u, 5u });
    indecies.insert(indecies.end(), { 7u, 5u, 6u });

    indecies.insert(indecies.end(), { 5u, 4u, 0u });
    indecies.insert(indecies.end(), { 5u, 0u, 1u });

    indecies.insert(indecies.end(), { 1u, 2u, 6u });
    indecies.insert(indecies.end(), { 1u, 6u, 5u });

    indecies.insert(indecies.end(), { 4u, 7u, 3u });
    indecies.insert(indecies.end(), { 4u, 3u, 0u });

    return std::make_shared<MeshInstance>(
        positions,
        std::vector(positions.size(), this->color_),
        vertexNormals,
        //faceNormals,
        std::vector(positions.size(), glm::zero<glm::vec3>()),  // TODO: texture coords
        indecies
    );
}

float ParallelepipedGenerator::GetHeight() const {
    return this->height_;
}

void ParallelepipedGenerator::SetHeight(float height) {
    this->height_ = height;
}

float ParallelepipedGenerator::GetWidth() const {
    return this->width_;
}

void ParallelepipedGenerator::SetWidth(float width) {
    this->width_ = width;
}

float ParallelepipedGenerator::GetDepth() const {
    return this->depth_;
}

void ParallelepipedGenerator::SetDepth(float depth) {
    this->depth_ = depth;
}
