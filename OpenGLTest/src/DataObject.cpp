#include "DataObject.hpp"

BindableDataObject::BindableDataObject() = default;

BindableDataObject::BindableDataObject(BindableDataObject&&) noexcept = default;

BindableDataObject::~BindableDataObject() = default;

BindableDataObject& BindableDataObject::operator=(BindableDataObject&&) noexcept = default;

unsigned BindableDataObject::GetIndexId() const {
    return this->id_;
}

bool BindableDataObject::IsBinded() const {
    return this->isBinded_;
}

void BindableDataObject::Bind() {
    this->isBinded_ = true;
}

void BindableDataObject::Unbind() {
    this->isBinded_ = false;
}
