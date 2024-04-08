#pragma once
#include "BaseMeshParseBuilder.hpp"

class RectangleMeshParseBuilder : public BaseMeshParseBuilder {
private:
    static constexpr const char* PARSE_NAME = ArgParseWrapper::RECTANGLE_COMMAND;
    static constexpr const char* PARSE_DESC = "Generate rectangle mesh";

public:
    explicit RectangleMeshParseBuilder()
        : BaseMeshParseBuilder(RectangleMeshParseBuilder::PARSE_NAME) {

    }

    RectangleMeshParseBuilder(const RectangleMeshParseBuilder&) = delete;

    RectangleMeshParseBuilder(RectangleMeshParseBuilder&&) noexcept = default;

    RectangleMeshParseBuilder& operator=(const RectangleMeshParseBuilder&) = delete;

    RectangleMeshParseBuilder& operator=(RectangleMeshParseBuilder&&) noexcept = default;

    ~RectangleMeshParseBuilder() override = default;

    std::unique_ptr<argparse::ArgumentParser> GetUniqueProduct() override {
        this->AddDesc_(RectangleMeshParseBuilder::PARSE_DESC);

        this->AddOriginArgument_();
        this->AddColorArgument_();
        this->AddHeightArgument_();
        this->AddWidthArgument_();

        return this->GetResultHelper_();
    }
};
