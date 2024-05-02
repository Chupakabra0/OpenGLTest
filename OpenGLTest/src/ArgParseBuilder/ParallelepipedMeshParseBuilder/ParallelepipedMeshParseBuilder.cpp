#include "ArgParseBuilder/ParallelepipedMeshParseBuilder/ParallelepipedMeshParseBuilder.hpp"
#include "ArgParseWrapper/ArgParseWrapper.hpp"

const char* ParallelepipedMeshParseBuilder::PARSE_NAME = ArgParseWrapper::PARALLELEPIPED_COMMAND;
const char* ParallelepipedMeshParseBuilder::PARSE_DESC = "Generate parallelepiped mesh";

ParallelepipedMeshParseBuilder::ParallelepipedMeshParseBuilder()
    : BaseMeshParseBuilder(ParallelepipedMeshParseBuilder::PARSE_NAME) {

}

std::unique_ptr<argparse::ArgumentParser> ParallelepipedMeshParseBuilder::GetUniqueProduct() {
    this->AddDesc_(ParallelepipedMeshParseBuilder::PARSE_DESC);

    this->AddOriginArgument_();
    this->AddColorArgument_();
    this->AddHeightArgument_();
    this->AddWidthArgument_();
    this->AddDepthArgument_();

    return this->GetResultHelper_();
}
