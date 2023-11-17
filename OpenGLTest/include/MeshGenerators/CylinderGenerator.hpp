#pragma once
#include "MeshGenerator.hpp"

class CylinderGenerator : public MeshGenerator {
public:
    explicit CylinderGenerator(float height, float radius, int segments, int slices,
        const glm::vec3& circleOrigin, const glm::vec3& color)
        : MeshGenerator(circleOrigin, color), height_(height), radius_(radius), segments_(segments) {
        this->ConstructorHelper_(slices);
    }

    CylinderGenerator(const CylinderGenerator&) = default;

    CylinderGenerator(CylinderGenerator&&) noexcept = default;

    CylinderGenerator& operator=(const CylinderGenerator&) = default;

    CylinderGenerator& operator=(CylinderGenerator&&) noexcept = default;

    ~CylinderGenerator() noexcept = default;

    MeshClass GenerateMesh() override {
        std::vector<glm::vec3> positions{};
        std::vector<unsigned> indecies{};

        positions.push_back(this->origin_);

        for (int i = 0; i < this->segments_; ++i) {
            const float phi = static_cast<float>(i) * glm::two_pi<float>() / this->segments_;

            const glm::vec3 circlePointBottom = this->origin_ + this->radius_ * glm::vec3(glm::cos(phi), 0.0f, glm::sin(phi));
            const glm::vec3 circlePointTop    = circlePointBottom + glm::vec3(0.0f, this->height_, 0.0f);

            const float step          = 1.0f / this->slices_;
            const glm::vec3 direction = circlePointTop - circlePointBottom;

            const auto calc = [&direction, &circlePointBottom](float t) {
                return circlePointBottom + t * direction;
            };

            for (int j = 0; j < this->slices_; ++j) {
                positions.push_back(calc(j * step));
            }

            positions.push_back(circlePointTop);
        }

        positions.push_back(this->origin_ + glm::vec3(0.0f, this->height_, 0.0f));

        std::vector vertexNormals(positions.size(), glm::vec3(0.0f, 0.0f, 0.0f));
        vertexNormals.front() = glm::vec3(0.0f, -1.0f, 0.0f);
        vertexNormals.back()  = glm::vec3(0.0f, 1.0f, 0.0f);

        // BOTTOM CIRCLE
        for (int i = 1; i <= this->segments_; ++i) {
            const unsigned curr = (i - 1) * (this->slices_ + 1u) + 1u;
            const unsigned next = i < this->segments_ ? i * (this->slices_ + 1u) + 1u : 1u;

            const glm::vec3 normalA = CalculateNormal(positions.front(), positions[curr], positions[next]);
            indecies.insert(indecies.end(), {0u, curr, next});
            vertexNormals[curr] += normalA;
        }

        // TOP CIRCLE
        for (int i = 1; i <= this->segments_; ++i) {
            const unsigned curr = i * (this->slices_ + 1u);
            const unsigned next = i < this->segments_ ? (i + 1u) * (this->slices_ + 1u) : this->slices_ + 1u;

            const glm::vec3 normalA = CalculateNormal(positions.back(), positions[curr], positions[next]);
            indecies.insert(indecies.end(), {static_cast<unsigned>(positions.size() - 1u), next, curr});
            vertexNormals[curr] += normalA;
        }

        // MIDDLE
        for (int i = 1; i <= this->slices_; ++i) {
            for (int j = 1; j <= this->segments_; ++j) {
                    const unsigned a = j < this->segments_ ? (this->slices_ * j) + i + j : i;
                    const unsigned b = j < this->segments_ ? (this->slices_ * j) + i + 1u + j : i + 1u;
                    const unsigned c = (this->slices_ * (j - 1)) + i + j - 1u;
                    const unsigned d = (this->slices_ * (j - 1)) + i + j;

                    const glm::vec3 normal = CalculateNormal(positions[b], positions[a], positions[c]) + CalculateNormal(positions[b], positions[c], positions[d]);
                    indecies.insert(indecies.end(), {b, a, c});
                    indecies.insert(indecies.end(), {b, c, d});
                    vertexNormals[a] += normal;
                    vertexNormals[b] += normal;
                    vertexNormals[c] += normal;
                    vertexNormals[d] += normal;
            }
        }

        for (auto& vn : vertexNormals) {
            vn = vn == glm::zero<glm::vec3>() ? vn : glm::normalize(vn);
        }

        positions.shrink_to_fit();
        vertexNormals.shrink_to_fit();
        indecies.shrink_to_fit();

        return MeshClass(
            positions,
            std::vector(positions.size(), this->color_),
            vertexNormals,
            std::vector(positions.size(), glm::zero<glm::vec3>()),
            indecies
        );
    }

private:
    float height_{};
    float radius_{};
    int segments_{};
    int slices_{};

    void ConstructorHelper_(int slices) {
        if (slices < 1) {
            throw std::runtime_error("Error: slices < 1");
        }

        this->slices_ = slices;
    }
};
