#pragma once
#include "glad/glad.h"

#include "IndexBufferObject.hpp"
#include "VertexBufferObject.hpp"
#include "DataObjectGuard.hpp"

#include <memory>
#include <vector>
#include <format>

class VertexArrayObject : public BindableDataObject {
public:
    VertexArrayObject() = delete;

    explicit VertexArrayObject(IndexBufferObject* ibo);

    VertexArrayObject(const VertexArrayObject&) = delete;

    VertexArrayObject(VertexArrayObject&& move) noexcept;

    VertexArrayObject& operator=(const VertexArrayObject&) = delete;

    VertexArrayObject& operator=(VertexArrayObject&&) noexcept;

    ~VertexArrayObject() noexcept;

    void Bind() override;

    void Unbind() override;

    template<class Vec>
    void AddBuffer(const Vec& data, const VertexBufferAttributes& attr) {
        VertexBufferObject vbo{data};
        DataObjectGuard guard{*this};

        const auto& elements{attr.GetElements()};
        long long offset{};
        for (int i = 0; i < elements.size(); ++i) {
            const auto& el = elements[i];
            vbo.AddAttributePointer(this->attrId_, el.vertexDataCount, el.valueType, attr.GetStride(), offset, el.normalized);
            vbo.EnableAttribute(this->attrId_++);
            
            this->vertexBufferAttributes_.push_back(attr);
            offset += static_cast<long long>(el.vertexDataCount) * GetSizeOfType(el.valueType);
        }
    }

    const IndexBufferObject* GetIBO() const;

    void SetIBO(IndexBufferObject* ibo);

    const VertexBufferAttributesElement& GetAttributeElement(VertexBufferAttributesType vbType) {
        for (const auto& val : this->vertexBufferAttributes_) {
            for (const auto& el : val.GetElements()) {
                if (el.vbType == vbType) {
                    return el;
                }
            }
        }

        throw std::runtime_error(std::format("Error: vertex buffer with type {} not found\n", static_cast<int>(vbType)));
    }

private:
    int attrId_{};
    std::unique_ptr<IndexBufferObject> ibo_;
    std::vector<VertexBufferAttributes> vertexBufferAttributes_;

    void ConstructHelper_();

    void DestroyHelper_() const noexcept;
};
