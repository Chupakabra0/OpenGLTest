#pragma once
#include "BaseMeshParseBuilder.hpp"

class IcosahedronMeshParseBuilder : public BaseMeshParseBuilder {
private:
    static constexpr const char* PARSE_NAME = ArgParseWrapper::ICOSAHEDRON_COMMAND;
    static constexpr const char* PARSE_DESC = "Generate icosahedron mesh";

public:
    explicit IcosahedronMeshParseBuilder()
        : BaseMeshParseBuilder(IcosahedronMeshParseBuilder::PARSE_NAME) {

    }

    IcosahedronMeshParseBuilder(const IcosahedronMeshParseBuilder&) = delete;

    IcosahedronMeshParseBuilder(IcosahedronMeshParseBuilder&&) noexcept = default;

    IcosahedronMeshParseBuilder& operator=(const IcosahedronMeshParseBuilder&) = delete;

    IcosahedronMeshParseBuilder& operator=(IcosahedronMeshParseBuilder&&) noexcept = default;

    ~IcosahedronMeshParseBuilder() override = default;

    std::unique_ptr<argparse::ArgumentParser> GetUniqueProduct() override {
        this->AddDesc_(IcosahedronMeshParseBuilder::PARSE_DESC);

        this->AddOriginArgument_();
        this->AddColorArgument_();
        this->AddRadiusArgument_();

        return this->GetResultHelper_();
    }
};
