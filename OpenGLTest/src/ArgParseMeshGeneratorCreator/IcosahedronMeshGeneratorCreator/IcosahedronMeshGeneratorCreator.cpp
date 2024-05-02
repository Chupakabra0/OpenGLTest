#include "ArgParseMeshGeneratorCreator/IcosahedronMeshGeneratorCreator/IcosahedronMeshGeneratorCreator.hpp"

#include "ArgParseWrapper/ArgParseWrapper.hpp"
#include "MeshGenerators/GenericMeshGenerators/IcosahedronGenerator/IcosahedronGenerator.hpp"
#include "Utils/Utils.hpp"

IcosahedronMeshGeneratorCreator::IcosahedronMeshGeneratorCreator(const std::shared_ptr<IMeshGeneratorFactory>& meshGeneratorFactory)
    : BaseArgParseMeshGeneratorCreator(meshGeneratorFactory) {

}

std::shared_ptr<IMeshGenerator> IcosahedronMeshGeneratorCreator::Create(argparse::ArgumentParser& argumentParser) {
    const auto origin =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::ICOSAHEDRON_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT);
    const auto color =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::ICOSAHEDRON_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_COLOR_ARGUMENT);
    const auto radius =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::ICOSAHEDRON_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_RADIUS_ARGUMENT);

    return this->meshGeneratorFactory_->GenerateUniqueIcosahedronGenerator(
        radius, VectorToVec3(origin), VectorToVec3(color)
    );
}
