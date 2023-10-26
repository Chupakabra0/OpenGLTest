#include "DataObjectGuard.hpp"

DataObjectGuard::DataObjectGuard(BindableDataObject& dataObject)
    : isBindedIn_(dataObject.IsBinded()), dataObject_(dataObject) {
    this->ConstructHelper_();
}

DataObjectGuard::~DataObjectGuard() {
    this->DestroyHelper_();
}

void DataObjectGuard::ConstructHelper_() {
    if (this->isBindedIn_) {
        return;
    }

    this->dataObject_.get().Bind();
}

void DataObjectGuard::DestroyHelper_() noexcept {
    if (isBindedIn_) {
        return;
    }

    this->dataObject_.get().Unbind();
}
