#pragma once
#include "BaseMeshParseBuilder.hpp"

class IcosphereMeshParseBuilder : public BaseMeshParseBuilder {
private:
    static constexpr const char* PARSE_NAME = ArgParseWrapper::ICOSPHERE_COMMAND;
    static constexpr const char* PARSE_DESC = "Generate icosphere mesh";

public:
    explicit IcosphereMeshParseBuilder()
        : BaseMeshParseBuilder(IcosphereMeshParseBuilder::PARSE_NAME) {

    }

    IcosphereMeshParseBuilder(const IcosphereMeshParseBuilder&) = delete;

    IcosphereMeshParseBuilder(IcosphereMeshParseBuilder&&) noexcept = default;

    IcosphereMeshParseBuilder& operator=(const IcosphereMeshParseBuilder&) = delete;

    IcosphereMeshParseBuilder& operator=(IcosphereMeshParseBuilder&&) noexcept = default;

    ~IcosphereMeshParseBuilder() override = default;

    std::unique_ptr<argparse::ArgumentParser> GetUniqueProduct() override {
        this->AddDesc_(IcosphereMeshParseBuilder::PARSE_DESC);

        this->AddOriginArgument_();
        this->AddColorArgument_();
        this->AddRadiusArgument_();
        this->AddIterationsArgument_();

        return this->GetResultHelper_();
    }

private:
    void AddIterationsArgument_() {
        this->argumentParser_->add_argument(ArgParseWrapper::SHORT_ITERATIONS_ARGUMENT, ArgParseWrapper::LONG_ITERATIONS_ARGUMENT)
            .help("Iterations of the mesh").nargs(1).scan<'i', int>().required();
    }
};