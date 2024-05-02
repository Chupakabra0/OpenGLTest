#pragma once
#include "ArgParseBuilder/BaseMeshParserBuilder/BaseMeshParseBuilder.hpp"

class IcosphereMeshParseBuilder : public BaseMeshParseBuilder {
private:
    static const char* PARSE_NAME;
    static const char* PARSE_DESC;

public:
    explicit IcosphereMeshParseBuilder();

    IcosphereMeshParseBuilder(const IcosphereMeshParseBuilder&) = delete;

    IcosphereMeshParseBuilder(IcosphereMeshParseBuilder&&) noexcept = default;

    IcosphereMeshParseBuilder& operator=(const IcosphereMeshParseBuilder&) = delete;

    IcosphereMeshParseBuilder& operator=(IcosphereMeshParseBuilder&&) noexcept = default;

    ~IcosphereMeshParseBuilder() override = default;

    std::unique_ptr<argparse::ArgumentParser> GetUniqueProduct() override;

private:
    void AddIterationsArgument_();
};
