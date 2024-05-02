#pragma once
#include "ArgParseBuilder/BaseMeshParserBuilder/BaseMeshParseBuilder.hpp"

class ParallelepipedMeshParseBuilder : public BaseMeshParseBuilder {
private:
    static const char* PARSE_NAME;
    static const char* PARSE_DESC;

public:
    explicit ParallelepipedMeshParseBuilder();

    ParallelepipedMeshParseBuilder(const ParallelepipedMeshParseBuilder&) = delete;

    ParallelepipedMeshParseBuilder(ParallelepipedMeshParseBuilder&&) noexcept = default;

    ParallelepipedMeshParseBuilder& operator=(const ParallelepipedMeshParseBuilder&) = delete;

    ParallelepipedMeshParseBuilder& operator=(ParallelepipedMeshParseBuilder&&) noexcept = default;

    ~ParallelepipedMeshParseBuilder() override = default;

    std::unique_ptr<argparse::ArgumentParser> GetUniqueProduct() override;
};
