#pragma once
#include "BaseMeshParseBuilder.hpp"

class CircleMeshParseBuilder : public BaseMeshParseBuilder {
private:
    static constexpr const char* PARSE_NAME = ArgParseWrapper::CIRCLE_COMMAND;
    static constexpr const char* PARSE_DESC = "Generate circle mesh";

public:
    explicit CircleMeshParseBuilder()
        : BaseMeshParseBuilder(CircleMeshParseBuilder::PARSE_NAME) {

    }

    CircleMeshParseBuilder(const CircleMeshParseBuilder&) = delete;

    CircleMeshParseBuilder(CircleMeshParseBuilder&&) noexcept = default;

    CircleMeshParseBuilder& operator=(const CircleMeshParseBuilder&) = delete;

    CircleMeshParseBuilder& operator=(CircleMeshParseBuilder&&) noexcept = default;

    ~CircleMeshParseBuilder() override = default;

    std::unique_ptr<argparse::ArgumentParser> GetUniqueProduct() override {
        this->AddDesc_(CircleMeshParseBuilder::PARSE_DESC);

        this->AddOriginArgument_();
        this->AddColorArgument_();
        this->AddRadiusArgument_();
        this->AddSegmentsArgument_();

        return this->GetResultHelper_();
    }
};