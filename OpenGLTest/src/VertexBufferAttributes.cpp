#include "VertexBufferAttributes.hpp"

VertexBufferAttributes::VertexBufferAttributes(unsigned vertexDataCount, unsigned totalDataCount, ValueType type,
    Normalize normalized, VertexBufferAttributesType vbType) {
    this->Add(vertexDataCount, totalDataCount, type, normalized, vbType);
}

VertexBufferAttributes::VertexBufferAttributes(const VertexBufferAttributes&) = default;

VertexBufferAttributes::VertexBufferAttributes(VertexBufferAttributes&&) noexcept = default;

VertexBufferAttributes& VertexBufferAttributes::operator=(const VertexBufferAttributes&) = default;

VertexBufferAttributes& VertexBufferAttributes::operator=(VertexBufferAttributes&&) noexcept = default;

VertexBufferAttributes::~VertexBufferAttributes() = default;

const std::vector<VertexBufferAttributesElement>& VertexBufferAttributes::GetElements() const {
    return this->elements_;
}

int VertexBufferAttributes::GetStride() const {
    return this->stride_;
}

void VertexBufferAttributes::Add(unsigned vertexDataCount, unsigned totalDataCount, ValueType type, Normalize normalized, VertexBufferAttributesType vbType) {
    this->elements_.emplace_back(
        VertexBufferAttributesElement{
            .vertexDataCount = vertexDataCount,
            .totalDataCount  = totalDataCount,
            .valueType       = type,
            .normalized      = normalized,
            .vbType          = vbType
        }
    );

    this->stride_ += GetSizeOfType(type) * vertexDataCount;
}
