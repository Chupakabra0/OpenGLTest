#include "IcosahedronGenerator.hpp"

#include "MeshInstance/MeshInstance.hpp"

IcosahedronGenerator::IcosahedronGenerator(float radius, const glm::vec3& origin, const glm::vec3& color)
    : MeshGenerator(origin, color), radius_(radius) {

}

std::shared_ptr<IMeshInstance> IcosahedronGenerator::GenerateMesh() {
    std::vector<glm::vec3> positions{};
    std::vector<unsigned> indecies{};

    const float plusGoldenRatio = glm::sqrt((5.0f + glm::sqrt(5.0f)) / 10.0f);
    const float minusGoldenRatio = glm::sqrt((5.0f - glm::sqrt(5.0f)) / 10.0f);

    // FIRST GOLDEN RECTANGLE OxOy
    positions.push_back(
        this->origin_ + this->radius_ * glm::vec3(
            minusGoldenRatio,
            plusGoldenRatio,
            0.0f
        )
    ); // 0
    positions.push_back(
        this->origin_ + this->radius_ * glm::vec3(
            -minusGoldenRatio,
            plusGoldenRatio,
            0.0f
        )
    ); // 1
    positions.push_back(
        this->origin_ + this->radius_ * glm::vec3(
            -minusGoldenRatio,
            -plusGoldenRatio,
            0.0f
        )
    ); // 2
    positions.push_back(
        this->origin_ + this->radius_ * glm::vec3(
            minusGoldenRatio,
            -plusGoldenRatio,
            0.0f
        )
    ); // 3

    // SECOND GOLDEN RECTANGLE OxOz
    positions.push_back(
        this->origin_ + this->radius_ * glm::vec3(
            plusGoldenRatio,
            0.0f,
            minusGoldenRatio
        )
    ); // 4
    positions.push_back(
        this->origin_ + this->radius_ * glm::vec3(
            -plusGoldenRatio,
            0.0f,
            minusGoldenRatio
        )
    ); // 5
    positions.push_back(
        this->origin_ + this->radius_ * glm::vec3(
            -plusGoldenRatio,
            0.0f,
            -minusGoldenRatio
        )
    ); // 6
    positions.push_back(
        this->origin_ + this->radius_ * glm::vec3(
            plusGoldenRatio,
            0.0f,
            -minusGoldenRatio
        )
    ); // 7

    // THIRD GOLDEN RECTANGLE OyOz
    positions.push_back(
        this->origin_ + this->radius_ * glm::vec3(
            0.0f,
            minusGoldenRatio,
            plusGoldenRatio
        )
    ); // 8
    positions.push_back(
        this->origin_ + this->radius_ * glm::vec3(
            0.0f,
            -minusGoldenRatio,
            plusGoldenRatio
        )
    ); // 9
    positions.push_back(
        this->origin_ + this->radius_ * glm::vec3(
            0.0f,
            -minusGoldenRatio,
            -plusGoldenRatio
        )
    ); // 10
    positions.push_back(
        this->origin_ + this->radius_ * glm::vec3(
            0.0f,
            minusGoldenRatio,
            -plusGoldenRatio
        )
    ); // 11

    // Duplicate positions (to attach different face normals)
    positions.push_back(positions[0]);  // 12
    positions.push_back(positions[2]);  // 13
    positions.push_back(positions[4]);  // 14
    positions.push_back(positions[6]);  // 15
    positions.push_back(positions[7]);  // 16
    positions.push_back(positions[9]);  // 17
    positions.push_back(positions[10]); // 18
    positions.push_back(positions[11]); // 19

    // 0  1  2  3  4  5  6  7  8  9  10 11
    // 12 __ 13 __ 14 __ 15 16 __ 17 18 19

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
    // Start of duplication vertices usage
    indecies.insert(indecies.end(), { 15u, 2u, 5u });   //
    indecies.insert(indecies.end(), { 19u, 10u, 6u });  //
    indecies.insert(indecies.end(), { 12u, 7u, 11u });  //

    // 5 faces adjacent to 3rd
    indecies.insert(indecies.end(), { 17u, 4u, 8u });   //
    indecies.insert(indecies.end(), { 13u, 9u, 5u });   //
    indecies.insert(indecies.end(), { 18u, 2u, 6u });   //
    indecies.insert(indecies.end(), { 16u, 10u, 11u }); //
    indecies.insert(indecies.end(), { 14u, 7u, 0u });   //

    //for (int i = 0; i < this->iterations_ - 1; ++i) {
    //    std::unordered_map<glm::vec3, unsigned> tempPositions{};
    //    std::vector<unsigned> tempIndecies{};

    //    for (int j = 0; j < indecies.size(); j += 3) {
    //        const glm::vec3& a = positions[indecies[j]];
    //        const glm::vec3& b = positions[indecies[j + 1]];
    //        const glm::vec3& c = positions[indecies[j + 2]];

    //        if (!tempPositions.contains(a)) {
    //            tempPositions.emplace(a, tempPositions.size());
    //        }
    //        if (!tempPositions.contains(b)) {
    //            tempPositions.emplace(b, tempPositions.size());
    //        }
    //        if (!tempPositions.contains(c)) {
    //            tempPositions.emplace(c, tempPositions.size());
    //        }

    //        const glm::vec3& ab = (a + b) / 2.0f;
    //        const glm::vec3& bc = (b + c) / 2.0f;
    //        const glm::vec3& ca = (c + a) / 2.0f;

    //        if (!tempPositions.contains(ab)) {
    //            tempPositions.emplace(ab, tempPositions.size());
    //        }
    //        if (!tempPositions.contains(bc)) {
    //            tempPositions.emplace(bc, tempPositions.size());
    //        }
    //        if (!tempPositions.contains(ca)) {
    //            tempPositions.emplace(ca, tempPositions.size());
    //        }

    //        tempIndecies.insert(tempIndecies.end(), {tempPositions[ab], tempPositions[bc], tempPositions[ca]});
    //        tempIndecies.insert(tempIndecies.end(), {tempPositions[bc], tempPositions[c], tempPositions[ca]});
    //        tempIndecies.insert(tempIndecies.end(), {tempPositions[ca], tempPositions[a], tempPositions[ab]});
    //        tempIndecies.insert(tempIndecies.end(), {tempPositions[b], tempPositions[bc], tempPositions[ab]});
    //    }

    //    positions.clear();
    //    positions.resize(tempPositions.size());

    //    for (const auto& [vec, ind] : tempPositions) {
    //        positions[ind] = vec;
    //    }

    //    std::swap(tempIndecies, indecies);
    //}

    std::vector<glm::vec3> vertexNormals(positions.size(), glm::zero<glm::vec3>());
    std::vector<glm::vec3> faceNormals(positions.size(), glm::zero<glm::vec3>());
    std::unordered_map<glm::vec3, std::pair<glm::vec3, int>> vertexNormalsMap{};
    std::unordered_map<unsigned, std::pair<glm::vec3, int>> faceNormalsMap{};

    for (int i = 0; i < indecies.size(); i += 3) {
        const glm::vec3& a = positions[indecies[i]];
        const glm::vec3& b = positions[indecies[i + 1]];
        const glm::vec3& c = positions[indecies[i + 2]];

        const glm::vec3 n = CalculateNormal(a, b, c);

        faceNormalsMap[indecies[i]] = std::make_pair(faceNormalsMap[indecies[i]].first + n, faceNormalsMap[indecies[i]].second + 1);

        for (int j = 0; j < 3; ++j) {
            vertexNormalsMap[positions[indecies[i + j]]] = std::make_pair(vertexNormalsMap[positions[indecies[i + j]]].first + n, vertexNormalsMap[positions[indecies[i + j]]].second + 1);
        }
    }

    for (int i = 0; i < vertexNormals.size(); ++i) {
        const auto& [vec, cnt] = vertexNormalsMap[positions[i]];
        vertexNormals[i] = glm::normalize(vec);
    }
    for (int i = 0; i < faceNormals.size(); ++i) {
        const auto& [vec, cnt] = faceNormalsMap[i];
        faceNormals[i] = glm::normalize(vec);
    }

    return std::make_shared<MeshInstance>(
        positions,
        std::vector(positions.size(), this->color_),
        vertexNormals,
        //faceNormals,
        std::vector(positions.size(), glm::zero<glm::vec3>()),      // TODO: texture coords
        indecies
    );
}
