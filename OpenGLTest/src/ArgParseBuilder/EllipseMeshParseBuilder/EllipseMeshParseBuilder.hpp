#pragma once
#include "ArgParseBuilder/BaseMeshParserBuilder/BaseMeshParseBuilder.hpp"

class EllipseMeshParseBuilder : public BaseMeshParseBuilder {
private:
    static const char* PARSE_NAME;
    static const char* PARSE_DESC;

public:
    explicit EllipseMeshParseBuilder();

    EllipseMeshParseBuilder(const EllipseMeshParseBuilder&) = delete;

    EllipseMeshParseBuilder(EllipseMeshParseBuilder&&) noexcept = default;

    EllipseMeshParseBuilder& operator=(const EllipseMeshParseBuilder&) = delete;

    EllipseMeshParseBuilder& operator=(EllipseMeshParseBuilder&&) noexcept = default;

    ~EllipseMeshParseBuilder() override = default;

    std::unique_ptr<argparse::ArgumentParser> GetUniqueProduct() override;

private:
    void AddAArgument_();

    void AddBArgument_();
};
