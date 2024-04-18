#pragma once
#include "ArgParseMeshGeneratorCreator/BaseArgParseMeshGeneratorCreator/BaseArgParseMeshGeneratorCreator.hpp"

class EllipseMeshGeneratorCreator : public BaseArgParseMeshGeneratorCreator {
public:
    EllipseMeshGeneratorCreator() = delete;

    explicit EllipseMeshGeneratorCreator(const std::shared_ptr<IMeshGeneratorFactory>& meshGeneratorFactory);

    EllipseMeshGeneratorCreator(const EllipseMeshGeneratorCreator&) = default;

    EllipseMeshGeneratorCreator(EllipseMeshGeneratorCreator&&) noexcept = default;

    EllipseMeshGeneratorCreator& operator=(const EllipseMeshGeneratorCreator&) = default;

    EllipseMeshGeneratorCreator& operator=(EllipseMeshGeneratorCreator&&) noexcept = default;

    ~EllipseMeshGeneratorCreator() override = default;

    std::shared_ptr<IMeshGenerator> Create(argparse::ArgumentParser& argumentParser) override;
};
