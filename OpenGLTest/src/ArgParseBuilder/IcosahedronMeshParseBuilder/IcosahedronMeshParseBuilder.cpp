#include "ArgParseBuilder/IcosahedronMeshParseBuilder/IcosahedronMeshParseBuilder.hpp"
#include "ArgParseWrapper/ArgParseWrapper.hpp"

const char* IcosahedronMeshParseBuilder::PARSE_NAME = ArgParseWrapper::ICOSAHEDRON_COMMAND;
const char* IcosahedronMeshParseBuilder::PARSE_DESC = "Generate icosahedron mesh";

IcosahedronMeshParseBuilder::IcosahedronMeshParseBuilder()
    : BaseMeshParseBuilder(IcosahedronMeshParseBuilder::PARSE_NAME) {

}

std::unique_ptr<argparse::ArgumentParser> IcosahedronMeshParseBuilder::GetUniqueProduct() {
    this->AddDesc_(IcosahedronMeshParseBuilder::PARSE_DESC);

    this->AddOriginArgument_();
    this->AddColorArgument_();
    this->AddRadiusArgument_();

    return this->GetResultHelper_();
}
