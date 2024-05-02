#pragma once
#include "ArgParseBuilder/BaseMeshParserBuilder/BaseMeshParseBuilder.hpp"

class RectangleMeshParseBuilder : public BaseMeshParseBuilder {
private:
    static const char* PARSE_NAME;
    static const char* PARSE_DESC;

public:
    explicit RectangleMeshParseBuilder();

    RectangleMeshParseBuilder(const RectangleMeshParseBuilder&) = delete;

    RectangleMeshParseBuilder(RectangleMeshParseBuilder&&) noexcept = default;

    RectangleMeshParseBuilder& operator=(const RectangleMeshParseBuilder&) = delete;

    RectangleMeshParseBuilder& operator=(RectangleMeshParseBuilder&&) noexcept = default;

    ~RectangleMeshParseBuilder() override = default;

    std::unique_ptr<argparse::ArgumentParser> GetUniqueProduct() override;
};
