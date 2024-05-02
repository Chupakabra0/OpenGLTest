#pragma once
#include "MaterialInstance/MaterialInstance.h"
#include "MeshGenerators/IMeshGenerator.hpp"

class MaterialMeshGenerator : public IMeshGenerator {
public:
    MaterialMeshGenerator() = delete;

    explicit MaterialMeshGenerator(const std::shared_ptr<IMeshGenerator>& meshGenerator, const MaterialInstance& material);

    MaterialMeshGenerator(const MaterialMeshGenerator&) = default;

    MaterialMeshGenerator(MaterialMeshGenerator&&) noexcept = default;

    MaterialMeshGenerator& operator=(const MaterialMeshGenerator&) = default;

    MaterialMeshGenerator& operator=(MaterialMeshGenerator&&) noexcept = default;

    ~MaterialMeshGenerator() override = default;

    std::shared_ptr<IMeshInstance> GenerateMesh() override;

    MaterialInstance GetMaterial() const;

    void SetMaterial(const MaterialInstance& material);

private:
    std::shared_ptr<IMeshGenerator> meshGenerator_{};
    MaterialInstance material_{};
};
