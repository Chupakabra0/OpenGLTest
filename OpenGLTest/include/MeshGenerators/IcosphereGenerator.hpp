#pragma once
#include "MeshGenerator.hpp"

#include <glm/gtx/hash.hpp>

#include <unordered_map>
#include <array>

class IcosphereGenerator : public MeshGenerator {
public:
    explicit IcosphereGenerator(float radius, int iterations, const glm::vec3& origin, const glm::vec3& colors)
        : MeshGenerator(origin, colors), radius_(radius), iterations_(iterations) {

    }

    IcosphereGenerator(const IcosphereGenerator&) = default;

    IcosphereGenerator(IcosphereGenerator&&) noexcept = default;

    IcosphereGenerator& operator=(const IcosphereGenerator&) = default;

    IcosphereGenerator& operator=(IcosphereGenerator&&) noexcept = default;

    ~IcosphereGenerator() override = default;

    MeshClass GenerateMesh() override {
        std::vector<glm::vec3> positions{};
        std::vector<unsigned> indecies{};

        const float plusGoldenRatio  = glm::sqrt((5.0f + glm::sqrt(5.0f)) / 10.0f);
        const float minusGoldenRatio = glm::sqrt((5.0f - glm::sqrt(5.0f)) / 10.0f);

        // FIRST GOLDEN RECTANGLE OxOy
        positions.push_back(
            glm::vec3(
                minusGoldenRatio,
                plusGoldenRatio,
                0.0f
            )
        ); // 0
        positions.push_back(
            glm::vec3(
                -minusGoldenRatio,
                plusGoldenRatio,
                0.0f
            )
        ); // 1
        positions.push_back(
            glm::vec3(
                -minusGoldenRatio,
                -plusGoldenRatio,
                0.0f
            )
        ); // 2
        positions.push_back(
            glm::vec3(
                minusGoldenRatio,
                -plusGoldenRatio,
                0.0f
            )
        ); // 3

        // SECOND GOLDEN RECTANGLE OxOz
        positions.push_back(
            glm::vec3(
                plusGoldenRatio,
                0.0f,
                minusGoldenRatio
            )
        ); // 4
        positions.push_back(
            glm::vec3(
                -plusGoldenRatio,
                0.0f,
                minusGoldenRatio
            )
        ); // 5
        positions.push_back(
            glm::vec3(
                -plusGoldenRatio,
                0.0f,
                -minusGoldenRatio
            )
        ); // 6
        positions.push_back(
            glm::vec3(
                plusGoldenRatio,
                0.0f,
                -minusGoldenRatio
            )
        ); // 7

        // THIRD GOLDEN RECTANGLE OyOz
        positions.push_back(
            glm::vec3(
                0.0f,
                minusGoldenRatio,
                plusGoldenRatio
            )
        ); // 8
        positions.push_back(
            glm::vec3(
                0.0f,
                -minusGoldenRatio,
                plusGoldenRatio
            )
        ); // 9
        positions.push_back(
            glm::vec3(
                0.0f,
                -minusGoldenRatio,
                -plusGoldenRatio
            )
        ); // 10
        positions.push_back(
            glm::vec3(
                0.0f,
                minusGoldenRatio,
                -plusGoldenRatio
            )
        ); // 11

        // Duplicate positions (to attach different face normals)
        //positions.push_back(positions[0]);  // 12
        //positions.push_back(positions[2]);  // 13
        //positions.push_back(positions[4]);  // 14
        //positions.push_back(positions[6]);  // 15
        //positions.push_back(positions[7]);  // 16
        //positions.push_back(positions[9]);  // 17
        //positions.push_back(positions[10]); // 18
        //positions.push_back(positions[11]); // 19

        // 0  1  2  3  4  5  6  7  8  9  10 11
        // 12 __ 13 __ 14 __ 15 16 __ 17 18 19

        // 5 faces around 1st point
        indecies.insert(indecies.end(), {1u, 5u, 8u});
        indecies.insert(indecies.end(), {8u, 0u, 1u});
        indecies.insert(indecies.end(), {0u, 11u, 1u});
        indecies.insert(indecies.end(), {11u, 6u, 1u});
        indecies.insert(indecies.end(), {6u, 5u, 1u});

        // 5 faces around 3rd point
        indecies.insert(indecies.end(), {3u, 4u, 9u});
        indecies.insert(indecies.end(), {9u, 2u, 3u});
        indecies.insert(indecies.end(), {2u, 10u, 3u});
        indecies.insert(indecies.end(), {10u, 7u, 3u});
        indecies.insert(indecies.end(), {7u, 4u, 3u});

        // 5 faces adjacent to 1st
        indecies.insert(indecies.end(), {4u, 0u, 8u});
        indecies.insert(indecies.end(), {5u, 9u, 8u});
        //// Start of duplication vertices usage
        //indecies.insert(indecies.end(), {15u, 2u, 5u});   //
        //indecies.insert(indecies.end(), {19u, 10u, 6u});  //
        //indecies.insert(indecies.end(), {12u, 7u, 11u});  //

        //// 5 faces adjacent to 3rd
        //indecies.insert(indecies.end(), {17u, 4u, 8u});   //
        //indecies.insert(indecies.end(), {13u, 9u, 5u});   //
        //indecies.insert(indecies.end(), {18u, 2u, 6u});   //
        //indecies.insert(indecies.end(), {16u, 10u, 11u}); //
        //indecies.insert(indecies.end(), {14u, 7u, 0u});   //

        indecies.insert(indecies.end(), {6u, 2u, 5u});   //
        indecies.insert(indecies.end(), {11u, 10u, 6u}); //
        indecies.insert(indecies.end(), {0u, 7u, 11u});  //

        // 5 faces adjacent to 3rd
        indecies.insert(indecies.end(), {9u, 4u, 8u});   //
        indecies.insert(indecies.end(), {2u, 9u, 5u});   //
        indecies.insert(indecies.end(), {10u, 2u, 6u});  //
        indecies.insert(indecies.end(), {7u, 10u, 11u}); //
        indecies.insert(indecies.end(), {4u, 7u, 0u});   //

        for (int i = 0; i < this->iterations_ - 1; ++i) {
            std::unordered_map<glm::vec3, unsigned> positionsToIndecies{};
            std::vector<unsigned> tempIndecies{};

            for (int j = 0; j < indecies.size(); j += 3) {
                const glm::vec3& a = positions[indecies[j]];
                const glm::vec3& b = positions[indecies[j + 1]];
                const glm::vec3& c = positions[indecies[j + 2]];

                std::array<glm::vec3, 3> triangle{a, b, c};

                for (int k = 0; k < triangle.size(); ++k) {
                    if (!positionsToIndecies.contains(triangle[k])) {
                        positionsToIndecies.emplace(triangle[k], positionsToIndecies.size());
                    }
                }

                const glm::vec3& ab = glm::normalize((a + b) / 2.0f);
                const glm::vec3& bc = glm::normalize((b + c) / 2.0f);
                const glm::vec3& ca = glm::normalize((c + a) / 2.0f);

                triangle = {ab, bc, ca};

                for (int k = 0; k < triangle.size(); ++k) {
                    if (!positionsToIndecies.contains(triangle[k])) {
                        positionsToIndecies.emplace(triangle[k], positionsToIndecies.size());
                    }
                }

                tempIndecies.insert(tempIndecies.end(), {positionsToIndecies[ab], positionsToIndecies[bc], positionsToIndecies[ca]});
                tempIndecies.insert(tempIndecies.end(), {positionsToIndecies[bc], positionsToIndecies[c], positionsToIndecies[ca]});
                tempIndecies.insert(tempIndecies.end(), {positionsToIndecies[ca], positionsToIndecies[a], positionsToIndecies[ab]});
                tempIndecies.insert(tempIndecies.end(), {positionsToIndecies[b], positionsToIndecies[bc], positionsToIndecies[ab]});
            }

            positions.clear();
            positions.resize(positionsToIndecies.size());

            for (const auto& [vec, ind] : positionsToIndecies) {
                positions[ind] = vec;
            }

            std::swap(tempIndecies, indecies);
        }

        std::vector<glm::vec3> normals(positions.size(), glm::zero<glm::vec3>());
        for (int i = 0; i < positions.size(); ++i) {
            normals[i]   = glm::normalize(positions[i]);
            positions[i] = this->origin_ + this->radius_ * positions[i];
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
    float radius_{};
    int iterations_{};
};
