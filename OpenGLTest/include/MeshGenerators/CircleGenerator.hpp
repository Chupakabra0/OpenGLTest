#pragma once
#include "MeshGenerator.hpp"

class CircleGenerator : public MeshGenerator {
public:
    CircleGenerator() = delete;

    explicit CircleGenerator(float radius, int segments, const glm::vec3& origin, const glm::vec3& color)
        : MeshGenerator(origin, color), radius_(radius), segments_(segments) {

    }

    CircleGenerator(const CircleGenerator&) = default;

    CircleGenerator(CircleGenerator&&) noexcept = default;

    CircleGenerator& operator=(const CircleGenerator&) = default;

    CircleGenerator& operator=(CircleGenerator&&) noexcept = default;

    ~CircleGenerator() override = default;

    MeshClass GenerateMesh() override {
        std::vector<glm::vec3> positions{};

        positions.push_back(this->origin_);

        for (int i = 0; i < this->segments_; ++i) {
            const float phi = static_cast<float>(i) * glm::two_pi<float>() / static_cast<float>(this->segments_);

            positions.push_back(
                this->origin_ + this->radius_ * glm::vec3(
                    glm::cos(phi),
                    glm::sin(phi),
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

    float GetRadius() const {
        return this->radius_;
    }

    void SetRadius(float radius) {
        this->radius_ = radius;
    }

    int GetSegments() const {
        return this->segments_;
    }

    void SetSegments(int segments) {
        this->segments_ = segments_;
    }

private:
    float radius_;
    int segments_;
};