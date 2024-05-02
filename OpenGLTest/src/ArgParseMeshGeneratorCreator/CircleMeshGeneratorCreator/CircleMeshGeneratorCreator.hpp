#pragma once
#include "ArgParseMeshGeneratorCreator/IArgParseMeshGeneratorCreator.hpp"
#include "ArgParseMeshGeneratorCreator/BaseArgParseMeshGeneratorCreator/BaseArgParseMeshGeneratorCreator.hpp"

class CircleMeshGeneratorCreator : public BaseArgParseMeshGeneratorCreator {
public:
    CircleMeshGeneratorCreator() = delete;

    explicit CircleMeshGeneratorCreator(const std::shared_ptr<IMeshGeneratorFactory>& meshGeneratorFactory);

    CircleMeshGeneratorCreator(const CircleMeshGeneratorCreator&) = default;

    CircleMeshGeneratorCreator(CircleMeshGeneratorCreator&&) noexcept = default;

    CircleMeshGeneratorCreator& operator=(const CircleMeshGeneratorCreator&) = default;

    CircleMeshGeneratorCreator& operator=(CircleMeshGeneratorCreator&&) noexcept = default;

    ~CircleMeshGeneratorCreator() override = default;

    std::shared_ptr<IMeshGenerator> Create(argparse::ArgumentParser& argumentParser) override;
};
