#include "MeshGenerators/MaterialMeshGenerator.hpp"
#include "MeshInstance/MaterialMeshInstance.hpp"

MaterialMeshGenerator::MaterialMeshGenerator(const std::shared_ptr<IMeshGenerator>& meshGenerator, const MaterialInstance& material)
    : meshGenerator_(meshGenerator), material_(material) {
    if (this->meshGenerator_ == nullptr) {
        throw std::runtime_error("Mesh generator is nullptr");
    }
}

std::shared_ptr<IMeshInstance> MaterialMeshGenerator::GenerateMesh() {
    auto mesh = this->meshGenerator_->GenerateMesh();

    return std::make_shared<MaterialMeshInstance>(mesh, this->material_);
}

MaterialInstance MaterialMeshGenerator::GetMaterial() const {
    return this->material_;
}

void MaterialMeshGenerator::SetMaterial(const MaterialInstance& material) {
    this->material_ = material;
}
