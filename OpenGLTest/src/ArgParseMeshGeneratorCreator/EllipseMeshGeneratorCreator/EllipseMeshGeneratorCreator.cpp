#include "ArgParseMeshGeneratorCreator/EllipseMeshGeneratorCreator/EllipseMeshGeneratorCreator.hpp"

#include "ArgParseWrapper/ArgParseWrapper.hpp"
#include "MeshGenerators/GenericMeshGenerators/EllipseGenerator/EllipseGenerator.hpp"
#include "Utils/Utils.hpp"

EllipseMeshGeneratorCreator::EllipseMeshGeneratorCreator(const std::shared_ptr<IMeshGeneratorFactory>& meshGeneratorFactory)
    : BaseArgParseMeshGeneratorCreator(meshGeneratorFactory) {

}

std::shared_ptr<IMeshGenerator> EllipseMeshGeneratorCreator::Create(argparse::ArgumentParser& argumentParser) {
    const auto origin =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::ELLIPSE_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT);
    const auto color =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::ELLIPSE_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_COLOR_ARGUMENT);
    const auto a =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::ELLIPSE_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_A_PARAMETER_ARGUMENT);
    const auto b =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::ELLIPSE_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_B_PARAMETER_ARGUMENT);
    const auto segments =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::ELLIPSE_COMMAND)
            .get<int>(ArgParseWrapper::SHORT_SEGMENTS_ARGUMENT);

    return this->meshGeneratorFactory_->GenerateUniqueEllipseGenerator(
        a, b, segments, VectorToVec3(origin), VectorToVec3(color)
    );
}
