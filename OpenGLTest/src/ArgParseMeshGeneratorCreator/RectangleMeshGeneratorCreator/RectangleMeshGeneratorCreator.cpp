#include "ArgParseMeshGeneratorCreator/RectangleMeshGeneratorCreator/RectangleMeshGeneratorCreator.hpp"

#include "ArgParseWrapper/ArgParseWrapper.hpp"
#include "MeshGenerators/GenericMeshGenerators/RectangleGenerator/RectangleGenerator.hpp"
#include "Utils/Utils.hpp"

RectangleMeshGeneratorCreator::RectangleMeshGeneratorCreator(const std::shared_ptr<IMeshGeneratorFactory>& meshGeneratorFactory)
    : BaseArgParseMeshGeneratorCreator(meshGeneratorFactory) {
    
}

std::shared_ptr<IMeshGenerator> RectangleMeshGeneratorCreator::Create(argparse::ArgumentParser& argumentParser) {
    const auto origin =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::RECTANGLE_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT);
    const auto color  =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::RECTANGLE_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_COLOR_ARGUMENT);
    const auto height =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::RECTANGLE_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_HEIGHT_ARGUMENT);
    const auto width =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::RECTANGLE_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_WIDTH_ARGUMENT);

    return this->meshGeneratorFactory_->GenerateUniqueRectangleGenerator(
        height, width, VectorToVec3(origin), VectorToVec3(color)
    );
}
