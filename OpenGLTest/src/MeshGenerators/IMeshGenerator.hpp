#pragma once
#include "MeshInstance/IMeshInstance.hpp"

struct IMeshGenerator {
public:
    explicit IMeshGenerator() = default;

    IMeshGenerator(const IMeshGenerator&) = default;

    IMeshGenerator(IMeshGenerator&&) noexcept = default;

    IMeshGenerator& operator=(const IMeshGenerator&) = default;

    IMeshGenerator& operator=(IMeshGenerator&&) noexcept = default;

    virtual ~IMeshGenerator() = default;

    virtual std::shared_ptr<IMeshInstance> GenerateMesh() = 0;
};
