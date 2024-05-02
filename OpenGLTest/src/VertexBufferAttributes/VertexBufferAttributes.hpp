#pragma once
#include "Utils/Utils.hpp"

#include <vector>

enum class VertexBufferAttributesType : int {
    NONE          = 0,
    POSITION      = 1,
    COLOR         = 2,
    VERTEX_NORMAL = 3,
    FACE_NORMAL   = 4,
    TEXT_COORD    = 5,
    AMBIENT       = 6,
    DIFFUSE       = 7,
    SPECULAR      = 8,
    SHININESS     = 9,
};

struct VertexBufferAttributesElement {
    unsigned vertexDataCount{};
    unsigned totalDataCount{};
    ValueType valueType{};
    Normalize normalized{};
    VertexBufferAttributesType vbType{};
};

class VertexBufferAttributes {
public:
    explicit VertexBufferAttributes() = default;

    explicit VertexBufferAttributes(unsigned vertexDataCount, unsigned totalDataCount, ValueType type,
        Normalize normalized, VertexBufferAttributesType vbType);

    VertexBufferAttributes(const VertexBufferAttributes&);

    VertexBufferAttributes(VertexBufferAttributes&&) noexcept;

    VertexBufferAttributes& operator=(const VertexBufferAttributes&);

    VertexBufferAttributes& operator=(VertexBufferAttributes&&) noexcept;

    ~VertexBufferAttributes();

    const std::vector<VertexBufferAttributesElement>& GetElements() const;

    int GetStride() const;

    void Add(unsigned vertexDataCount, unsigned totalDataCount, ValueType type, Normalize normalized, VertexBufferAttributesType vbType);

private:
    std::vector<VertexBufferAttributesElement> elements_{};
    int stride_{};
};
