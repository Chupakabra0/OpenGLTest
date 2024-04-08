#pragma once
#include "argparse/argparse.hpp"

class ArgParseBuilder {
public:
    ArgParseBuilder() = delete;

    explicit ArgParseBuilder(const std::string& name)
        : name_(name) {
        this->Reset();
    }

    ArgParseBuilder(const ArgParseBuilder&) = delete;

    ArgParseBuilder(ArgParseBuilder&&) noexcept = default;

    ArgParseBuilder& operator=(const ArgParseBuilder&) = delete;

    ArgParseBuilder& operator=(ArgParseBuilder&&) noexcept = default;

    virtual ~ArgParseBuilder() = default;

    virtual std::unique_ptr<argparse::ArgumentParser> GetUniqueProduct() = 0;

protected:
    std::unique_ptr<argparse::ArgumentParser> argumentParser_{};
    std::string name_{};

    void Reset() {
        std::make_unique<argparse::ArgumentParser>(this->name_).swap(this->argumentParser_);
    }

    std::unique_ptr<argparse::ArgumentParser> GetResultHelper_() {
        auto result = std::move(this->argumentParser_);
        this->Reset();

        return result;
    }
};
