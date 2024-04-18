#pragma once
#include "MeshGenerators/MeshGenerator.hpp"

#include <memory>

struct IMeshGeneratorFactory {
public:
    explicit IMeshGeneratorFactory() = default;

    IMeshGeneratorFactory(const IMeshGeneratorFactory&) = default;

    IMeshGeneratorFactory(IMeshGeneratorFactory&&) noexcept = default;

    IMeshGeneratorFactory& operator=(const IMeshGeneratorFactory&) = default;

    IMeshGeneratorFactory& operator=(IMeshGeneratorFactory&&) noexcept = default;

    virtual ~IMeshGeneratorFactory() = default;

    virtual std::unique_ptr<MeshGenerator> GenerateUniqueCircleGenerator(
        float radius, int segments, const glm::vec3& origin, const glm::vec3& color) = 0;

    virtual std::unique_ptr<MeshGenerator> GenerateUniqueCylinderGenerator(
        float height, float radius, int segments, int slices, const glm::vec3& circleOrigin, const glm::vec3& color) = 0;

    virtual std::unique_ptr<MeshGenerator> GenerateUniqueEllipseGenerator(
        float a, float b, int segments, const glm::vec3& origin, const glm::vec3& color) = 0;

    virtual std::unique_ptr<MeshGenerator> GenerateUniqueIcosahedronGenerator(
        float radius, const glm::vec3& origin, const glm::vec3& color) = 0;
    
    virtual std::unique_ptr<MeshGenerator> GenerateUniqueIcosphereGenerator(
        float radius, int iterations, const glm::vec3& origin, const glm::vec3& colors) = 0;

    virtual std::unique_ptr<MeshGenerator> GenerateUniqueParallelipedGenerator(
        float height, float width, float depth, const glm::vec3& origin, const glm::vec3& color) = 0;

    virtual std::unique_ptr<MeshGenerator> GenerateUniqueRectangleGenerator(
        float height, float width, const glm::vec3& origin, const glm::vec3& color) = 0;

    virtual std::unique_ptr<MeshGenerator> GenerateUniqueTorusGenerator(
        float innerRadius, float outerRadius, int divSlices, int divLoops, const glm::vec3& origin, const glm::vec3& color) = 0;

    virtual std::unique_ptr<MeshGenerator> GenerateUniqueUvSphereGenerator(
        float radius, int slices, int stacks, const glm::vec3& origin, const glm::vec3& color) = 0;
};
