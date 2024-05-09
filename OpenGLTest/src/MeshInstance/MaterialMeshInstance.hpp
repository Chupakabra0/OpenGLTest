#pragma once
#include "MeshInstance/IMeshInstance.hpp"
#include "..\MaterialInstance\MaterialInstance.hpp"

#include <memory>

class MaterialMeshInstance : public IMeshInstance {
public:
    explicit MaterialMeshInstance() = default;

    explicit MaterialMeshInstance(const std::shared_ptr<IMeshInstance>& mesh, const MaterialInstance& material);

    MaterialMeshInstance(const MaterialMeshInstance&) = default;

    MaterialMeshInstance(MaterialMeshInstance&&) noexcept = default;

    MaterialMeshInstance& operator=(const MaterialMeshInstance&) = default;

    MaterialMeshInstance& operator=(MaterialMeshInstance&&) noexcept = default;

    ~MaterialMeshInstance() override = default;

    void AddVertex(
        const glm::vec3& position, const glm::vec3& color,
        const glm::vec3& vertexNormal, const glm::vec3& texture) override;

    void SetTexture(unsigned index, const glm::vec3& texture) override;

    void SetVertexNormal(unsigned index, const glm::vec3& normal) override;

    void SetColor(unsigned index, const glm::vec3& color) override;

    void SetPosition(unsigned index, const glm::vec3& position) override;

    void AddFace(unsigned a, unsigned b, unsigned c) override;

    IndexBufferObject GenerateIBO() const override;

    VertexArrayObject GenerateVAO(IndexBufferObject* ibo = nullptr) const override;

    const std::vector<unsigned>& GetIndecies() const override;

    const std::vector<glm::vec3>& GetPositions() const override;

    const std::vector<glm::vec3>& GetColors() const override;

    const std::vector<glm::vec3>& GetVertexNormals() const override;

    const std::vector<glm::vec3>& GetTextCoords() const override;

    const std::vector<float>& GetShininess() const {
        return this->shininessMaterial_;
    }

    void SetShininess(float shininess) {
        this->shininessMaterial_ = std::vector(this->shininessMaterial_.size(), shininess);
    }

private:
    std::vector<glm::vec3> ambientMaterial_{};
    std::vector<glm::vec3> diffuseMaterial_{};
    std::vector<glm::vec3> specularMaterial_{};
    std::vector<float> shininessMaterial_{};
    std::shared_ptr<IMeshInstance> meshInstance_{};

    void InitMaterials_(const MaterialInstance& material);
};
