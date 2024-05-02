#pragma once
#include "ArgParseMeshGeneratorCreator/BaseArgParseMeshGeneratorCreator/BaseArgParseMeshGeneratorCreator.hpp"

class RectangleMeshGeneratorCreator : public BaseArgParseMeshGeneratorCreator {
public:
    RectangleMeshGeneratorCreator() = delete;

    explicit RectangleMeshGeneratorCreator(const std::shared_ptr<IMeshGeneratorFactory>& meshGeneratorFactory);

    RectangleMeshGeneratorCreator(const RectangleMeshGeneratorCreator&) = default;

    RectangleMeshGeneratorCreator(RectangleMeshGeneratorCreator&&) noexcept = default;

    RectangleMeshGeneratorCreator& operator=(const RectangleMeshGeneratorCreator&) = default;

    RectangleMeshGeneratorCreator& operator=(RectangleMeshGeneratorCreator&&) noexcept = default;

    ~RectangleMeshGeneratorCreator() override = default;

    std::shared_ptr<IMeshGenerator> Create(argparse::ArgumentParser& argumentParser) override;
};
