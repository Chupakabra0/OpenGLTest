#pragma once
#include "ArgParseMeshGeneratorCreator/BaseArgParseMeshGeneratorCreator/BaseArgParseMeshGeneratorCreator.hpp"

class IcosahedronMeshGeneratorCreator : public BaseArgParseMeshGeneratorCreator {
public:
    IcosahedronMeshGeneratorCreator() = delete;

    explicit IcosahedronMeshGeneratorCreator(const std::shared_ptr<IMeshGeneratorFactory>& meshGeneratorFactory);

    IcosahedronMeshGeneratorCreator(const IcosahedronMeshGeneratorCreator&) = default;

    IcosahedronMeshGeneratorCreator(IcosahedronMeshGeneratorCreator&&) noexcept = default;

    IcosahedronMeshGeneratorCreator& operator=(const IcosahedronMeshGeneratorCreator&) = default;

    IcosahedronMeshGeneratorCreator& operator=(IcosahedronMeshGeneratorCreator&&) noexcept = default;

    ~IcosahedronMeshGeneratorCreator() override = default;

    std::shared_ptr<IMeshGenerator> Create(argparse::ArgumentParser& argumentParser) override;
};
