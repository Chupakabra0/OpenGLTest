#include "ArgParseMeshGeneratorCreator/UvSphereMeshGeneratorCreator/UvSphereMeshGeneratorCreator.hpp"

#include "ArgParseWrapper/ArgParseWrapper.hpp"
#include "MeshGenerators/GenericMeshGenerators/UVSphereGenerator/UVSphereGenerator.hpp"
#include "Utils/Utils.hpp"

UvSphereMeshGeneratorCreator::UvSphereMeshGeneratorCreator(const std::shared_ptr<IMeshGeneratorFactory>& meshGeneratorFactory)
    : BaseArgParseMeshGeneratorCreator(meshGeneratorFactory) {
    
}

std::shared_ptr<IMeshGenerator> UvSphereMeshGeneratorCreator::Create(argparse::ArgumentParser& argumentParser) {
    const auto origin =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::UV_SPHERE_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT);
    const auto color =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::UV_SPHERE_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_COLOR_ARGUMENT);
    const auto radius =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::UV_SPHERE_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_RADIUS_ARGUMENT);
    const auto slices =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::UV_SPHERE_COMMAND)
            .get<int>(ArgParseWrapper::SHORT_SLICES_ARGUMENT);
    const auto segments =
        argumentParser.at<argparse::ArgumentParser>(ArgParseWrapper::UV_SPHERE_COMMAND)
            .get<int>(ArgParseWrapper::SHORT_SEGMENTS_ARGUMENT);

    return this->meshGeneratorFactory_->GenerateUniqueUvSphereGenerator(
        radius, slices, segments, VectorToVec3(origin), VectorToVec3(color)
    );
}
