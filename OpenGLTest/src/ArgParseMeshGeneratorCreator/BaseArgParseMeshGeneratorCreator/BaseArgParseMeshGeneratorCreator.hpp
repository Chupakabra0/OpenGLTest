#pragma once
#include "ArgParseMeshGeneratorCreator/IArgParseMeshGeneratorCreator.hpp"
#include "MeshGeneratorFactory/IMeshGeneratorFactory.hpp"

class BaseArgParseMeshGeneratorCreator : public IArgParseMeshGeneratorCreator {
public:
    BaseArgParseMeshGeneratorCreator() = delete;

    explicit BaseArgParseMeshGeneratorCreator(const std::shared_ptr<IMeshGeneratorFactory>& meshGeneratorFactory);

    BaseArgParseMeshGeneratorCreator(const BaseArgParseMeshGeneratorCreator&) = default;

    BaseArgParseMeshGeneratorCreator(BaseArgParseMeshGeneratorCreator&&) noexcept = default;

    BaseArgParseMeshGeneratorCreator& operator=(const BaseArgParseMeshGeneratorCreator&) = default;

    BaseArgParseMeshGeneratorCreator& operator=(BaseArgParseMeshGeneratorCreator&&) noexcept = default;

    ~BaseArgParseMeshGeneratorCreator() override = default;

    std::shared_ptr<IMeshGenerator> Create(argparse::ArgumentParser& argumentParser) override = 0;

protected:
    std::shared_ptr<IMeshGeneratorFactory> meshGeneratorFactory_{};
};
