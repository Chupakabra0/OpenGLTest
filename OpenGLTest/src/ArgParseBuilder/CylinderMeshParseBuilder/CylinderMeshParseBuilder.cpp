#include "ArgParseBuilder/CylinderMeshParseBuilder/CylinderMeshParseBuilder.hpp"
#include "ArgParseWrapper/ArgParseWrapper.hpp"

const char* CylinderMeshParseBuilder::PARSE_NAME = ArgParseWrapper::CYLINDER_COMMAND;
const char* CylinderMeshParseBuilder::PARSE_DESC = "Generate cylinder mesh";

CylinderMeshParseBuilder::CylinderMeshParseBuilder()
    : BaseMeshParseBuilder(CylinderMeshParseBuilder::PARSE_NAME) {

}

std::unique_ptr<argparse::ArgumentParser> CylinderMeshParseBuilder::GetUniqueProduct() {
    this->AddDesc_(CylinderMeshParseBuilder::PARSE_DESC);

    this->AddOriginArgument_();
    this->AddColorArgument_();
    this->AddHeightArgument_();
    this->AddRadiusArgument_();
    this->AddSegmentsArgument_();
    this->AddSlicesArgument_();

    return this->GetResultHelper_();
}
