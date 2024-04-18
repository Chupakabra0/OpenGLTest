#include "ArgParseBuilder/UvSphereMeshParseBuilder/UvSphereMeshParseBuilder.hpp"
#include "ArgParseWrapper/ArgParseWrapper.hpp"

const char* UvSphereMeshParseBuilder::PARSE_NAME = ArgParseWrapper::UV_SPHERE_COMMAND;
const char* UvSphereMeshParseBuilder::PARSE_DESC = "Generate uv-sphere mesh";

UvSphereMeshParseBuilder::UvSphereMeshParseBuilder()
    : BaseMeshParseBuilder(UvSphereMeshParseBuilder::PARSE_NAME) {

}

std::unique_ptr<argparse::ArgumentParser> UvSphereMeshParseBuilder::GetUniqueProduct() {
    this->AddDesc_(UvSphereMeshParseBuilder::PARSE_DESC);

    this->AddOriginArgument_();
    this->AddColorArgument_();
    this->AddRadiusArgument_();
    this->AddSlicesArgument_();
    this->AddSegmentsArgument_();

    return this->GetResultHelper_();
}
