#include "MeshGenerators/GenericMeshGenerators/TorusGenerator/TorusGenerator.hpp"
#include "MeshInstance/MeshInstance.hpp"

TorusGenerator::TorusGenerator(float innerRadius, float outerRadius, int divSlices, int divLoops, const glm::vec3& origin, const glm::vec3& color)
    : MeshGenerator(origin, color), innerRadius_(innerRadius), outerRadius_(outerRadius), divSlices_(divSlices), divLoops_(divLoops) {
    this->ConstructorHelper_(divSlices, divLoops);
}

std::shared_ptr<IMeshInstance> TorusGenerator::GenerateMesh() {
    std::vector<glm::vec3> positions{};
    std::vector<glm::vec3> normals{};
    std::vector<unsigned> indecies{};

    for (int i = 0; i < this->divSlices_; ++i) {
        const float v = static_cast<float>(i) / this->divSlices_ * glm::two_pi<float>();
        const float cosSlices = glm::cos(v);
        const float sinSlices = glm::sin(v);
        const float sliceRad = this->outerRadius_ + this->innerRadius_ * cosSlices;

        for (int j = 0; j < this->divLoops_; ++j) {
            const float u = static_cast<float>(j) / this->divLoops_ * glm::two_pi<float>();
            const float cosLoops = glm::cos(u);
            const float sinLoops = glm::sin(u);

            const float x = sliceRad * cosLoops;
            const float y = sliceRad * sinLoops;
            const float z = this->innerRadius_ * sinSlices;

            const glm::vec3 temp = glm::vec3(x, y, z);

            positions.push_back(this->origin_ + temp);
            normals.emplace_back(
                cosSlices * cosLoops,
                cosSlices * sinLoops,
                sinSlices
            );
        }
    }

    for (int i = 0; i < this->divSlices_; i++) {
        const unsigned iNext = (i + 1) % this->divSlices_;
        for (int j = 0; j < this->divLoops_; j++) {
            const unsigned jNext = (j + 1) % this->divLoops_;
            const unsigned i0 = i * this->divLoops_ + j;
            const unsigned i1 = i * this->divLoops_ + jNext;
            const unsigned i2 = iNext * this->divLoops_ + jNext;
            const unsigned i3 = iNext * this->divLoops_ + j;

            indecies.insert(indecies.end(), { i1, i3, i0 });
            indecies.insert(indecies.end(), { i1, i2, i3 });
        }
    }

    return std::make_shared<MeshInstance>(
        positions,
        std::vector(positions.size(), this->color_),
        normals,
        std::vector(positions.size(), glm::zero<glm::vec3>()),
        indecies
    );
}

void TorusGenerator::ConstructorHelper_(int divSlices, int divLoops) {
    if (divSlices < 3) {
        throw std::runtime_error("Torus creating error: divSlices < 3");
    }

    if (divLoops < 3) {
        throw std::runtime_error("Torus creating error: divLoops < 3");
    }

    this->divSlices_ = divSlices;
    this->divLoops_  = divLoops;
}
