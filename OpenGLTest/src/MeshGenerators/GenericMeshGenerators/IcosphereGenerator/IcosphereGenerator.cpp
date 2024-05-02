#include "MeshGenerators/GenericMeshGenerators/IcosphereGenerator/IcosphereGenerator.hpp"
#include "MeshInstance/MeshInstance.hpp"

#include <glm/gtx/hash.hpp>

#include <unordered_map>
#include <array>


IcosphereGenerator::IcosphereGenerator(float radius, int iterations, const glm::vec3& origin, const glm::vec3& colors)
    : MeshGenerator(origin, colors), radius_(radius), iterations_(iterations) {

}

std::shared_ptr<IMeshInstance> IcosphereGenerator::GenerateMesh() {
    std::vector<glm::vec3> positions{};
    std::vector<unsigned> indecies{};

    const float plusGoldenRatio = glm::sqrt((5.0f + glm::sqrt(5.0f)) / 10.0f);
    const float minusGoldenRatio = glm::sqrt((5.0f - glm::sqrt(5.0f)) / 10.0f);

    // FIRST GOLDEN RECTANGLE OxOy
    positions.emplace_back(minusGoldenRatio, plusGoldenRatio, 0.0f);   // 0
    positions.emplace_back(-minusGoldenRatio, plusGoldenRatio, 0.0f);  // 1
    positions.emplace_back(-minusGoldenRatio, -plusGoldenRatio, 0.0f); // 2
    positions.emplace_back(minusGoldenRatio, -plusGoldenRatio, 0.0f);  // 3

    // SECOND GOLDEN RECTANGLE OxOz
    positions.emplace_back(plusGoldenRatio, 0.0f, minusGoldenRatio);   // 4
    positions.emplace_back(-plusGoldenRatio, 0.0f, minusGoldenRatio);  // 5
    positions.emplace_back(-plusGoldenRatio, 0.0f, -minusGoldenRatio); // 6
    positions.emplace_back(plusGoldenRatio, 0.0f, -minusGoldenRatio);  // 7

    // THIRD GOLDEN RECTANGLE OyOz
    positions.emplace_back(0.0f, minusGoldenRatio, plusGoldenRatio);   // 8
    positions.emplace_back(0.0f, -minusGoldenRatio, plusGoldenRatio);  // 9
    positions.emplace_back(0.0f, -minusGoldenRatio, -plusGoldenRatio); // 10
    positions.emplace_back(0.0f, minusGoldenRatio, -plusGoldenRatio);  // 11

    // 5 faces around 1st point
    indecies.insert(indecies.end(), { 1u, 5u, 8u });
    indecies.insert(indecies.end(), { 8u, 0u, 1u });
    indecies.insert(indecies.end(), { 0u, 11u, 1u });
    indecies.insert(indecies.end(), { 11u, 6u, 1u });
    indecies.insert(indecies.end(), { 6u, 5u, 1u });

    // 5 faces around 3rd point
    indecies.insert(indecies.end(), { 3u, 4u, 9u });
    indecies.insert(indecies.end(), { 9u, 2u, 3u });
    indecies.insert(indecies.end(), { 2u, 10u, 3u });
    indecies.insert(indecies.end(), { 10u, 7u, 3u });
    indecies.insert(indecies.end(), { 7u, 4u, 3u });

    // 5 faces adjacent to 1st
    indecies.insert(indecies.end(), { 4u, 0u, 8u });
    indecies.insert(indecies.end(), { 5u, 9u, 8u });
    indecies.insert(indecies.end(), { 6u, 2u, 5u });
    indecies.insert(indecies.end(), { 11u, 10u, 6u });
    indecies.insert(indecies.end(), { 0u, 7u, 11u });

    // 5 faces adjacent to 3rd
    indecies.insert(indecies.end(), { 9u, 4u, 8u });
    indecies.insert(indecies.end(), { 2u, 9u, 5u });
    indecies.insert(indecies.end(), { 10u, 2u, 6u });
    indecies.insert(indecies.end(), { 7u, 10u, 11u });
    indecies.insert(indecies.end(), { 4u, 7u, 0u });

    for (int i = 0; i < this->iterations_ - 1; ++i) {
        std::unordered_map<glm::vec3, unsigned> positionsToIndecies{};
        std::vector<unsigned> tempIndecies{};

        for (int j = 0; j < indecies.size(); j += 3) {
            const glm::vec3& a = positions[indecies[j]];
            const glm::vec3& b = positions[indecies[j + 1]];
            const glm::vec3& c = positions[indecies[j + 2]];

            std::array<glm::vec3, 3> triangle{ a, b, c };

            for (int k = 0; k < triangle.size(); ++k) {
                if (!positionsToIndecies.contains(triangle[k])) {
                    positionsToIndecies.emplace(triangle[k], positionsToIndecies.size());
                }
            }

            const glm::vec3& ab = glm::normalize((a + b) / 2.0f);
            const glm::vec3& bc = glm::normalize((b + c) / 2.0f);
            const glm::vec3& ca = glm::normalize((c + a) / 2.0f);

            triangle = { ab, bc, ca };

            for (int k = 0; k < triangle.size(); ++k) {
                if (!positionsToIndecies.contains(triangle[k])) {
                    positionsToIndecies.emplace(triangle[k], positionsToIndecies.size());
                }
            }

            tempIndecies.insert(tempIndecies.end(), { positionsToIndecies[ab], positionsToIndecies[bc], positionsToIndecies[ca] });
            tempIndecies.insert(tempIndecies.end(), { positionsToIndecies[bc], positionsToIndecies[c], positionsToIndecies[ca] });
            tempIndecies.insert(tempIndecies.end(), { positionsToIndecies[ca], positionsToIndecies[a], positionsToIndecies[ab] });
            tempIndecies.insert(tempIndecies.end(), { positionsToIndecies[b], positionsToIndecies[bc], positionsToIndecies[ab] });
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
        normals[i] = glm::normalize(positions[i]);
        positions[i] = this->origin_ + this->radius_ * positions[i];
    }

    return std::make_shared<MeshInstance>(
        positions,
        std::vector(positions.size(), this->color_),
        normals,
        std::vector(positions.size(), glm::zero<glm::vec3>()),
        indecies
    );
}
