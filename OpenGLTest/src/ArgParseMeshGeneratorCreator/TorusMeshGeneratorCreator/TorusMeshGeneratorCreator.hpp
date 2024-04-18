#pragma once
#include "ArgParseMeshGeneratorCreator/BaseArgParseMeshGeneratorCreator/BaseArgParseMeshGeneratorCreator.hpp"

class TorusMeshGeneratorCreator : public BaseArgParseMeshGeneratorCreator {
public:
    TorusMeshGeneratorCreator() = delete;

    explicit TorusMeshGeneratorCreator(const std::shared_ptr<IMeshGeneratorFactory>& meshGeneratorFactory);

    TorusMeshGeneratorCreator(const TorusMeshGeneratorCreator&) = default;

    TorusMeshGeneratorCreator(TorusMeshGeneratorCreator&&) noexcept = default;

    TorusMeshGeneratorCreator& operator=(const TorusMeshGeneratorCreator&) = default;

    TorusMeshGeneratorCreator& operator=(TorusMeshGeneratorCreator&&) noexcept = default;

    ~TorusMeshGeneratorCreator() override = default;

    std::shared_ptr<IMeshGenerator> Create(argparse::ArgumentParser& argumentParser) override;
};
