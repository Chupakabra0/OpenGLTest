#include "ArgParseMeshGeneratorCreator/CylinderMeshGeneratorCreator/CylinderMeshGeneratorCreator.hpp"

#include "ArgParseWrapper/ArgParseWrapper.hpp"
#include "MeshGenerators/GenericMeshGenerators/CylinderGenerator/CylinderGenerator.hpp"
#include "Utils/Utils.hpp"

CylinderMeshGeneratorCreator::CylinderMeshGeneratorCreator(const std::shared_ptr<IMeshGeneratorFactory>& meshGeneratorFactory)
    : BaseArgParseMeshGeneratorCreator(meshGeneratorFactory) {

}

std::shared_ptr<IMeshGenerator> CylinderMeshGeneratorCreator::Create(argparse::ArgumentParser& argumentParser) {
    const auto origin =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::CYLINDER_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT);
    const auto color =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::CYLINDER_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_COLOR_ARGUMENT);
    const auto height =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::CYLINDER_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_HEIGHT_ARGUMENT);
    const auto radius =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::CYLINDER_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_RADIUS_ARGUMENT);
    const auto segments =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::CYLINDER_COMMAND)
            .get<int>(ArgParseWrapper::SHORT_SEGMENTS_ARGUMENT);
    const auto slices =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::CYLINDER_COMMAND)
            .get<int>(ArgParseWrapper::SHORT_SLICES_ARGUMENT);

    return this->meshGeneratorFactory_->GenerateUniqueCylinderGenerator(
        height, radius, segments, slices, VectorToVec3(origin), VectorToVec3(color)
    );
}
