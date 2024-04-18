#pragma once
#include "BindableDataObject/BindableDataObject.hpp"
#include "Utils/Utils.hpp"

class VertexBufferObject : public BindableDataObject {
public:
    VertexBufferObject() = delete;

    explicit VertexBufferObject(const void* data, unsigned size);

    template<class Vec>
    explicit VertexBufferObject(const Vec& vec) {
        this->ConstructHelper_(vec.data(), static_cast<unsigned>(vec.size() * sizeof(Vec::value_type)));
    }

    VertexBufferObject(const VertexBufferObject&) = delete;

    VertexBufferObject(VertexBufferObject&&) noexcept;

    VertexBufferObject& operator=(const VertexBufferObject&) = delete;

    VertexBufferObject& operator=(VertexBufferObject&&) noexcept;

    ~VertexBufferObject() noexcept override;

    void Bind() override;

    void Unbind() override;

    void AddAttributePointer(unsigned location, unsigned vertexSize, ValueType type, int stride, long long offset,
        Normalize normalize);

    void EnableAttribute(unsigned location) const;

    void DisableAttribute(unsigned location) const;

private:
    void ConstructHelper_(const void* data, unsigned size);

    void DestroyHelper_() noexcept;
};
