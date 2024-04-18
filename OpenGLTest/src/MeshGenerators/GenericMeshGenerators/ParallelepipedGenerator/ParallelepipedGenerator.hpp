#pragma once
#include "MeshGenerators/MeshGenerator.hpp"

class ParallelepipedGenerator : public MeshGenerator {
public:
    ParallelepipedGenerator() = delete;

    explicit ParallelepipedGenerator(float height, float width, float depth, const glm::vec3& origin, const glm::vec3& color);

    ParallelepipedGenerator(const ParallelepipedGenerator&) = default;

    ParallelepipedGenerator(ParallelepipedGenerator&&) noexcept = default;

    ParallelepipedGenerator& operator=(const ParallelepipedGenerator&) = default;

    ParallelepipedGenerator& operator=(ParallelepipedGenerator&&) noexcept = default;

    ~ParallelepipedGenerator() override = default;

    std::shared_ptr<IMeshInstance> GenerateMesh() override;

    float GetHeight() const;

    void SetHeight(float height);

    float GetWidth() const;

    void SetWidth(float width);

    float GetDepth() const;

    void SetDepth(float depth);

private:
    float height_;
    float width_;
    float depth_;
};
