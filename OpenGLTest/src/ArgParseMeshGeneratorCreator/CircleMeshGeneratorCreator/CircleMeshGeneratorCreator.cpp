#include "ArgParseMeshGeneratorCreator/CircleMeshGeneratorCreator/CircleMeshGeneratorCreator.hpp"

#include "ArgParseWrapper/ArgParseWrapper.hpp"
#include "MeshGenerators/GenericMeshGenerators/CircleGenerator/CircleGenerator.hpp"
#include "Utils/Utils.hpp"

CircleMeshGeneratorCreator::CircleMeshGeneratorCreator(const std::shared_ptr<IMeshGeneratorFactory>& meshGeneratorFactory)
    : BaseArgParseMeshGeneratorCreator(meshGeneratorFactory) {
        
}

std::shared_ptr<IMeshGenerator> CircleMeshGeneratorCreator::Create(argparse::ArgumentParser& argumentParser) {
    const auto origin =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::CIRCLE_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT);
    const auto color =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::CIRCLE_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_COLOR_ARGUMENT);
    const auto radius =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::CIRCLE_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_RADIUS_ARGUMENT);
    const auto segments =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::CIRCLE_COMMAND)
            .get<int>(ArgParseWrapper::SHORT_SEGMENTS_ARGUMENT);

    return this->meshGeneratorFactory_->GenerateUniqueCircleGenerator(
        radius, segments, VectorToVec3(origin), VectorToVec3(color)
    );
}
