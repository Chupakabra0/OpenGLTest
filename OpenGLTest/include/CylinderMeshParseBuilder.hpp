#pragma once
#include "BaseMeshParseBuilder.hpp"

class CylinderMeshParseBuilder : public BaseMeshParseBuilder {
private:
    static constexpr const char* PARSE_NAME = ArgParseWrapper::CYLINDER_COMMAND;
    static constexpr const char* PARSE_DESC = "Generate cylinder mesh";

public:
    explicit CylinderMeshParseBuilder()
        : BaseMeshParseBuilder(CylinderMeshParseBuilder::PARSE_NAME) {

    }

    CylinderMeshParseBuilder(const CylinderMeshParseBuilder&) = delete;

    CylinderMeshParseBuilder(CylinderMeshParseBuilder&&) noexcept = default;

    CylinderMeshParseBuilder& operator=(const CylinderMeshParseBuilder&) = delete;

    CylinderMeshParseBuilder& operator=(CylinderMeshParseBuilder&&) noexcept = default;

    ~CylinderMeshParseBuilder() override = default;

    std::unique_ptr<argparse::ArgumentParser> GetUniqueProduct() override {
        this->AddDesc_(CylinderMeshParseBuilder::PARSE_DESC);

        this->AddOriginArgument_();
        this->AddColorArgument_();
        this->AddHeightArgument_();
        this->AddRadiusArgument_();
        this->AddSegmentsArgument_();
        this->AddSlicesArgument_();

        return this->GetResultHelper_();
    }
};