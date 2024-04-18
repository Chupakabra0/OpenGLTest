#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "IndexBufferObject/IndexBufferObject.hpp"
#include "VertexArrayObject/VertexArrayObject.hpp"

struct IMeshInstance {
public:
    explicit IMeshInstance() = default;

    IMeshInstance(const IMeshInstance&) = default;

    IMeshInstance(IMeshInstance&&) noexcept = default;

    IMeshInstance& operator=(const IMeshInstance&) = default;

    IMeshInstance& operator=(IMeshInstance&&) noexcept = default;

    virtual ~IMeshInstance() = default;

    virtual void AddVertex(
        const glm::vec3& position, const glm::vec3& color,
        const glm::vec3& vertexNormal = glm::zero<glm::vec3>(),
        const glm::vec3& texture = glm::zero<glm::vec3>()) = 0;

    virtual void SetTexture(unsigned index, const glm::vec3& texture) = 0;

    virtual void SetVertexNormal(unsigned index, const glm::vec3& normal) = 0;

    virtual void SetColor(unsigned index, const glm::vec3& color) = 0;

    virtual void SetPosition(unsigned index, const glm::vec3& position) = 0;

    virtual void AddFace(unsigned a, unsigned b, unsigned c) = 0;

    virtual IndexBufferObject GenerateIBO() const = 0;

    virtual VertexArrayObject GenerateVAO(IndexBufferObject* ibo = nullptr) const = 0;

    virtual const std::vector<unsigned>& GetIndecies() const = 0;

    virtual const std::vector<glm::vec3>& GetPositions() const = 0;

    virtual const std::vector<glm::vec3>& GetColors() const = 0;

    virtual const std::vector<glm::vec3>& GetVertexNormals() const = 0;

    virtual const std::vector<glm::vec3>& GetTextCoords() const = 0;
};
