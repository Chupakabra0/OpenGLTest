#pragma once
#include "MeshGenerators/MeshGenerator.hpp"

class UVSphereGenerator : public MeshGenerator {
public:
    UVSphereGenerator() = delete;

    explicit UVSphereGenerator(float radius, int slices, int stacks, const glm::vec3& origin, const glm::vec3& color);

    UVSphereGenerator(const UVSphereGenerator&) = default;

    UVSphereGenerator(UVSphereGenerator&&) noexcept = default;

    UVSphereGenerator& operator=(const UVSphereGenerator&) = default;

    UVSphereGenerator& operator=(UVSphereGenerator&&) noexcept = default;

    ~UVSphereGenerator() override = default;

    std::shared_ptr<IMeshInstance> GenerateMesh() override;

private:
    float radius_{};
    int slices_{};
    int stacks_{};

    void ConstructorHelper_(int slices, int stacks);
};
