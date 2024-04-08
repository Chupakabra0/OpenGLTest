#pragma once
#include "BaseMeshParseBuilder.hpp"

class UvSphereMeshParseBuilder : public BaseMeshParseBuilder {
private:
    static constexpr const char* PARSE_NAME = ArgParseWrapper::UV_SPHERE_COMMAND;
    static constexpr const char* PARSE_DESC = "Generate uv-sphere mesh";

public:
    explicit UvSphereMeshParseBuilder()
        : BaseMeshParseBuilder(UvSphereMeshParseBuilder::PARSE_NAME) {

    }

    UvSphereMeshParseBuilder(const UvSphereMeshParseBuilder&) = delete;

    UvSphereMeshParseBuilder(UvSphereMeshParseBuilder&&) noexcept = default;

    UvSphereMeshParseBuilder& operator=(const UvSphereMeshParseBuilder&) = delete;

    UvSphereMeshParseBuilder& operator=(UvSphereMeshParseBuilder&&) noexcept = default;

    ~UvSphereMeshParseBuilder() override = default;

    std::unique_ptr<argparse::ArgumentParser> GetUniqueProduct() override {
        this->AddDesc_(UvSphereMeshParseBuilder::PARSE_DESC);

        this->AddOriginArgument_();
        this->AddColorArgument_();
        this->AddRadiusArgument_();
        this->AddSlicesArgument_();
        this->AddSegmentsArgument_();

        return this->GetResultHelper_();
    }
};
