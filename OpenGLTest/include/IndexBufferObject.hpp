#pragma once
#include "VertexBufferAttributes.hpp"
#include "DataObject.hpp"

#include "glad/glad.h"

class IndexBufferObject : public BindableDataObject {
public:
    IndexBufferObject() = delete;

    explicit IndexBufferObject(const void* data, unsigned count);

    template<class Vec>
    explicit IndexBufferObject(const Vec& vec)
        : indexType_(GetType<typename Vec::value_type>()), count_(static_cast<unsigned>(vec.size())) {
        this->ConstructHelper_(vec.data(), static_cast<unsigned>(this->count_ * sizeof(Vec::value_type)));
    }

    IndexBufferObject(const IndexBufferObject&) = delete;

    IndexBufferObject(IndexBufferObject&& move) noexcept;

    IndexBufferObject& operator=(const IndexBufferObject&) = delete;

    IndexBufferObject& operator=(IndexBufferObject&&) noexcept;

    ~IndexBufferObject() noexcept;

    void Bind() override;

    void Unbind() override;

    unsigned GetIndexCount() const;

    ValueType GetIndexType() const;

private:
    ValueType indexType_{};
    unsigned count_{};

    void ConstructHelper_(const void* data, unsigned size);

    void DestroyHelper_() const noexcept;
};
