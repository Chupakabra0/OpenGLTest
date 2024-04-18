#pragma once
#include "ArgParseBuilder/BaseMeshParserBuilder/BaseMeshParseBuilder.hpp"

class IcosahedronMeshParseBuilder : public BaseMeshParseBuilder {
private:
    static const char* PARSE_NAME;
    static const char* PARSE_DESC;

public:
    explicit IcosahedronMeshParseBuilder();

    IcosahedronMeshParseBuilder(const IcosahedronMeshParseBuilder&) = delete;

    IcosahedronMeshParseBuilder(IcosahedronMeshParseBuilder&&) noexcept = default;

    IcosahedronMeshParseBuilder& operator=(const IcosahedronMeshParseBuilder&) = delete;

    IcosahedronMeshParseBuilder& operator=(IcosahedronMeshParseBuilder&&) noexcept = default;

    ~IcosahedronMeshParseBuilder() override = default;

    std::unique_ptr<argparse::ArgumentParser> GetUniqueProduct() override;
};
