#pragma once
#include "DataObject.hpp"

#include <memory>

class DataObjectGuard {
public:
    DataObjectGuard() = delete;

    explicit DataObjectGuard(BindableDataObject& dataObject);

    DataObjectGuard(const DataObjectGuard&) = delete;

    DataObjectGuard(DataObjectGuard&&) = delete;

    DataObjectGuard& operator=(const DataObjectGuard&) = delete;

    DataObjectGuard& operator=(DataObjectGuard&&) = delete;

    ~DataObjectGuard();

private:
    bool isBindedIn_{};
    std::reference_wrapper<BindableDataObject> dataObject_;

    void ConstructHelper_();

    void DestroyHelper_() noexcept;
};
