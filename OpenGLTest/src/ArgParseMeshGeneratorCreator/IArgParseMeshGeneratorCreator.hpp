#pragma once
#include "MeshGenerators/MeshGenerator.hpp"

#include <memory>
#include <argparse/argparse.hpp>

struct IArgParseMeshGeneratorCreator {
public:
    explicit IArgParseMeshGeneratorCreator() = default;

    IArgParseMeshGeneratorCreator(const IArgParseMeshGeneratorCreator&) = default;

    IArgParseMeshGeneratorCreator(IArgParseMeshGeneratorCreator&&) noexcept = default;

    IArgParseMeshGeneratorCreator& operator=(const IArgParseMeshGeneratorCreator&) = default;

    IArgParseMeshGeneratorCreator& operator=(IArgParseMeshGeneratorCreator&&) noexcept = default;

    virtual ~IArgParseMeshGeneratorCreator() = default;

    virtual std::shared_ptr<IMeshGenerator> Create(argparse::ArgumentParser& argumentParser) = 0;
};
