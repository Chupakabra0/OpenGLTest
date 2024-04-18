#include "ArgParseMeshGeneratorCreator/TorusMeshGeneratorCreator/TorusMeshGeneratorCreator.hpp"

#include "ArgParseWrapper/ArgParseWrapper.hpp"
#include "MeshGenerators/GenericMeshGenerators/TorusGenerator/TorusGenerator.hpp"
#include "Utils/Utils.hpp"

TorusMeshGeneratorCreator::TorusMeshGeneratorCreator(const std::shared_ptr<IMeshGeneratorFactory>& meshGeneratorFactory)
    : BaseArgParseMeshGeneratorCreator(meshGeneratorFactory) {
    
} 

std::shared_ptr<IMeshGenerator> TorusMeshGeneratorCreator::Create(argparse::ArgumentParser& argumentParser) {
    const auto origin =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::TORUS_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT);
    const auto color =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::TORUS_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_COLOR_ARGUMENT);
    const auto innerRadius =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::TORUS_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_INNER_RADIUS_ARGUMENT);
    const auto outerRadius =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::TORUS_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_OUTER_RADIUS_ARGUMENT);
    const auto slices =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::TORUS_COMMAND)
            .get<int>(ArgParseWrapper::SHORT_SLICES_ARGUMENT);
    const auto segments =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::TORUS_COMMAND)
            .get<int>(ArgParseWrapper::SHORT_SEGMENTS_ARGUMENT);

    return this->meshGeneratorFactory_->GenerateUniqueTorusGenerator(
        innerRadius, outerRadius, slices, segments, VectorToVec3(origin), VectorToVec3(color)
    );
}
