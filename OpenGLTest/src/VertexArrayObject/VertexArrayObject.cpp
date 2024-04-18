#include "VertexArrayObject/VertexArrayObject.hpp"

VertexArrayObject::VertexArrayObject(IndexBufferObject* ibo)
    : ibo_(ibo) {
    this->ConstructHelper_();
}

VertexArrayObject::VertexArrayObject(VertexArrayObject&& move) noexcept = default;

VertexArrayObject& VertexArrayObject::operator=(VertexArrayObject&&) noexcept = default;

VertexArrayObject::~VertexArrayObject() noexcept {
    this->DestroyHelper_();
}

void VertexArrayObject::Bind() {
    if (this->isBinded_) {
        return;
    }

    glBindVertexArray(this->id_);

    if (this->ibo_ != nullptr) {
        this->ibo_->Bind();
    }
    BindableDataObject::Bind();
}

void VertexArrayObject::Unbind() {
    if (!this->isBinded_) {
        return;
    }

    glBindVertexArray(0u);

    if (this->ibo_ != nullptr) {
        this->ibo_->Unbind();
    }
    BindableDataObject::Unbind();
}

const IndexBufferObject* VertexArrayObject::GetIBO() const {
    return this->ibo_.get();
}

void VertexArrayObject::SetIBO(IndexBufferObject* ibo) {
    this->ibo_ = std::unique_ptr<IndexBufferObject>(ibo);
}

void VertexArrayObject::ConstructHelper_() {
    glGenVertexArrays(1, &this->id_);
}

void VertexArrayObject::DestroyHelper_() const noexcept {
    glDeleteVertexArrays(1, &this->id_);
}
