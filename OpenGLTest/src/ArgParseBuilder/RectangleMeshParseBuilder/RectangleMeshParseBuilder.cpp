#include "ArgParseBuilder/RectangleMeshParseBuilder/RectangleMeshParseBuilder.hpp"
#include "ArgParseWrapper/ArgParseWrapper.hpp"

const char* RectangleMeshParseBuilder::PARSE_NAME = ArgParseWrapper::RECTANGLE_COMMAND;
const char* RectangleMeshParseBuilder::PARSE_DESC = "Generate rectangle mesh";

RectangleMeshParseBuilder::RectangleMeshParseBuilder()
    : BaseMeshParseBuilder(RectangleMeshParseBuilder::PARSE_NAME) {

}

std::unique_ptr<argparse::ArgumentParser> RectangleMeshParseBuilder::GetUniqueProduct() {
    this->AddDesc_(RectangleMeshParseBuilder::PARSE_DESC);

    this->AddOriginArgument_();
    this->AddColorArgument_();
    this->AddHeightArgument_();
    this->AddWidthArgument_();

    return this->GetResultHelper_();
}
