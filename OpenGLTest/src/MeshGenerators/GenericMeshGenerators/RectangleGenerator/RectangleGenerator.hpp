#pragma once
#include "MeshGenerators/MeshGenerator.hpp"

class RectangleGenerator : public MeshGenerator {
public:
    RectangleGenerator() = delete;

    explicit RectangleGenerator(float height, float width, const glm::vec3& origin, const glm::vec3& color);

    RectangleGenerator(const RectangleGenerator&) = default;

    RectangleGenerator(RectangleGenerator&&) noexcept = default;

    RectangleGenerator& operator=(const RectangleGenerator&) = default;

    RectangleGenerator& operator=(RectangleGenerator&&) noexcept = default;

    ~RectangleGenerator() override = default;

    std::shared_ptr<IMeshInstance> GenerateMesh() override;

    float GetHeight() const;

    void SetHeight(float height);

    float GetWidth() const;

    void SetWidth(float width);

private:
    float height_;
    float width_;
};
