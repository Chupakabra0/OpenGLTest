#include "MeshGeneratorFactory/MaterialMeshGeneratorFactory/MaterialMeshGeneratorFactory.hpp"
#include "MeshGenerators/MaterialMeshGenerator.hpp"

MaterialMeshGeneratorFactory::MaterialMeshGeneratorFactory(const MaterialInstance& material)
    : material_(material) {
    this->meshGeneratorFactory_ = std::make_shared<GenericMeshGeneratorFactory>();
}

std::unique_ptr<IMeshGenerator> MaterialMeshGeneratorFactory::GenerateUniqueCircleGenerator(
    float radius, int segments, const glm::vec3& origin, const glm::vec3& color) {
    std::shared_ptr<IMeshGenerator> meshGenerator = this->meshGeneratorFactory_->GenerateUniqueCircleGenerator(radius, segments, origin, color);

    return std::make_unique<MaterialMeshGenerator>(meshGenerator, this->material_);
}

std::unique_ptr<IMeshGenerator> MaterialMeshGeneratorFactory::GenerateUniqueCylinderGenerator(
    float height, float radius, int segments, int slices, const glm::vec3& circleOrigin, const glm::vec3& color) {
    std::shared_ptr<IMeshGenerator> meshGenerator = this->meshGeneratorFactory_->GenerateUniqueCylinderGenerator(
        height, radius, segments, slices, circleOrigin, color
    );

    return std::make_unique<MaterialMeshGenerator>(meshGenerator, this->material_);
}

std::unique_ptr<IMeshGenerator> MaterialMeshGeneratorFactory::GenerateUniqueEllipseGenerator(
    float a, float b, int segments, const glm::vec3& origin, const glm::vec3& color) {
    std::shared_ptr<IMeshGenerator> meshGenerator = this->meshGeneratorFactory_->GenerateUniqueEllipseGenerator(
        a, b, segments, origin, color
    );

    return std::make_unique<MaterialMeshGenerator>(meshGenerator, this->material_);
}

std::unique_ptr<IMeshGenerator> MaterialMeshGeneratorFactory::GenerateUniqueIcosahedronGenerator(
    float radius, const glm::vec3& origin, const glm::vec3& color) {
    std::shared_ptr<IMeshGenerator> meshGenerator = this->meshGeneratorFactory_->GenerateUniqueIcosahedronGenerator(
        radius, origin, color
    );

    return std::make_unique<MaterialMeshGenerator>(meshGenerator, this->material_);
}

std::unique_ptr<IMeshGenerator> MaterialMeshGeneratorFactory::GenerateUniqueIcosphereGenerator(
    float radius, int iterations, const glm::vec3& origin, const glm::vec3& color) {
    std::shared_ptr<IMeshGenerator> meshGenerator = this->meshGeneratorFactory_->GenerateUniqueIcosphereGenerator(
        radius, iterations, origin, color
    );

    return std::make_unique<MaterialMeshGenerator>(meshGenerator, this->material_);
}

std::unique_ptr<IMeshGenerator> MaterialMeshGeneratorFactory::GenerateUniqueParallelipedGenerator(
    float height, float width, float depth, const glm::vec3& origin, const glm::vec3& color) {
    std::shared_ptr<IMeshGenerator> meshGenerator = this->meshGeneratorFactory_->GenerateUniqueParallelipedGenerator(
        height, width, depth, origin, color
    );

    return std::make_unique<MaterialMeshGenerator>(meshGenerator, this->material_);
}

std::unique_ptr<IMeshGenerator> MaterialMeshGeneratorFactory::GenerateUniqueRectangleGenerator(
    float height, float width, const glm::vec3& origin, const glm::vec3& color) {
    std::shared_ptr<IMeshGenerator> meshGenerator = this->meshGeneratorFactory_->GenerateUniqueRectangleGenerator(
        height, width, origin, color
    );

    return std::make_unique<MaterialMeshGenerator>(meshGenerator, this->material_);
}

std::unique_ptr<IMeshGenerator> MaterialMeshGeneratorFactory::GenerateUniqueTorusGenerator(
    float innerRadius, float outerRadius, int divSlices, int divLoops, const glm::vec3& origin, const glm::vec3& color) {
    std::shared_ptr<IMeshGenerator> meshGenerator = this->meshGeneratorFactory_->GenerateUniqueTorusGenerator(
        innerRadius, outerRadius, divSlices, divLoops, origin, color
    );

    return std::make_unique<MaterialMeshGenerator>(meshGenerator, this->material_);
}

std::unique_ptr<IMeshGenerator> MaterialMeshGeneratorFactory::GenerateUniqueUvSphereGenerator(
    float radius, int slices, int stacks, const glm::vec3& origin, const glm::vec3& color) {
    std::shared_ptr<IMeshGenerator> meshGenerator = this->meshGeneratorFactory_->GenerateUniqueUvSphereGenerator(
        radius, slices, stacks, origin, color
    );

    return std::make_unique<MaterialMeshGenerator>(meshGenerator, this->material_);
}
