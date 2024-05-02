#include "ArgParseBuilder/CircleMeshParseBuilder/CircleMeshParseBuilder.hpp"
#include "ArgParseWrapper/ArgParseWrapper.hpp"

const char* CircleMeshParseBuilder::PARSE_NAME = ArgParseWrapper::CIRCLE_COMMAND;
const char* CircleMeshParseBuilder::PARSE_DESC = "Generate circle mesh";

CircleMeshParseBuilder::CircleMeshParseBuilder()
    : BaseMeshParseBuilder(CircleMeshParseBuilder::PARSE_NAME) {

}

std::unique_ptr<argparse::ArgumentParser> CircleMeshParseBuilder::GetUniqueProduct() {
    this->AddDesc_(CircleMeshParseBuilder::PARSE_DESC);

    this->AddOriginArgument_();
    this->AddColorArgument_();
    this->AddRadiusArgument_();
    this->AddSegmentsArgument_();

    return this->GetResultHelper_();
}
