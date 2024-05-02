#pragma once
#include <vector>

#include <glm/gtc/constants.hpp>

#include "MeshInstance/IMeshInstance.hpp"

class MeshInstance : public IMeshInstance {
public:
    explicit MeshInstance() = default;

    explicit MeshInstance(
        const std::vector<glm::vec3>& positions, const std::vector<glm::vec3>& colors, const std::vector<glm::vec3>& vertexNormals,
        const std::vector<glm::vec3>& textures, const std::vector<unsigned>& indecies
    );

    MeshInstance(const MeshInstance&) = default;

    MeshInstance(MeshInstance&&) noexcept = default;

    MeshInstance& operator=(const MeshInstance&) = default;

    MeshInstance& operator=(MeshInstance&&) noexcept = default;

    ~MeshInstance() override = default;

    void AddVertex(
        const glm::vec3& position, const glm::vec3& color,
        const glm::vec3& vertexNormal = glm::zero<glm::vec3>(),
        const glm::vec3& texture = glm::zero<glm::vec3>()) override;

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

    //void SetTexture(const std::shared_ptr<TextureInstance>&) {

    //}

protected:
    //std::shared_ptr<TextureInstance> texture_{};
    std::vector<unsigned> indecies_{};
    std::vector<glm::vec3> positions_{};
    std::vector<glm::vec3> colors_{};
    std::vector<glm::vec3> vertexNormals_{};
    std::vector<glm::vec3> textCoords_{};
};
