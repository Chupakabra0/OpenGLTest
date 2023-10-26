#include "VertexBufferObject.hpp"
#include "DataObjectGuard.hpp"

VertexBufferObject::VertexBufferObject(const void* data, unsigned size) {
    this->ConstructHelper_(data, size);
}

VertexBufferObject::VertexBufferObject(VertexBufferObject&&) noexcept = default;

VertexBufferObject& VertexBufferObject::operator=(VertexBufferObject&&) noexcept = default;

VertexBufferObject::~VertexBufferObject() noexcept {
    this->DestroyHelper_();
}

void VertexBufferObject::Bind() {
    if (this->isBinded_) {
        return;
    }

    glBindBuffer(GL_ARRAY_BUFFER, this->id_);

    BindableDataObject::Bind();
}

void VertexBufferObject::Unbind() {
    if (!this->isBinded_) {
        return;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0u);

    BindableDataObject::Unbind();
}

void VertexBufferObject::AddAttributePointer(unsigned location, unsigned vertexSize, ValueType type, int stride, long long offset,
    Normalize normalize) {
    DataObjectGuard guard{*this};
    glVertexAttribPointer(location, vertexSize, static_cast<int>(type), static_cast<bool>(normalize), stride, reinterpret_cast<void*>(offset));
}

void VertexBufferObject::EnableAttribute(unsigned location) const {
    glEnableVertexAttribArray(location);
}

void VertexBufferObject::DisableAttribute(unsigned location) const {
    glDisableVertexAttribArray(location);
}

void VertexBufferObject::ConstructHelper_(const void* data, unsigned size) {
    glGenBuffers(1, &this->id_);
    DataObjectGuard guard{*this};
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBufferObject::DestroyHelper_() noexcept {
    glDeleteBuffers(1, &this->id_);
}