#pragma once
#include <glm/glm.hpp>

#include "IMeshGenerator.hpp"

class MeshGenerator : public IMeshGenerator {
public:
    MeshGenerator() = delete;

    explicit MeshGenerator(const glm::vec3& origin, const glm::vec3& color);

    MeshGenerator(const MeshGenerator&) = default;

    MeshGenerator(MeshGenerator&&) noexcept = default;

    MeshGenerator& operator=(const MeshGenerator&) = default;

    MeshGenerator& operator=(MeshGenerator&&) noexcept = default;

    ~MeshGenerator() override = default;

    std::shared_ptr<IMeshInstance> GenerateMesh() override = 0;

    const glm::vec3& GetOrigin() const;

    void SetOrigin(const glm::vec3& origin);

    const glm::vec3& GetColor() const;

    void SetColor(const glm::vec3& color);

protected:
    glm::vec3 origin_{};
    glm::vec3 color_{};
};
