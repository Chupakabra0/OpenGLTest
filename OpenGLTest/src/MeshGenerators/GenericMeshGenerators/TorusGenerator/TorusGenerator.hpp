#pragma once

#include "MeshGenerators/MeshGenerator.hpp"

class TorusGenerator : public MeshGenerator {
public:
    explicit TorusGenerator(float innerRadius, float outerRadius, int divSlices, int divLoops,
        const glm::vec3& origin, const glm::vec3& color);

    TorusGenerator(const TorusGenerator&) = default;

    TorusGenerator(TorusGenerator&&) noexcept = default;

    TorusGenerator& operator=(const TorusGenerator&) = default;

    TorusGenerator& operator=(TorusGenerator&&) noexcept = default;

    ~TorusGenerator() noexcept override = default;

    std::shared_ptr<IMeshInstance> GenerateMesh() override;

private:
    float innerRadius_{};
    float outerRadius_{};
    int divSlices_{};
    int divLoops_{};

    void ConstructorHelper_(int divSlices, int divLoops);
};
