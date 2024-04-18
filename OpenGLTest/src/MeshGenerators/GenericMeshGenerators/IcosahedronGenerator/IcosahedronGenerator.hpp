#pragma once
#include "MeshGenerators/MeshGenerator.hpp"

#include <glm/gtx/hash.hpp>

class IcosahedronGenerator : public MeshGenerator {
public:
    IcosahedronGenerator() = delete;

    explicit IcosahedronGenerator(float radius, const glm::vec3& origin, const glm::vec3& color);

    IcosahedronGenerator(const IcosahedronGenerator&) = default;

    IcosahedronGenerator(IcosahedronGenerator&&) noexcept = default;

    IcosahedronGenerator& operator=(const IcosahedronGenerator&) = default;

    IcosahedronGenerator& operator=(IcosahedronGenerator&&) noexcept = default;

    ~IcosahedronGenerator() override = default;

    std::shared_ptr<IMeshInstance> GenerateMesh() override;

private:
    float radius_{};
};
