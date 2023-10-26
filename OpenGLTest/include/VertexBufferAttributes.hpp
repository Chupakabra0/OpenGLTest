#pragma once
#include "Utils.hpp"

#include <vector>

enum class VertexBufferAttributesType : int {
    NONE          = 0,
    POSITION      = 1,
    COLOR         = 2,
    VERTEX_NORMAL = 4,
    FACE_NORMAL   = 8,
    TEXT_COORD    = 16
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
