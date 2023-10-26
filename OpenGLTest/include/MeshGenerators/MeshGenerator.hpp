#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/transform.hpp>

#include <vector>
#include <stdexcept>

#include "VertexArrayObject.hpp"

class MeshClass {
public:
    explicit MeshClass() = default;

    //explicit MeshClass(const std::vector<glm::vec3>& positions, const std::vector<glm::vec3>& colors, const std::vector<glm::vec3>& vertexNormals,
    //    const std::vector<glm::vec3>& faceNormals, const std::vector<glm::vec3>& textures, const std::vector<unsigned>& indecies)
    //    : indecies_(indecies), positions_(positions), colors_(colors), vertexNormals_(vertexNormals), faceNormals_(faceNormals), textCoords_(textures) {

    //}

    explicit MeshClass(const std::vector<glm::vec3>& positions, const std::vector<glm::vec3>& colors, const std::vector<glm::vec3>& vertexNormals,
        const std::vector<glm::vec3>& textures, const std::vector<unsigned>& indecies)
        : indecies_(indecies), positions_(positions), colors_(colors), vertexNormals_(vertexNormals), textCoords_(textures) {

    }

    //void AddVertex(const glm::vec3& position, const glm::vec3& color,
    //    const glm::vec3& vertexNormal = glm::zero<glm::vec3>(), const glm::vec3& faceNormal = glm::zero<glm::vec3>(),
    //    const glm::vec3& texture = glm::zero<glm::vec3>()) {
    //    this->positions_.push_back(position);
    //    this->colors_.push_back(color);
    //    this->vertexNormals_.push_back(vertexNormal);
    //    this->faceNormals_.push_back(faceNormal);
    //    this->textCoords_.push_back(texture);
    //}

    void AddVertex(const glm::vec3& position, const glm::vec3& color,
        const glm::vec3& vertexNormal = glm::zero<glm::vec3>(), const glm::vec3& texture = glm::zero<glm::vec3>()) {
        this->positions_.push_back(position);
        this->colors_.push_back(color);
        this->vertexNormals_.push_back(vertexNormal);
        this->textCoords_.push_back(texture);
    }

    void SetTexture(unsigned index, const glm::vec3& texture) {
        if (index >= this->textCoords_.size()) {
            throw std::runtime_error("Setting texture error! Needed vertex does not exist!");
        }

        this->textCoords_[index] = texture;
    }

    void SetVertexNormal(unsigned index, const glm::vec3& normal) {
        if (index >= this->vertexNormals_.size()) {
            throw std::runtime_error("Setting normal error! Needed vertex does not exist!");
        }

        this->vertexNormals_[index] = normal;
    }

    //void SetFaceNormal(unsigned index, const glm::vec3& normal) {
    //    if (index >= this->faceNormals_.size()) {
    //        throw std::runtime_error("Setting normal error! Needed vertex does not exist!");
    //    }

    //    this->faceNormals_[index] = normal;
    //}

    void SetColor(unsigned index, const glm::vec3& color) {
        if (index >= this->colors_.size()) {
            throw std::runtime_error("Setting color error! Needed vertex does not exist!");
        }

        this->colors_[index] = color;
    }

    void SetPosition(unsigned index, const glm::vec3& position) {
        if (index >= this->positions_.size()) {
            throw std::runtime_error("Setting texture error! Needed vertex does not exist!");
        }

        this->positions_[index] = position;
    }

    void AddFace(unsigned a, unsigned b, unsigned c) {
        if (a >= this->positions_.size() || b >= this->positions_.size() || c >= this->positions_.size()) {
            throw std::runtime_error("Face creation error! Needed vertex does not exist!");
        }

        this->indecies_.push_back(a);
        this->indecies_.push_back(b);
        this->indecies_.push_back(c);
    }

    IndexBufferObject GenerateIBO() const {
        return IndexBufferObject{this->indecies_};
    }

    VertexArrayObject GenerateVAO(IndexBufferObject* ibo = nullptr) const {
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

        // Faces' normals init
        //const VertexBufferAttributes faceNormalsAttribute{
        //    vertexSize, static_cast<unsigned>(this->faceNormals_.size()), ValueType::FLOAT, Normalize::NORMALIZE, VertexBufferAttributesType::FACE_NORMAL
        //};

        // Texture init
        const VertexBufferAttributes textureAttribute{
            vertexSize, static_cast<unsigned>(this->textCoords_.size()), ValueType::FLOAT, Normalize::NOT_NORMALIZE, VertexBufferAttributesType::TEXT_COORD
        };

        vao.AddBuffer(this->positions_, positionsAttribute);
        vao.AddBuffer(this->colors_, colorAttribute);
        vao.AddBuffer(this->vertexNormals_, vertexNormalsAttribute);
        //vao.AddBuffer(this->faceNormals_, faceNormalsAttribute);
        vao.AddBuffer(this->textCoords_, textureAttribute);

        return vao;
    }

    const std::vector<unsigned>& GetIndecies() const {
        return this->indecies_;
    }

    const std::vector<glm::vec3>& GetPositions() const {
        return this->positions_;
    }

    const std::vector<glm::vec3>& GetColors() const {
        return this->colors_;
    }

    const std::vector<glm::vec3>& GetVertexNormals() const {
        return this->vertexNormals_;
    }

    //const std::vector<glm::vec3>& GetFaceNormals() const {
    //    return this->faceNormals_;
    //}

    const std::vector<glm::vec3>& GetTextCoords() const {
        return this->textCoords_;
    }

    //void SetTexture(const std::shared_ptr<Texture>& texture) {
    //    this->texture_ = texture;
    //}

private:
    //std::shared_ptr<Texture> texture_{};
    std::vector<unsigned> indecies_{};
    std::vector<glm::vec3> positions_{};
    std::vector<glm::vec3> colors_{};
    std::vector<glm::vec3> vertexNormals_{};
    //std::vector<glm::vec3> faceNormals_{};
    std::vector<glm::vec3> textCoords_{};
};

struct MeshGenerator {
public:
    MeshGenerator() = delete;

    explicit MeshGenerator(const glm::vec3& origin, const glm::vec3& color)
        : origin_(origin), color_(color) {

    }

    MeshGenerator(const MeshGenerator&) = default;

    MeshGenerator(MeshGenerator&&) noexcept = default;

    MeshGenerator& operator=(const MeshGenerator&) = default;

    MeshGenerator& operator=(MeshGenerator&&) noexcept = default;

    virtual ~MeshGenerator() = default;

    virtual MeshClass GenerateMesh() = 0;

    const glm::vec3& GetOrigin() const {
        return this->origin_;
    }

    void SetOrigin(const glm::vec3& origin) {
        this->origin_ = origin;
    }

    const glm::vec3& GetColor() const {
        return this->color_;
    }

    void SetColor(const glm::vec3& color) {
        this->color_ = color;
    }

protected:
    glm::vec3 origin_{};
    glm::vec3 color_{};
};
