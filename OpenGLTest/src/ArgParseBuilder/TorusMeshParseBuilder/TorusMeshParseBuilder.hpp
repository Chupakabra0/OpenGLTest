#pragma once
#include "ArgParseBuilder/BaseMeshParserBuilder/BaseMeshParseBuilder.hpp"

class TorusMeshParseBuilder : public BaseMeshParseBuilder {
private:
    static const char* PARSE_NAME;
    static const char* PARSE_DESC;

public:
    explicit TorusMeshParseBuilder();

    TorusMeshParseBuilder(const TorusMeshParseBuilder&) = delete;

    TorusMeshParseBuilder(TorusMeshParseBuilder&&) noexcept = default;

    TorusMeshParseBuilder& operator=(const TorusMeshParseBuilder&) = delete;

    TorusMeshParseBuilder& operator=(TorusMeshParseBuilder&&) noexcept = default;

    ~TorusMeshParseBuilder() override = default;

    std::unique_ptr<argparse::ArgumentParser> GetUniqueProduct() override;

private:
    void AddInnerRadiusArgument_();

    void AddOuterRadiusArgument_();
};
