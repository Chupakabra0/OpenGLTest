#pragma once
#include "ArgParseBuilder/ArgParseBuilder.hpp"

class BaseMeshParseBuilder : public ArgParseBuilder {
public:
    BaseMeshParseBuilder() = delete;

    BaseMeshParseBuilder(const BaseMeshParseBuilder&) = delete;

    BaseMeshParseBuilder(BaseMeshParseBuilder&&) noexcept = default;

    BaseMeshParseBuilder& operator=(const BaseMeshParseBuilder&) = delete;

    BaseMeshParseBuilder& operator=(BaseMeshParseBuilder&&) noexcept = default;

    ~BaseMeshParseBuilder() override = default;

    explicit BaseMeshParseBuilder(const std::string& name);

    std::unique_ptr<argparse::ArgumentParser> GetUniqueProduct() override = 0;

protected:
    virtual void AddOriginArgument_();

    virtual void AddColorArgument_();

    virtual void AddSlicesArgument_();

    virtual void AddSegmentsArgument_();

    virtual void AddRadiusArgument_();

    virtual void AddHeightArgument_();

    virtual void AddWidthArgument_();

    virtual void AddDepthArgument_();

    virtual void AddDesc_(const std::string& desc);
};
