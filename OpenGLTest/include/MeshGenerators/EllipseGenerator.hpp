#pragma once
#include "MeshGenerator.hpp"

class EllipseGenerator : public MeshGenerator {
public:
    EllipseGenerator() = delete;

    explicit EllipseGenerator(float a, float b, int segments, const glm::vec3& origin, const glm::vec3& color)
        : MeshGenerator(origin, color), a_(a), b_(b), segments_(segments) {

    }

    EllipseGenerator(const EllipseGenerator&) = default;

    EllipseGenerator(EllipseGenerator&&) noexcept = default;

    EllipseGenerator& operator=(const EllipseGenerator&) = default;

    EllipseGenerator& operator=(EllipseGenerator&&) noexcept = default;

    ~EllipseGenerator() override = default;

    MeshClass GenerateMesh() override {
        std::vector<glm::vec3> positions{};

        positions.push_back(this->origin_);

        for (int i = 0; i < this->segments_; ++i) {
            const float phi = static_cast<float>(i) * glm::two_pi<float>() / static_cast<float>(this->segments_);

            positions.push_back(
                this->origin_ + glm::vec3(
                    this->a_ * glm::cos(phi),
                    this->b_ * glm::sin(phi),
                    0.0f
                )
            );
        }

        std::vector<unsigned> indecies{};
        for (int i = 1; i <= this->segments_; ++i) {
            indecies.push_back(0u);
            indecies.push_back(static_cast<unsigned>(i));

            if (i < this->segments_) {
                indecies.push_back(static_cast<unsigned>(i) + 1u);
            }
            else {
                indecies.push_back(1u);
            }
        }

        return MeshClass(
            positions,
            std::vector(positions.size(), this->color_),
            std::vector(positions.size(), glm::vec3(0.0f, 0.0f, 1.0f)),
            std::vector(positions.size(), glm::zero<glm::vec3>()),      // TODO: texture coords
            indecies
        );
    }

    float GetA() const {
        return this->a_;
    }

    void SetA(float a) {
        this->a_ = a;
    }

    float GetB() const {
        return this->b_;
    }

    void SetB(float b) {
        this->b_ = b;
    }

    int GetSegments() const {
        return this->segments_;
    }

    void SetSegments(int segments) {
        this->segments_ = segments_;
    }

private:
    float a_;
    float b_;
    int segments_;
};
