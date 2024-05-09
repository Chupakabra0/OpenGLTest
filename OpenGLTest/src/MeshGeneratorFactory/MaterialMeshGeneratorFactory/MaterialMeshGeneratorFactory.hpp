#pragma once
#include "MeshGeneratorFactory/GenericMeshGeneratorFactory/GenericMeshGeneratorFactory.hpp"
#include "..\..\MaterialInstance\MaterialInstance.hpp"

class MaterialMeshGeneratorFactory : public IMeshGeneratorFactory {
public:
    MaterialMeshGeneratorFactory() = delete;

    explicit MaterialMeshGeneratorFactory(const MaterialInstance& material);

    MaterialMeshGeneratorFactory(const MaterialMeshGeneratorFactory&) = default;

    MaterialMeshGeneratorFactory(MaterialMeshGeneratorFactory&&) noexcept = default;

    MaterialMeshGeneratorFactory& operator=(const MaterialMeshGeneratorFactory&) = default;

    MaterialMeshGeneratorFactory& operator=(MaterialMeshGeneratorFactory&&) noexcept = default;

    ~MaterialMeshGeneratorFactory() override = default;

    std::unique_ptr<IMeshGenerator> GenerateUniqueCircleGenerator(
        float radius, int segments, const glm::vec3& origin,
        const glm::vec3& color) override;

    std::unique_ptr<IMeshGenerator> GenerateUniqueCylinderGenerator(
        float height, float radius, int segments, int slices,
        const glm::vec3& circleOrigin, const glm::vec3& color) override;

    std::unique_ptr<IMeshGenerator> GenerateUniqueEllipseGenerator(
        float a, float b, int segments,
        const glm::vec3& origin, const glm::vec3& color) override;

    std::unique_ptr<IMeshGenerator> GenerateUniqueIcosahedronGenerator(
        float radius, const glm::vec3& origin,
        const glm::vec3& color) override;

    std::unique_ptr<IMeshGenerator> GenerateUniqueIcosphereGenerator(
        float radius, int iterations,
        const glm::vec3& origin, const glm::vec3& color) override;

    std::unique_ptr<IMeshGenerator> GenerateUniqueParallelipedGenerator(
        float height, float width, float depth,
        const glm::vec3& origin, const glm::vec3& color) override;

    std::unique_ptr<IMeshGenerator> GenerateUniqueRectangleGenerator(
        float height, float width, const glm::vec3& origin,
        const glm::vec3& color) override;

    std::unique_ptr<IMeshGenerator> GenerateUniqueTorusGenerator(
        float innerRadius, float outerRadius, int divSlices,
        int divLoops, const glm::vec3& origin, const glm::vec3& color) override;

    std::unique_ptr<IMeshGenerator> GenerateUniqueUvSphereGenerator(
        float radius, int slices, int stacks,
        const glm::vec3& origin, const glm::vec3& color) override;

private:
    std::shared_ptr<GenericMeshGeneratorFactory> meshGeneratorFactory_{};
    MaterialInstance material_{};
};
