#include "ArgParseBuilder/EllipseMeshParseBuilder/EllipseMeshParseBuilder.hpp"
#include "ArgParseWrapper/ArgParseWrapper.hpp"

const char* EllipseMeshParseBuilder::PARSE_NAME = ArgParseWrapper::ELLIPSE_COMMAND;
const char* EllipseMeshParseBuilder::PARSE_DESC = "Generate ellipse mesh";

EllipseMeshParseBuilder::EllipseMeshParseBuilder()
    : BaseMeshParseBuilder(EllipseMeshParseBuilder::PARSE_NAME) {

}

std::unique_ptr<argparse::ArgumentParser> EllipseMeshParseBuilder::GetUniqueProduct() {
    this->AddDesc_(EllipseMeshParseBuilder::PARSE_DESC);

    this->AddOriginArgument_();
    this->AddColorArgument_();
    this->AddAArgument_();
    this->AddBArgument_();
    this->AddSegmentsArgument_();

    return this->GetResultHelper_();
}

void EllipseMeshParseBuilder::AddAArgument_() {
    this->argumentParser_->add_argument(ArgParseWrapper::SHORT_A_PARAMETER_ARGUMENT, ArgParseWrapper::LONG_A_PARAMETER_ARGUMENT)
        .help("A parameter of the mesh").nargs(1).scan<'f', float>().required();
}

void EllipseMeshParseBuilder::AddBArgument_() {
    this->argumentParser_->add_argument(ArgParseWrapper::SHORT_B_PARAMETER_ARGUMENT, ArgParseWrapper::LONG_B_PARAMETER_ARGUMENT)
        .help("B parameter of the mesh").nargs(1).scan<'f', float>().required();
}
