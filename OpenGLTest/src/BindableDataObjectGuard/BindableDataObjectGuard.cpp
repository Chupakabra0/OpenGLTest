#include "BindableDataObjectGuard/BindableDataObjectGuard.hpp"

BindableDataObjectGuard::BindableDataObjectGuard(BindableDataObject& dataObject)
    : isBindedIn_(dataObject.IsBinded()), dataObject_(dataObject) {
    this->ConstructHelper_();
}

BindableDataObjectGuard::~BindableDataObjectGuard() {
    this->DestroyHelper_();
}

void BindableDataObjectGuard::ConstructHelper_() {
    if (this->isBindedIn_) {
        return;
    }

    this->dataObject_.get().Bind();
}

void BindableDataObjectGuard::DestroyHelper_() noexcept {
    if (isBindedIn_) {
        return;
    }

    this->dataObject_.get().Unbind();
}
