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

    virtual std::unique_ptr<IMeshGenerator> GenerateUniqueCircleGenerator(
        float radius, int segments, const glm::vec3& origin, const glm::vec3& color) = 0;

    virtual std::unique_ptr<IMeshGenerator> GenerateUniqueCylinderGenerator(
        float height, float radius, int segments, int slices, const glm::vec3& circleOrigin, const glm::vec3& color) = 0;

    virtual std::unique_ptr<IMeshGenerator> GenerateUniqueEllipseGenerator(
        float a, float b, int segments, const glm::vec3& origin, const glm::vec3& color) = 0;

    virtual std::unique_ptr<IMeshGenerator> GenerateUniqueIcosahedronGenerator(
        float radius, const glm::vec3& origin, const glm::vec3& color) = 0;
    
    virtual std::unique_ptr<IMeshGenerator> GenerateUniqueIcosphereGenerator(
        float radius, int iterations, const glm::vec3& origin, const glm::vec3& colors) = 0;

    virtual std::unique_ptr<IMeshGenerator> GenerateUniqueParallelipedGenerator(
        float height, float width, float depth, const glm::vec3& origin, const glm::vec3& color) = 0;

    virtual std::unique_ptr<IMeshGenerator> GenerateUniqueRectangleGenerator(
        float height, float width, const glm::vec3& origin, const glm::vec3& color) = 0;

    virtual std::unique_ptr<IMeshGenerator> GenerateUniqueTorusGenerator(
        float innerRadius, float outerRadius, int divSlices, int divLoops, const glm::vec3& origin, const glm::vec3& color) = 0;

    virtual std::unique_ptr<IMeshGenerator> GenerateUniqueUvSphereGenerator(
        float radius, int slices, int stacks, const glm::vec3& origin, const glm::vec3& color) = 0;
};
