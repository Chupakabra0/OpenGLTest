#pragma once
#include "MeshGenerators/MeshGenerator.hpp"

class CircleGenerator : public MeshGenerator {
public:
    CircleGenerator() = delete;

    explicit CircleGenerator(float radius, int segments, const glm::vec3& origin, const glm::vec3& color);

    CircleGenerator(const CircleGenerator&) = default;

    CircleGenerator(CircleGenerator&&) noexcept = default;

    CircleGenerator& operator=(const CircleGenerator&) = default;

    CircleGenerator& operator=(CircleGenerator&&) noexcept = default;

    ~CircleGenerator() override = default;

    std::shared_ptr<IMeshInstance> GenerateMesh() override;

    float GetRadius() const;

    void SetRadius(float radius);

    int GetSegments() const;

    void SetSegments(int segments);

private:
    float radius_;
    int segments_;
};
