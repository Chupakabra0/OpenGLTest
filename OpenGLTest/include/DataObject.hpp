#pragma once

class BindableDataObject {
public:
    explicit BindableDataObject();

    BindableDataObject(const BindableDataObject&) = delete;

    BindableDataObject(BindableDataObject&&) noexcept;

    BindableDataObject& operator=(const BindableDataObject&) = delete;

    BindableDataObject& operator=(BindableDataObject&&) noexcept;

    virtual ~BindableDataObject() = 0;

    unsigned GetIndexId() const;

    bool IsBinded() const;

    virtual void Bind();

    virtual void Unbind();

protected:
    bool isBinded_{};
    unsigned id_{};
};
