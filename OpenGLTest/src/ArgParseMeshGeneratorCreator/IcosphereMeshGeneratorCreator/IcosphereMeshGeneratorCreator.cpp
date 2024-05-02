#include "ArgParseMeshGeneratorCreator/IcosphereMeshGeneratorCreator/IcosphereMeshGeneratorCreator.hpp"

#include "ArgParseWrapper/ArgParseWrapper.hpp"
#include "MeshGenerators/GenericMeshGenerators/IcosphereGenerator/IcosphereGenerator.hpp"
#include "Utils/Utils.hpp"

IcosphereMeshGeneratorCreator::IcosphereMeshGeneratorCreator(const std::shared_ptr<IMeshGeneratorFactory>& meshGeneratorFactory)
    : BaseArgParseMeshGeneratorCreator(meshGeneratorFactory) {
    
}


std::shared_ptr<IMeshGenerator> IcosphereMeshGeneratorCreator::Create(argparse::ArgumentParser& argumentParser) {
    const auto origin =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::ICOSPHERE_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT);
    const auto color =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::ICOSPHERE_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_COLOR_ARGUMENT);
    const auto radius =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::ICOSPHERE_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_RADIUS_ARGUMENT);
    const auto iterations =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::ICOSPHERE_COMMAND)
            .get<int>(ArgParseWrapper::SHORT_ITERATIONS_ARGUMENT);

    return this->meshGeneratorFactory_->GenerateUniqueIcosphereGenerator(
        radius, iterations, VectorToVec3(origin), VectorToVec3(color)
    );
}
