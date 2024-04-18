#pragma once
#include "ArgParseMeshGeneratorCreator/BaseArgParseMeshGeneratorCreator/BaseArgParseMeshGeneratorCreator.hpp"

class CylinderMeshGeneratorCreator : public BaseArgParseMeshGeneratorCreator {
public:
    CylinderMeshGeneratorCreator() = delete;

    explicit CylinderMeshGeneratorCreator(const std::shared_ptr<IMeshGeneratorFactory>& meshGeneratorFactory);

    CylinderMeshGeneratorCreator(const CylinderMeshGeneratorCreator&) = default;

    CylinderMeshGeneratorCreator(CylinderMeshGeneratorCreator&&) noexcept = default;

    CylinderMeshGeneratorCreator& operator=(const CylinderMeshGeneratorCreator&) = default;

    CylinderMeshGeneratorCreator& operator=(CylinderMeshGeneratorCreator&&) noexcept = default;

    ~CylinderMeshGeneratorCreator() override = default;

    std::shared_ptr<IMeshGenerator> Create(argparse::ArgumentParser& argumentParser) override;
};

