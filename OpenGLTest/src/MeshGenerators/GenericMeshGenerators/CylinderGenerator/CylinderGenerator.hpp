#pragma once
#include "MeshGenerators/MeshGenerator.hpp"
#include "MeshInstance/MeshInstance.hpp"

class CylinderGenerator : public MeshGenerator {
public:
    explicit CylinderGenerator(float height, float radius, int segments, int slices,
        const glm::vec3& circleOrigin, const glm::vec3& color);

    CylinderGenerator(const CylinderGenerator&) = default;

    CylinderGenerator(CylinderGenerator&&) noexcept = default;

    CylinderGenerator& operator=(const CylinderGenerator&) = default;

    CylinderGenerator& operator=(CylinderGenerator&&) noexcept = default;

    ~CylinderGenerator() noexcept override = default;

    std::shared_ptr<IMeshInstance> GenerateMesh() override;

private:
    float height_{};
    float radius_{};
    int segments_{};
    int slices_{};

    void ConstructorHelper_(int slices);
};
