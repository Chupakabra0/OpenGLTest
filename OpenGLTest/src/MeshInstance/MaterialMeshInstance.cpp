#include "MeshInstance/MaterialMeshInstance.hpp"

MaterialMeshInstance::MaterialMeshInstance(const std::shared_ptr<IMeshInstance>& mesh, const MaterialInstance& material)
    : meshInstance_(mesh) {
    if (this->meshInstance_ == nullptr) {
        throw std::runtime_error("Mesh instance is nullptr");
    }

    this->InitMaterials_(material);
}

void MaterialMeshInstance::AddVertex(
    const glm::vec3& position, const glm::vec3& color,
    const glm::vec3& vertexNormal, const glm::vec3& texture) {
    this->meshInstance_->AddVertex(position, color, vertexNormal, texture);
}

void MaterialMeshInstance::SetTexture(unsigned index, const glm::vec3& texture) {
    this->meshInstance_->SetTexture(index, texture);
}

void MaterialMeshInstance::SetVertexNormal(unsigned index, const glm::vec3& normal) {
    this->meshInstance_->SetVertexNormal(index, normal);
}

void MaterialMeshInstance::SetColor(unsigned index, const glm::vec3& color) {
    this->meshInstance_->SetColor(index, color);
}

void MaterialMeshInstance::SetPosition(unsigned index, const glm::vec3& position) {
    this->meshInstance_->SetPosition(index, position);
}

void MaterialMeshInstance::AddFace(unsigned a, unsigned b, unsigned c) {
    this->meshInstance_->AddFace(a, b, c);
}

IndexBufferObject MaterialMeshInstance::GenerateIBO() const {
    return this->meshInstance_->GenerateIBO();
}

const std::vector<unsigned>& MaterialMeshInstance::GetIndecies() const {
    return this->meshInstance_->GetIndecies();
}

const std::vector<glm::vec3>& MaterialMeshInstance::GetPositions() const {
    return this->meshInstance_->GetPositions();
}

const std::vector<glm::vec3>& MaterialMeshInstance::GetColors() const {
    return this->meshInstance_->GetColors();
}

const std::vector<glm::vec3>& MaterialMeshInstance::GetVertexNormals() const {
    return this->meshInstance_->GetVertexNormals();
}

const std::vector<glm::vec3>& MaterialMeshInstance::GetTextCoords() const {
    return this->meshInstance_->GetTextCoords();
}

VertexArrayObject MaterialMeshInstance::GenerateVAO(IndexBufferObject* ibo) const {
    constexpr unsigned vertexSize{3u};
    VertexArrayObject vao = this->meshInstance_->GenerateVAO(ibo);

    VertexBufferAttributes ambientAttribute {
        vertexSize, static_cast<unsigned>(this->ambientMaterial_.size()), ValueType::FLOAT, Normalize::NOT_NORMALIZE, VertexBufferAttributesType::AMBIENT
    };

    VertexBufferAttributes diffuseAttribute {
        vertexSize, static_cast<unsigned>(this->diffuseMaterial_.size()), ValueType::FLOAT, Normalize::NOT_NORMALIZE, VertexBufferAttributesType::AMBIENT
    };

    VertexBufferAttributes specularAttribute {
        vertexSize, static_cast<unsigned>(this->specularMaterial_.size()), ValueType::FLOAT, Normalize::NOT_NORMALIZE, VertexBufferAttributesType::AMBIENT
    };

    VertexBufferAttributes shininessAttribute {
        1, static_cast<unsigned>(this->specularMaterial_.size()), ValueType::FLOAT, Normalize::NOT_NORMALIZE, VertexBufferAttributesType::AMBIENT
    };

    vao.AddBuffer(this->ambientMaterial_, ambientAttribute);
    vao.AddBuffer(this->diffuseMaterial_, diffuseAttribute);
    vao.AddBuffer(this->specularMaterial_, specularAttribute);
    vao.AddBuffer(this->specularMaterial_, shininessAttribute);

    return vao;
}

void MaterialMeshInstance::InitMaterials_(const MaterialInstance& material) {
    this->ambientMaterial_   = std::vector(this->meshInstance_->GetPositions().size(), material.ambient);
    this->diffuseMaterial_   = std::vector(this->meshInstance_->GetPositions().size(), material.diffuse);
    this->specularMaterial_  = std::vector(this->meshInstance_->GetPositions().size(), material.specular);
    this->shininessMaterial_ = std::vector(this->meshInstance_->GetPositions().size(), material.shininess);
}
