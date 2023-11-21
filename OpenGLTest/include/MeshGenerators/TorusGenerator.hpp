#pragma once

#include "MeshGenerator.hpp"

class TorusGenerator : public MeshGenerator {
public:
    explicit TorusGenerator(float innerRadius, float outerRadius, int divWidth, int divHeight, const glm::vec3& origin, const glm::vec3& color)
        : MeshGenerator(origin, color), innerRadius_(innerRadius), outerRadius_(outerRadius), divWidth_(divWidth), divHeight_(divHeight) {
        this->ConstructorHelper_();
    }

    TorusGenerator(const TorusGenerator&) = default;

    TorusGenerator(TorusGenerator&&) noexcept = default;

    TorusGenerator& operator=(const TorusGenerator&) = default;

    TorusGenerator& operator=(TorusGenerator&&) noexcept = default;

    ~TorusGenerator() noexcept = default;

    MeshClass GenerateMesh() override {
        std::vector<glm::vec3> positions{};
        std::vector<glm::vec3> normals{};
        std::vector<unsigned> indecies{};

        for (int i = 0; i < this->divWidth_; ++i) {
            const auto v           = static_cast<float>(i) / this->divWidth_;
            const auto slice_angle = v * glm::two_pi<float>();
            const auto cos_slices  = glm::cos(slice_angle);
            const auto sin_slices  = glm::sin(slice_angle);
            const auto slice_rad   = this->outerRadius_ + this->innerRadius_ * cos_slices;
            
            for (int j = 0; j < this->divHeight_; ++j) {
                const auto u          = static_cast<float>(j) / this->divHeight_;
                const auto loop_angle = u * glm::two_pi<float>();
                const auto cos_loops  = glm::cos(loop_angle);
                const auto sin_loops  = glm::sin(loop_angle);

                const auto x = slice_rad * cos_loops;
                const auto y = slice_rad * sin_loops;
                const auto z = this->innerRadius_ * sin_slices;

                const glm::vec3 temp = glm::vec3(x, y, z);

                positions.push_back(this->origin_ + temp);
                normals.push_back(glm::normalize(temp));
            }
        }

        for (int i = 0; i < this->divWidth_; i++) {
            auto i_next = (i + 1) % this->divWidth_;
            for (int j = 0; j < this->divHeight_; j++) {
                const unsigned j_next = (j + 1) % this->divHeight_;
                const unsigned i0 = i * this->divHeight_ + j;
                const unsigned i1 = i * this->divHeight_ + j_next;
                const unsigned i2 = i_next * this->divHeight_ + j_next;
                const unsigned i3 = i_next * this->divHeight_ + j;

                indecies.insert(indecies.end(), {i3, i1, i0});
                indecies.insert(indecies.end(), {i3, i1, i2});
            }
        }

        return MeshClass(
            positions,
            std::vector(positions.size(), this->color_),
            normals,
            std::vector(positions.size(), glm::zero<glm::vec3>()),
            indecies
        );
    }

private:
    float innerRadius_{};
    float outerRadius_{};
    int divWidth_{};
    int divHeight_{};

    void ConstructorHelper_() {

    }
};
