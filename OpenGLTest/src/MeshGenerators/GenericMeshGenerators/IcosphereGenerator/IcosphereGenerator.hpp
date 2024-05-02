#pragma once
#include "MeshGenerators/MeshGenerator.hpp"

class IcosphereGenerator : public MeshGenerator {
public:
    explicit IcosphereGenerator(float radius, int iterations, const glm::vec3& origin, const glm::vec3& colors);

    IcosphereGenerator(const IcosphereGenerator&) = default;

    IcosphereGenerator(IcosphereGenerator&&) noexcept = default;

    IcosphereGenerator& operator=(const IcosphereGenerator&) = default;

    IcosphereGenerator& operator=(IcosphereGenerator&&) noexcept = default;

    ~IcosphereGenerator() override = default;

    std::shared_ptr<IMeshInstance> GenerateMesh() override;

private:
    float radius_{};
    int iterations_{};
};
