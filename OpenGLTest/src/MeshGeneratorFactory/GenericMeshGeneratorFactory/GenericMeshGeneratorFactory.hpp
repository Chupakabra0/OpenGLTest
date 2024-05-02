#pragma once
#include "MeshGeneratorFactory/IMeshGeneratorFactory.hpp"

class GenericMeshGeneratorFactory : public IMeshGeneratorFactory {
public:
    explicit GenericMeshGeneratorFactory() = default;

    GenericMeshGeneratorFactory(const GenericMeshGeneratorFactory&) = default;

    GenericMeshGeneratorFactory(GenericMeshGeneratorFactory&&) noexcept = default;

    GenericMeshGeneratorFactory& operator=(const GenericMeshGeneratorFactory&) = default;

    GenericMeshGeneratorFactory& operator=(GenericMeshGeneratorFactory&&) noexcept = default;

    ~GenericMeshGeneratorFactory() override = default;

    std::unique_ptr<IMeshGenerator> GenerateUniqueCircleGenerator(
        float radius, int segments, const glm::vec3& origin, const glm::vec3& color) override;

    std::unique_ptr<IMeshGenerator> GenerateUniqueCylinderGenerator(
        float height, float radius, int segments, int slices,
        const glm::vec3& circleOrigin, const glm::vec3& color) override;

    std::unique_ptr<IMeshGenerator> GenerateUniqueEllipseGenerator(
        float a, float b, int segments, const glm::vec3& origin, const glm::vec3& color) override;

    std::unique_ptr<IMeshGenerator> GenerateUniqueIcosahedronGenerator(
        float radius, const glm::vec3& origin, const glm::vec3& color) override;

    std::unique_ptr<IMeshGenerator> GenerateUniqueIcosphereGenerator(
        float radius, int iterations, const glm::vec3& origin, const glm::vec3& colors) override;

    std::unique_ptr<IMeshGenerator> GenerateUniqueParallelipedGenerator(
        float height, float width, float depth, const glm::vec3& origin, const glm::vec3& color) override;

    std::unique_ptr<IMeshGenerator> GenerateUniqueRectangleGenerator(
        float height, float width, const glm::vec3& origin, const glm::vec3& color) override;

    std::unique_ptr<IMeshGenerator> GenerateUniqueTorusGenerator(
        float innerRadius, float outerRadius, int divSlices, int divLoops,
        const glm::vec3& origin, const glm::vec3& color) override;

    std::unique_ptr<IMeshGenerator> GenerateUniqueUvSphereGenerator(
        float radius, int slices, int stacks, const glm::vec3& origin, const glm::vec3& color) override;
};
