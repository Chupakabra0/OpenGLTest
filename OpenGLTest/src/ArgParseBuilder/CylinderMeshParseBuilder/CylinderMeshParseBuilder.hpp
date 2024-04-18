#pragma once
#include "ArgParseBuilder/BaseMeshParserBuilder/BaseMeshParseBuilder.hpp"
#include "ArgParseWrapper/ArgParseWrapper.hpp"

class CylinderMeshParseBuilder : public BaseMeshParseBuilder {
private:
    static const char* PARSE_NAME;
    static const char* PARSE_DESC;

public:
    explicit CylinderMeshParseBuilder();

    CylinderMeshParseBuilder(const CylinderMeshParseBuilder&) = delete;

    CylinderMeshParseBuilder(CylinderMeshParseBuilder&&) noexcept = default;

    CylinderMeshParseBuilder& operator=(const CylinderMeshParseBuilder&) = delete;

    CylinderMeshParseBuilder& operator=(CylinderMeshParseBuilder&&) noexcept = default;

    ~CylinderMeshParseBuilder() override = default;

    std::unique_ptr<argparse::ArgumentParser> GetUniqueProduct() override;
};
