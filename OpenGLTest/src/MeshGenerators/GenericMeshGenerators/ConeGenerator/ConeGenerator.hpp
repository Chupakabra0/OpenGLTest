#pragma once
#include "MeshGenerators/MeshGenerator.hpp"

class ConeGenerator : public MeshGenerator {
public:
    explicit ConeGenerator(float height, float radius, int segments, int slices, const glm::vec3& circleOrigin, const glm::vec3& color);

    ConeGenerator(const ConeGenerator&) = default;

    ConeGenerator(ConeGenerator&&) noexcept = default;

    ConeGenerator& operator=(const ConeGenerator&) = default;

    ConeGenerator& operator=(ConeGenerator&&) noexcept = default;

    ~ConeGenerator() noexcept override = default;

    std::shared_ptr<IMeshInstance> GenerateMesh() override;

private:
    float height_{};
    float radius_{};
    int segments_{};
    int slices_{};

    void ConstructHelper_(int slices);
};
