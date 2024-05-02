#include "ArgParseMeshGeneratorCreator/ParallelepipedMeshGeneratorCreator/ParallelepipedMeshGeneratorCreator.hpp"

#include "ArgParseWrapper/ArgParseWrapper.hpp"
#include "MeshGenerators/GenericMeshGenerators/ParallelepipedGenerator/ParallelepipedGenerator.hpp"
#include "Utils/Utils.hpp"

ParallelepipedMeshGeneratorCreator::ParallelepipedMeshGeneratorCreator(const std::shared_ptr<IMeshGeneratorFactory>& meshGeneratorFactory)
    : BaseArgParseMeshGeneratorCreator(meshGeneratorFactory) {
    
}

std::shared_ptr<IMeshGenerator> ParallelepipedMeshGeneratorCreator::Create(argparse::ArgumentParser& argumentParser) {
    const auto origin =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::PARALLELEPIPED_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT);
    const auto color =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::PARALLELEPIPED_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_COLOR_ARGUMENT);
    const auto height =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::PARALLELEPIPED_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_HEIGHT_ARGUMENT);
    const auto width =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::PARALLELEPIPED_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_WIDTH_ARGUMENT);
    const auto depth =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::PARALLELEPIPED_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_DEPTH_ARGUMENT);

    return this->meshGeneratorFactory_->GenerateUniqueParallelipedGenerator(
        height, width, depth, VectorToVec3(origin), VectorToVec3(color)
    );
}
