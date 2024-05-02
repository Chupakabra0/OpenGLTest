#pragma once
#include <memory>

#include "BindableDataObject/BindableDataObject.hpp"

class BindableDataObjectGuard {
public:
    BindableDataObjectGuard() = delete;

    explicit BindableDataObjectGuard(BindableDataObject& dataObject);

    BindableDataObjectGuard(const BindableDataObjectGuard&) = delete;

    BindableDataObjectGuard(BindableDataObjectGuard&&) = delete;

    BindableDataObjectGuard& operator=(const BindableDataObjectGuard&) = delete;

    BindableDataObjectGuard& operator=(BindableDataObjectGuard&&) = delete;

    ~BindableDataObjectGuard();

private:
    bool isBindedIn_{};
    std::reference_wrapper<BindableDataObject> dataObject_;

    void ConstructHelper_();

    void DestroyHelper_() noexcept;
};
