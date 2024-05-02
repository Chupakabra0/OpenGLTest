#pragma once
#include "ArgParseMeshGeneratorCreator/BaseArgParseMeshGeneratorCreator/BaseArgParseMeshGeneratorCreator.hpp"

class UvSphereMeshGeneratorCreator : public BaseArgParseMeshGeneratorCreator {
public:
    UvSphereMeshGeneratorCreator() = delete;

    explicit UvSphereMeshGeneratorCreator(const std::shared_ptr<IMeshGeneratorFactory>& meshGeneratorFactory);

    UvSphereMeshGeneratorCreator(const UvSphereMeshGeneratorCreator&) = default;

    UvSphereMeshGeneratorCreator(UvSphereMeshGeneratorCreator&&) noexcept = default;

    UvSphereMeshGeneratorCreator& operator=(const UvSphereMeshGeneratorCreator&) = default;

    UvSphereMeshGeneratorCreator& operator=(UvSphereMeshGeneratorCreator&&) noexcept = default;

    ~UvSphereMeshGeneratorCreator() override = default;

    std::shared_ptr<IMeshGenerator> Create(argparse::ArgumentParser& argumentParser) override;
};
