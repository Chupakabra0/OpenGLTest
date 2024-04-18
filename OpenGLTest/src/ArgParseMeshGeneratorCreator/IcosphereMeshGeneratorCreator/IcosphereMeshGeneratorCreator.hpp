#pragma once
#include "ArgParseMeshGeneratorCreator/BaseArgParseMeshGeneratorCreator/BaseArgParseMeshGeneratorCreator.hpp"

class IcosphereMeshGeneratorCreator : public BaseArgParseMeshGeneratorCreator {
public:
    IcosphereMeshGeneratorCreator() = delete;

    explicit IcosphereMeshGeneratorCreator(const std::shared_ptr<IMeshGeneratorFactory>& meshGeneratorFactory);

    IcosphereMeshGeneratorCreator(const IcosphereMeshGeneratorCreator&) = default;

    IcosphereMeshGeneratorCreator(IcosphereMeshGeneratorCreator&&) noexcept = default;

    IcosphereMeshGeneratorCreator& operator=(const IcosphereMeshGeneratorCreator&) = default;

    IcosphereMeshGeneratorCreator& operator=(IcosphereMeshGeneratorCreator&&) noexcept = default;

    ~IcosphereMeshGeneratorCreator() override = default;

    std::shared_ptr<IMeshGenerator> Create(argparse::ArgumentParser& argumentParser) override;
};
