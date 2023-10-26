#include "IndexBufferObject.hpp"

IndexBufferObject::IndexBufferObject(const void* data, unsigned count)
    : indexType_(ValueType::UINT), count_(count) {
    this->ConstructHelper_(data, this->count_ * sizeof(unsigned));
}

IndexBufferObject::IndexBufferObject(IndexBufferObject&& move) noexcept = default;

IndexBufferObject& IndexBufferObject::operator=(IndexBufferObject&&) noexcept = default;

IndexBufferObject::~IndexBufferObject() noexcept {
    this->DestroyHelper_();
}

void IndexBufferObject::Bind() {
    if (this->isBinded_) {
        return;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id_);

    BindableDataObject::Bind();
}

void IndexBufferObject::Unbind() {
    if (!this->isBinded_) {
        return;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);

    BindableDataObject::Unbind();
}

unsigned IndexBufferObject::GetIndexCount() const {
    return this->count_;
}

ValueType IndexBufferObject::GetIndexType() const {
    return this->indexType_;
}

void IndexBufferObject::ConstructHelper_(const void* data, unsigned size) {
    glGenBuffers(1, &this->id_);

    this->Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    this->Unbind();
}

void IndexBufferObject::DestroyHelper_() const noexcept {
    glDeleteBuffers(1, &this->id_);
}