#pragma once
#include "BaseMeshParseBuilder.hpp"

class ParallelepipedMeshParseBuilder : public BaseMeshParseBuilder {
private:
    static constexpr const char* PARSE_NAME = ArgParseWrapper::PARALLELEPIPED_COMMAND;
    static constexpr const char* PARSE_DESC = "Generate parallelepiped mesh";

public:
    explicit ParallelepipedMeshParseBuilder()
        : BaseMeshParseBuilder(ParallelepipedMeshParseBuilder::PARSE_NAME) {

    }

    ParallelepipedMeshParseBuilder(const ParallelepipedMeshParseBuilder&) = delete;

    ParallelepipedMeshParseBuilder(ParallelepipedMeshParseBuilder&&) noexcept = default;

    ParallelepipedMeshParseBuilder& operator=(const ParallelepipedMeshParseBuilder&) = delete;

    ParallelepipedMeshParseBuilder& operator=(ParallelepipedMeshParseBuilder&&) noexcept = default;

    ~ParallelepipedMeshParseBuilder() override = default;

    std::unique_ptr<argparse::ArgumentParser> GetUniqueProduct() override {
        this->AddDesc_(ParallelepipedMeshParseBuilder::PARSE_DESC);

        this->AddOriginArgument_();
        this->AddColorArgument_();
        this->AddHeightArgument_();
        this->AddWidthArgument_();
        this->AddDepthArgument_();

        return this->GetResultHelper_();
    }
};
