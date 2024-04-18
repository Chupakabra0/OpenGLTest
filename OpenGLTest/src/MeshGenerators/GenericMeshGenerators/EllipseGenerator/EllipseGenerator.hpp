#pragma once
#include "MeshGenerators/MeshGenerator.hpp"

class EllipseGenerator : public MeshGenerator {
public:
    EllipseGenerator() = delete;

    explicit EllipseGenerator(float a, float b, int segments, const glm::vec3& origin, const glm::vec3& color);

    EllipseGenerator(const EllipseGenerator&) = default;

    EllipseGenerator(EllipseGenerator&&) noexcept = default;

    EllipseGenerator& operator=(const EllipseGenerator&) = default;

    EllipseGenerator& operator=(EllipseGenerator&&) noexcept = default;

    ~EllipseGenerator() override = default;

    std::shared_ptr<IMeshInstance> GenerateMesh() override;

    float GetA() const;

    void SetA(float a);

    float GetB() const;

    void SetB(float b);

    int GetSegments() const;

    void SetSegments(int segments);

private:
    float a_;
    float b_;
    int segments_;
};
