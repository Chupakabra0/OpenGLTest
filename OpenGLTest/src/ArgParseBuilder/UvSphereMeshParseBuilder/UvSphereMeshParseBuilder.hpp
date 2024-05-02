#pragma once
#include "ArgParseBuilder/BaseMeshParserBuilder/BaseMeshParseBuilder.hpp"

class UvSphereMeshParseBuilder : public BaseMeshParseBuilder {
private:
    static const char* PARSE_NAME;
    static const char* PARSE_DESC;

public:
    explicit UvSphereMeshParseBuilder();

    UvSphereMeshParseBuilder(const UvSphereMeshParseBuilder&) = delete;

    UvSphereMeshParseBuilder(UvSphereMeshParseBuilder&&) noexcept = default;

    UvSphereMeshParseBuilder& operator=(const UvSphereMeshParseBuilder&) = delete;

    UvSphereMeshParseBuilder& operator=(UvSphereMeshParseBuilder&&) noexcept = default;

    ~UvSphereMeshParseBuilder() override = default;

    std::unique_ptr<argparse::ArgumentParser> GetUniqueProduct() override;
};
