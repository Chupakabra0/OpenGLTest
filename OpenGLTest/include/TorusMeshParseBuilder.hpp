#pragma once
#include "BaseMeshParseBuilder.hpp"

class TorusMeshParseBuilder : public BaseMeshParseBuilder {
private:
    static constexpr const char* PARSE_NAME = ArgParseWrapper::TORUS_COMMAND;
    static constexpr const char* PARSE_DESC = "Generate torus mesh";

public:
    explicit TorusMeshParseBuilder()
        : BaseMeshParseBuilder(TorusMeshParseBuilder::PARSE_NAME) {

    }

    TorusMeshParseBuilder(const TorusMeshParseBuilder&) = delete;

    TorusMeshParseBuilder(TorusMeshParseBuilder&&) noexcept = default;

    TorusMeshParseBuilder& operator=(const TorusMeshParseBuilder&) = delete;

    TorusMeshParseBuilder& operator=(TorusMeshParseBuilder&&) noexcept = default;

    ~TorusMeshParseBuilder() override = default;

    std::unique_ptr<argparse::ArgumentParser> GetUniqueProduct() override {
        this->AddDesc_(TorusMeshParseBuilder::PARSE_DESC);

        this->AddOriginArgument_();
        this->AddColorArgument_();
        this->AddInnerRadiusArgument_();
        this->AddOuterRadiusArgument_();
        this->AddSlicesArgument_();
        this->AddSegmentsArgument_();

        return this->GetResultHelper_();
    }

private:
    void AddInnerRadiusArgument_() {
        this->argumentParser_->add_argument(ArgParseWrapper::SHORT_INNER_RADIUS_ARGUMENT, ArgParseWrapper::LONG_INNER_RADIUS_ARGUMENT)
            .help("Inner radius of the mesh").nargs(1).scan<'f', float>().required();
    }

    void AddOuterRadiusArgument_() {
        this->argumentParser_->add_argument(ArgParseWrapper::SHORT_OUTER_RADIUS_ARGUMENT, ArgParseWrapper::LONG_OUTER_RADIUS_ARGUMENT)
            .help("Outer radius of the mesh").nargs(1).scan<'f', float>().required();
    }
};