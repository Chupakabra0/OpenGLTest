#pragma once
#include "ArgParseBuilder/ArgParseBuilder.hpp"

class MainParseBuilder : public ArgParseBuilder {
public:
    explicit MainParseBuilder(const std::string programName);

    MainParseBuilder(const MainParseBuilder&) = delete;

    MainParseBuilder(MainParseBuilder&&) noexcept = default;

    MainParseBuilder& operator=(const MainParseBuilder&) = delete;

    MainParseBuilder& operator=(MainParseBuilder&&) noexcept = default;

    ~MainParseBuilder() override = default;

    std::unique_ptr<argparse::ArgumentParser> GetUniqueProduct() override;

private:
    void AddHeightArgument_();

    void AddWidthArgument_();

    void AddTitleArgument_();

    void AddCameraPositionArgument_();

    void AddCameraTargetArgument_();

    void AddCameraAxisArguments_();

    void AddNearArgument_();

    void AddFarArgument_();

    void AddTopLeftArgument_();

    void AddBottomRightArgument_();

    void AddFieldOfViewArgument_();
};
