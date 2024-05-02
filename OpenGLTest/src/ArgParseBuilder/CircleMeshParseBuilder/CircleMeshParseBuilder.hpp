#pragma once
#include "ArgParseBuilder/BaseMeshParserBuilder/BaseMeshParseBuilder.hpp"

class CircleMeshParseBuilder : public BaseMeshParseBuilder {
private:
    static const char* PARSE_NAME;
    static const char* PARSE_DESC;

public:
    explicit CircleMeshParseBuilder();

    CircleMeshParseBuilder(const CircleMeshParseBuilder&) = delete;

    CircleMeshParseBuilder(CircleMeshParseBuilder&&) noexcept = default;

    CircleMeshParseBuilder& operator=(const CircleMeshParseBuilder&) = delete;

    CircleMeshParseBuilder& operator=(CircleMeshParseBuilder&&) noexcept = default;

    ~CircleMeshParseBuilder() override = default;

    std::unique_ptr<argparse::ArgumentParser> GetUniqueProduct() override;
};


