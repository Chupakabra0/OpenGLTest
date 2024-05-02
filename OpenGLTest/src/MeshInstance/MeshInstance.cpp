#include "MeshInstance/MeshInstance.hpp"

MeshInstance::MeshInstance(const std::vector<glm::vec3>& positions, const std::vector<glm::vec3>& colors,
    const std::vector<glm::vec3>& vertexNormals, const std::vector<glm::vec3>& textures, const std::vector<unsigned>& indecies)
    : indecies_(indecies), positions_(positions), colors_(colors), vertexNormals_(vertexNormals), textCoords_(textures) {

}

void MeshInstance::AddVertex(const glm::vec3& position, const glm::vec3& color, const glm::vec3& vertexNormal, const glm::vec3& texture) {
    this->positions_.push_back(position);
    this->colors_.push_back(color);
    this->vertexNormals_.push_back(vertexNormal);
    this->textCoords_.push_back(texture);
}

void MeshInstance::SetTexture(unsigned index, const glm::vec3& texture) {
    if (index >= this->textCoords_.size()) {
        throw std::runtime_error("Setting texture error! Needed vertex does not exist!");
    }

    this->textCoords_[index] = texture;
}

void MeshInstance::SetVertexNormal(unsigned index, const glm::vec3& normal) {
    if (index >= this->vertexNormals_.size()) {
        throw std::runtime_error("Setting normal error! Needed vertex does not exist!");
    }

    this->vertexNormals_[index] = normal;
}

void MeshInstance::SetColor(unsigned index, const glm::vec3& color) {
    if (index >= this->colors_.size()) {
        throw std::runtime_error("Setting color error! Needed vertex does not exist!");
    }

    this->colors_[index] = color;
}

void MeshInstance::SetPosition(unsigned index, const glm::vec3& position) {
    if (index >= this->positions_.size()) {
        throw std::runtime_error("Setting texture error! Needed vertex does not exist!");
    }

    this->positions_[index] = position;
}

void MeshInstance::AddFace(unsigned a, unsigned b, unsigned c) {
    if (a >= this->positions_.size() || b >= this->positions_.size() || c >= this->positions_.size()) {
        throw std::runtime_error("Face creation error! Needed vertex does not exist!");
    }

    this->indecies_.push_back(a);
    this->indecies_.push_back(b);
    this->indecies_.push_back(c);
}

IndexBufferObject MeshInstance::GenerateIBO() const {
    return IndexBufferObject{this->indecies_};
}

VertexArrayObject MeshInstance::GenerateVAO(IndexBufferObject* ibo) const {
    VertexArrayObject vao{ibo};
    constexpr unsigned vertexSize{3u};

    // Positions init
    const VertexBufferAttributes positionsAttribute{
        vertexSize, static_cast<unsigned>(this->positions_.size()), ValueType::FLOAT, Normalize::NOT_NORMALIZE, VertexBufferAttributesType::POSITION
    };

    // Colors init
    const VertexBufferAttributes colorAttribute{
        vertexSize, static_cast<unsigned>(this->colors_.size()), ValueType::FLOAT, Normalize::NOT_NORMALIZE, VertexBufferAttributesType::COLOR
    };

    // Vertices' normals init
    const VertexBufferAttributes vertexNormalsAttribute{
        vertexSize, static_cast<unsigned>(this->vertexNormals_.size()), ValueType::FLOAT, Normalize::NORMALIZE, VertexBufferAttributesType::VERTEX_NORMAL
    };

    // TextureInstance init
    const VertexBufferAttributes textureAttribute{
        vertexSize, static_cast<unsigned>(this->textCoords_.size()), ValueType::FLOAT, Normalize::NOT_NORMALIZE, VertexBufferAttributesType::TEXT_COORD
    };

    vao.AddBuffer(this->positions_, positionsAttribute);
    vao.AddBuffer(this->colors_, colorAttribute);
    vao.AddBuffer(this->vertexNormals_, vertexNormalsAttribute);
    vao.AddBuffer(this->textCoords_, textureAttribute);

    return vao;
}

const std::vector<unsigned>& MeshInstance::GetIndecies() const {
    return this->indecies_;
}

const std::vector<glm::vec3>& MeshInstance::GetPositions() const {
    return this->positions_;
}

const std::vector<glm::vec3>& MeshInstance::GetColors() const {
    return this->colors_;
}

const std::vector<glm::vec3>& MeshInstance::GetVertexNormals() const {
    return this->vertexNormals_;
}

const std::vector<glm::vec3>& MeshInstance::GetTextCoords() const {
    return this->textCoords_;
}
