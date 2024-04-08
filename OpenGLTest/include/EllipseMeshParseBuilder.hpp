#pragma once
#include "BaseMeshParseBuilder.hpp"

class EllipseMeshParseBuilder : public BaseMeshParseBuilder {
private:
    static constexpr const char* PARSE_NAME = ArgParseWrapper::ELLIPSE_COMMAND;
    static constexpr const char* PARSE_DESC = "Generate ellipse mesh";

public:
    explicit EllipseMeshParseBuilder()
        : BaseMeshParseBuilder(EllipseMeshParseBuilder::PARSE_NAME) {

    }

    EllipseMeshParseBuilder(const EllipseMeshParseBuilder&) = delete;

    EllipseMeshParseBuilder(EllipseMeshParseBuilder&&) noexcept = default;

    EllipseMeshParseBuilder& operator=(const EllipseMeshParseBuilder&) = delete;

    EllipseMeshParseBuilder& operator=(EllipseMeshParseBuilder&&) noexcept = default;

    ~EllipseMeshParseBuilder() override = default;

    std::unique_ptr<argparse::ArgumentParser> GetUniqueProduct() override {
        this->AddDesc_(EllipseMeshParseBuilder::PARSE_DESC);

        this->AddOriginArgument_();
        this->AddColorArgument_();
        this->AddAArgument_();
        this->AddBArgument_();
        this->AddSegmentsArgument_();

        return this->GetResultHelper_();
    }

private:
    void AddAArgument_() {
        this->argumentParser_->add_argument(ArgParseWrapper::SHORT_A_PARAMETER_ARGUMENT, ArgParseWrapper::LONG_A_PARAMETER_ARGUMENT)
            .help("A parameter of the mesh").nargs(1).scan<'f', float>().required();
    }

    void AddBArgument_() {
        this->argumentParser_->add_argument(ArgParseWrapper::SHORT_B_PARAMETER_ARGUMENT, ArgParseWrapper::LONG_B_PARAMETER_ARGUMENT)
            .help("B parameter of the mesh").nargs(1).scan<'f', float>().required();
    }
};
