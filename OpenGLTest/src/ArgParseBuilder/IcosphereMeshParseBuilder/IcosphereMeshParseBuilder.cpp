#include "ArgParseBuilder/IcosphereMeshParseBuilder/IcosphereMeshParseBuilder.hpp"
#include "ArgParseWrapper/ArgParseWrapper.hpp"

const char* IcosphereMeshParseBuilder::PARSE_NAME = ArgParseWrapper::ICOSPHERE_COMMAND;
const char* IcosphereMeshParseBuilder::PARSE_DESC = "Generate icosphere mesh";

IcosphereMeshParseBuilder::IcosphereMeshParseBuilder()
    : BaseMeshParseBuilder(IcosphereMeshParseBuilder::PARSE_NAME) {

}

std::unique_ptr<argparse::ArgumentParser> IcosphereMeshParseBuilder::GetUniqueProduct() {
    this->AddDesc_(IcosphereMeshParseBuilder::PARSE_DESC);

    this->AddOriginArgument_();
    this->AddColorArgument_();
    this->AddRadiusArgument_();
    this->AddIterationsArgument_();

    return this->GetResultHelper_();
}

void IcosphereMeshParseBuilder::AddIterationsArgument_() {
    this->argumentParser_->add_argument(ArgParseWrapper::SHORT_ITERATIONS_ARGUMENT, ArgParseWrapper::LONG_ITERATIONS_ARGUMENT)
        .help("Iterations of the mesh").nargs(1).scan<'i', int>().required();
}
