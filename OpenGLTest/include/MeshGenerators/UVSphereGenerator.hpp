#pragma once
#include "MeshGenerator.hpp"
#include "Utils.hpp"

#include <stdexcept>
#include <unordered_map>

class UVSphereGenerator : public MeshGenerator {
public:
    UVSphereGenerator() = delete;

    explicit UVSphereGenerator(float radius, int slices, int stacks, const glm::vec3& origin, const glm::vec3& color)
        : MeshGenerator(origin, color), radius_(radius) {
        this->ConstructorHelper_(slices, stacks);
    }

    UVSphereGenerator(const UVSphereGenerator&) = default;

    UVSphereGenerator(UVSphereGenerator&&) noexcept = default;

    UVSphereGenerator& operator=(const UVSphereGenerator&) = default;

    UVSphereGenerator& operator=(UVSphereGenerator&&) noexcept = default;

    ~UVSphereGenerator() override = default;

    MeshClass GenerateMesh() override {
        std::vector<glm::vec3> positions{};
        std::vector<unsigned> indecies{};

        positions.push_back(this->origin_ + glm::vec3(0.0f, this->radius_, 0.0f));

        for (int i = 0; i < this->stacks_ - 1; ++i) {
            const float alpha = static_cast<float>(i + 1) * glm::pi<float>() / static_cast<float>(this->stacks_);

            for (int j = 0; j < this->slices_; ++j) {
                const float beta = static_cast<float>(j) * glm::two_pi<float>() / static_cast<float>(this->slices_);

                positions.push_back(
                     this->origin_ + this->radius_ * glm::vec3(
                        glm::sin(alpha) * glm::cos(beta),
                        glm::cos(alpha),
                        glm::sin(alpha) * glm::sin(beta)
                     )
                );
            }
        }

        positions.push_back(this->origin_ - glm::vec3(0.0f, this->radius_, 0.0f));

        std::vector vertexNormals(positions.size(), glm::zero<glm::vec3>());
        std::vector faceNormals(positions.size(), glm::zero<glm::vec3>());

        vertexNormals.front() = glm::vec3(0.0f, 1.0f, 0.0f);
        vertexNormals.back()  = glm::vec3(0.0f, -1.0f, 0.0f);
        faceNormals.front()   = glm::vec3(0.0f, 1.0f, 0.0f);
        faceNormals.back()    = glm::vec3(0.0f, -1.0f, 0.0f);

        for (int i = 0; i < this->slices_; ++i) {
            unsigned i0 = i + 1;
            unsigned i1 = (i + 1) % this->slices_ + 1;
            indecies.insert(indecies.end(), {i0, 0u, i1});
            faceNormals[i0]    = CalculateNormal(positions[i0], positions[0u], positions[i1]);
            vertexNormals[i0] += faceNormals[i0];
            vertexNormals[i1] += faceNormals[i1];

            i0 = i + this->slices_ * (this->stacks_ - 2) + 1;
            i1 = (i + 1) % this->slices_ + this->slices_ * (this->stacks_ - 2) + 1;
            indecies.insert(indecies.end(), {i0, i1, static_cast<unsigned>(positions.size() - 1)});
            faceNormals[i0]    = CalculateNormal(positions[i0], positions[i1], positions[static_cast<unsigned>(positions.size() - 1)]);
            vertexNormals[i0] += faceNormals[i0];
            vertexNormals[i1] += faceNormals[i1];
        }

        for (int i = 0; i < this->stacks_ - 2; ++i) {
            unsigned i0 = i * this->slices_ + 1;
            unsigned i1 = (i + 1) * this->slices_ + 1;

            for (int j = 0; j < this->slices_; ++j) {
                unsigned j0 = i0 + j;
                unsigned j1 = i0 + (j + 1) % this->slices_;
                unsigned j2 = i1 + (j + 1) % this->slices_;
                unsigned j3 = i1 + j;

                indecies.insert(indecies.end(), {j0, j1, j2});
                indecies.insert(indecies.end(), {j0, j2, j3});
                faceNormals[j0]    = (CalculateNormal(positions[j0], positions[j1], positions[j2]) + CalculateNormal(positions[j0], positions[j2], positions[j3])) / 2.0f;
                vertexNormals[j0] += faceNormals[j0];
                vertexNormals[j1] += faceNormals[j1];
                vertexNormals[j2] += faceNormals[j2];
                vertexNormals[j3] += faceNormals[j3];
            }
        }

        for (auto& vn : vertexNormals) {
            vn = glm::normalize(vn);
        }

        auto temp = MeshClass(
            positions,
            std::vector(positions.size(), this->color_),
            vertexNormals,
            //faceNormals,
            std::vector(positions.size(), glm::zero<glm::vec3>()),
            indecies
        );

        return temp;
    }

private:
    float radius_{};
    int slices_{};
    int stacks_{};

    void ConstructorHelper_(int slices, int stacks) {
        if (slices < 3) {
            throw std::runtime_error("UV-sphere creating error: slices < 3");
        }
        if (stacks < 2) {
            throw std::runtime_error("UV-sphere creating error: stacks < 2");
        }

        this->slices_ = slices;
        this->stacks_ = stacks;
    }
};
