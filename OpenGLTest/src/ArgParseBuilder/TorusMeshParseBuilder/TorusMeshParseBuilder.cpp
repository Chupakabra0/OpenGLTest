#include "ArgParseBuilder/TorusMeshParseBuilder/TorusMeshParseBuilder.hpp"
#include "ArgParseWrapper/ArgParseWrapper.hpp"

const char* TorusMeshParseBuilder::PARSE_NAME = ArgParseWrapper::TORUS_COMMAND;
const char* TorusMeshParseBuilder::PARSE_DESC = "Generate torus mesh";

TorusMeshParseBuilder::TorusMeshParseBuilder()
    : BaseMeshParseBuilder(TorusMeshParseBuilder::PARSE_NAME) {

}

std::unique_ptr<argparse::ArgumentParser> TorusMeshParseBuilder::GetUniqueProduct() {
    this->AddDesc_(TorusMeshParseBuilder::PARSE_DESC);

    this->AddOriginArgument_();
    this->AddColorArgument_();
    this->AddInnerRadiusArgument_();
    this->AddOuterRadiusArgument_();
    this->AddSlicesArgument_();
    this->AddSegmentsArgument_();

    return this->GetResultHelper_();
}

void TorusMeshParseBuilder::AddInnerRadiusArgument_() {
    this->argumentParser_->add_argument(ArgParseWrapper::SHORT_INNER_RADIUS_ARGUMENT, ArgParseWrapper::LONG_INNER_RADIUS_ARGUMENT)
        .help("Inner radius of the mesh").nargs(1).scan<'f', float>().required();
}

void TorusMeshParseBuilder::AddOuterRadiusArgument_() {
    this->argumentParser_->add_argument(ArgParseWrapper::SHORT_OUTER_RADIUS_ARGUMENT, ArgParseWrapper::LONG_OUTER_RADIUS_ARGUMENT)
        .help("Outer radius of the mesh").nargs(1).scan<'f', float>().required();
}
