#pragma once
#include "ArgParseMeshGeneratorCreator/BaseArgParseMeshGeneratorCreator/BaseArgParseMeshGeneratorCreator.hpp"

class ParallelepipedMeshGeneratorCreator : public BaseArgParseMeshGeneratorCreator {
public:
    ParallelepipedMeshGeneratorCreator() = delete;

    explicit ParallelepipedMeshGeneratorCreator(const std::shared_ptr<IMeshGeneratorFactory>& meshGeneratorFactory);

    ParallelepipedMeshGeneratorCreator(const ParallelepipedMeshGeneratorCreator&) = default;

    ParallelepipedMeshGeneratorCreator(ParallelepipedMeshGeneratorCreator&&) noexcept = default;

    ParallelepipedMeshGeneratorCreator& operator=(const ParallelepipedMeshGeneratorCreator&) = default;

    ParallelepipedMeshGeneratorCreator& operator=(ParallelepipedMeshGeneratorCreator&&) noexcept = default;

    ~ParallelepipedMeshGeneratorCreator() override = default;

    std::shared_ptr<IMeshGenerator> Create(argparse::ArgumentParser& argumentParser) override;
};
