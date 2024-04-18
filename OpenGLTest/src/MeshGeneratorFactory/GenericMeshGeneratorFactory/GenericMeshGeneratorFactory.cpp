#include "MeshGeneratorFactory/GenericMeshGeneratorFactory/GenericMeshGeneratorFactory.hpp"

#include "MeshGenerators/GenericMeshGenerators/CircleGenerator/CircleGenerator.hpp"
#include "MeshGenerators/GenericMeshGenerators/CylinderGenerator/CylinderGenerator.hpp"
#include "MeshGenerators/GenericMeshGenerators/EllipseGenerator/EllipseGenerator.hpp"
#include "MeshGenerators/GenericMeshGenerators/IcosahedronGenerator/IcosahedronGenerator.hpp"
#include "MeshGenerators/GenericMeshGenerators/IcosphereGenerator/IcosphereGenerator.hpp"
#include "MeshGenerators/GenericMeshGenerators/ParallelepipedGenerator/ParallelepipedGenerator.hpp"
#include "MeshGenerators/GenericMeshGenerators/RectangleGenerator/RectangleGenerator.hpp"
#include "MeshGenerators/GenericMeshGenerators/TorusGenerator/TorusGenerator.hpp"
#include "MeshGenerators/GenericMeshGenerators/UvSphereGenerator/UvSphereGenerator.hpp"

std::unique_ptr<IMeshGenerator> GenericMeshGeneratorFactory::GenerateUniqueCircleGenerator(
    float radius, int segments, const glm::vec3& origin, const glm::vec3& color) {
    return std::make_unique<CircleGenerator>(radius, segments, origin, color);
}

std::unique_ptr<IMeshGenerator> GenericMeshGeneratorFactory::GenerateUniqueCylinderGenerator(
    float height, float radius, int segments, int slices, const glm::vec3& circleOrigin, const glm::vec3& color) {
    return std::make_unique<CylinderGenerator>(height, radius, segments, slices, circleOrigin, color);
}

std::unique_ptr<IMeshGenerator> GenericMeshGeneratorFactory::GenerateUniqueEllipseGenerator(
    float a, float b, int segments, const glm::vec3& origin, const glm::vec3& color) {
    return std::make_unique<EllipseGenerator>(a, b, segments, origin, color);
}

std::unique_ptr<IMeshGenerator> GenericMeshGeneratorFactory::GenerateUniqueIcosahedronGenerator(
    float radius, const glm::vec3& origin, const glm::vec3& color) {
    return std::make_unique<IcosahedronGenerator>(radius, origin, color);
}

std::unique_ptr<IMeshGenerator> GenericMeshGeneratorFactory::GenerateUniqueIcosphereGenerator(
    float radius, int iterations, const glm::vec3& origin, const glm::vec3& colors) {
    return std::make_unique<IcosphereGenerator>(radius, iterations, origin, colors);
}

std::unique_ptr<IMeshGenerator> GenericMeshGeneratorFactory::GenerateUniqueParallelipedGenerator(
    float height, float width, float depth, const glm::vec3& origin, const glm::vec3& color) {
    return std::make_unique<ParallelepipedGenerator>(height, width, depth, origin, color);
}

std::unique_ptr<IMeshGenerator> GenericMeshGeneratorFactory::GenerateUniqueRectangleGenerator(
    float height, float width, const glm::vec3& origin, const glm::vec3& color) {
    return std::make_unique<RectangleGenerator>(height, width, origin, color);
}

std::unique_ptr<IMeshGenerator> GenericMeshGeneratorFactory::GenerateUniqueTorusGenerator(
    float innerRadius, float outerRadius, int divSlices, int divLoops, const glm::vec3& origin, const glm::vec3& color) {
    return std::make_unique<TorusGenerator>(innerRadius, outerRadius, divSlices, divLoops, origin, color);
}

std::unique_ptr<IMeshGenerator> GenericMeshGeneratorFactory::GenerateUniqueUvSphereGenerator(
    float radius, int slices, int stacks, const glm::vec3& origin, const glm::vec3& color) {
    return std::make_unique<UVSphereGenerator>(radius, slices, stacks, origin, color);
}
