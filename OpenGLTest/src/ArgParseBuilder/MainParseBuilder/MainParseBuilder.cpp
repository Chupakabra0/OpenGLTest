#include "ArgParseBuilder/MainParseBuilder/MainParseBuilder.hpp"
#include "ArgParseWrapper/ArgParseWrapper.hpp"

MainParseBuilder::MainParseBuilder(const std::string programName)
    : ArgParseBuilder(programName) {

}

std::unique_ptr<argparse::ArgumentParser> MainParseBuilder::GetUniqueProduct() {
    this->AddJsonArgument_();
    this->AddHeightArgument_();
    this->AddWidthArgument_();
    this->AddTitleArgument_();
    this->AddCameraPositionArgument_();
    this->AddCameraTargetArgument_();
    this->AddCameraAxisArguments_();
    this->AddNearArgument_();
    this->AddFarArgument_();
    this->AddTopLeftArgument_();
    this->AddBottomRightArgument_();
    this->AddFieldOfViewArgument_();

    return this->GetResultHelper_();
}

void MainParseBuilder::AddJsonArgument_() {
    this->argumentParser_->add_argument(
        ArgParseWrapper::SHORT_CONFIG_JSON_ARGUMENT,
        ArgParseWrapper::LONG_CONFIG_JSON_ARGUMENT)
        .help("Config json filepath")
        .nargs(1).default_value(ArgParseWrapper::DEFAULT_CONFIG_JSON_VALUE);
}

void MainParseBuilder::AddHeightArgument_() {
    this->argumentParser_->add_argument(
        ArgParseWrapper::SHORT_WINDOW_HEIGHT_ARGUMENT,
        ArgParseWrapper::LONG_WINDOW_HEIGHT_ARGUMENT)
        .help("Height of application window")
        .nargs(1).scan<'i', int>()
        .default_value(ArgParseWrapper::DEFAULT_WINDOW_HEIGHT_VALUE);
}

void MainParseBuilder::AddWidthArgument_() {
    this->argumentParser_->add_argument(
        ArgParseWrapper::SHORT_WINDOW_WIDTH_ARGUMENT,
        ArgParseWrapper::LONG_WINDOW_WIDTH_ARGUMENT)
        .help("Width of application window")
        .nargs(1).scan<'i', int>()
        .default_value(ArgParseWrapper::DEFAULT_WINDOW_WIDTH_VALUE);
}

void MainParseBuilder::AddTitleArgument_() {
    this->argumentParser_->add_argument(
        ArgParseWrapper::SHORT_WINDOW_NAME_ARGUMENT,
        ArgParseWrapper::LONG_WINDOW_NAME_ARGUMENT)
        .help("Title of application window")
        .default_value(ArgParseWrapper::DEFAULT_WINDOW_NAME_VALUE);
}

void MainParseBuilder::AddCameraPositionArgument_() {
    this->argumentParser_->add_argument(
        ArgParseWrapper::SHORT_CAMERA_POSITION_ARGUMENT,
        ArgParseWrapper::LONG_CAMERA_POSITION_ARGUMENT)
        .help("Initial camera position")
        .nargs(3).scan<'f', float>()
        .default_value(ArgParseWrapper::DEFAULT_CAMERA_POSITION_VALUE);
}

void MainParseBuilder::AddCameraTargetArgument_() {
    this->argumentParser_->add_argument(
        ArgParseWrapper::SHORT_CAMERA_TARET_ARGUMENT,
        ArgParseWrapper::LONG_CAMERA_TARET_ARGUMENT)
        .help("Initial camera target")
        .nargs(3).scan<'f', float>()
        .default_value(ArgParseWrapper::DEFAULT_CAMERA_TARET_VALUE);
}

void MainParseBuilder::AddCameraAxisArguments_() {
    this->argumentParser_->add_argument(
        ArgParseWrapper::SHORT_CAMERA_AXIS_X_ARGUMENT,
        ArgParseWrapper::LONG_CAMERA_AXIS_X_ARGUMENT)
        .help("Initial basis Ox vector of camera")
        .nargs(3).scan<'f', float>()
        .default_value(ArgParseWrapper::DEFAULT_CAMERA_AXIS_X_VALUE);

    this->argumentParser_->add_argument(
        ArgParseWrapper::SHORT_CAMERA_AXIS_Y_ARGUMENT,
        ArgParseWrapper::LONG_CAMERA_AXIS_Y_ARGUMENT)
        .help("Initial basis Oy vector of camera")
        .nargs(3).scan<'f', float>()
        .default_value(ArgParseWrapper::DEFAULT_CAMERA_AXIS_Y_VALUE);

    this->argumentParser_->add_argument(
        ArgParseWrapper::SHORT_CAMERA_AXIS_Z_ARGUMENT,
        ArgParseWrapper::LONG_CAMERA_AXIS_Z_ARGUMENT)
        .help("Initial basis Oz vector of camera")
        .nargs(3).scan<'f', float>()
        .default_value(ArgParseWrapper::DEFAULT_CAMERA_AXIS_Z_VALUE);
}

void MainParseBuilder::AddNearArgument_() {
    this->argumentParser_->add_argument(
        ArgParseWrapper::SHORT_VIEWPORT_NEAR_Z_ARGUMENT,
        ArgParseWrapper::LONG_VIEWPORT_NEAR_Z_ARGUMENT)
        .help("Distance to the nearest viewport plane")
        .nargs(1).scan<'f', float>()
        .default_value(ArgParseWrapper::DEFAULT_VIEWPORT_NEAR_Z_VALUE);
}

void MainParseBuilder::AddFarArgument_() {
    this->argumentParser_->add_argument(
        ArgParseWrapper::SHORT_VIEWPORT_FAR_Z_ARGUMENT,
        ArgParseWrapper::LONG_VIEWPORT_FAR_Z_ARGUMENT)
        .help("Distance to the farthest viewport plane")
        .nargs(1).scan<'f', float>()
        .default_value(ArgParseWrapper::DEFAULT_VIEWPORT_FAR_Z_VALUE);
}

void MainParseBuilder::AddTopLeftArgument_() {
    this->argumentParser_->add_argument(
        ArgParseWrapper::SHORT_VIEWPORT_TOP_LEFT_ARGUMENT,
        ArgParseWrapper::LONG_VIEWPORT_TOP_LEFT_ARGUMENT)
        .help("Viewport top left point")
        .nargs(2).scan<'f', float>()
        .default_value(ArgParseWrapper::DEFAULT_VIEWPORT_TOP_LEFT_VALUE);
}

void MainParseBuilder::AddBottomRightArgument_() {
    this->argumentParser_->add_argument(
        ArgParseWrapper::SHORT_VIEWPORT_BOTTOM_RIGHT_ARGUMENT,
        ArgParseWrapper::LONG_VIEWPORT_BOTTOM_RIGHT_ARGUMENT)
        .help("Viewport bottom right point")
        .nargs(2).scan<'f', float>()
        .default_value(ArgParseWrapper::DEFAULT_VIEWPORT_BOTTOM_RIGHT_VALUE);
}

void MainParseBuilder::AddFieldOfViewArgument_() {
    this->argumentParser_->add_argument(
        ArgParseWrapper::SHORT_VIEWPORT_FOV_ARGUMENT,
        ArgParseWrapper::LONG_VIEWPORT_FOV_ARGUMENT)
        .help("Angle of observable field camera view in degrees")
        .nargs(1).scan<'f', float>()
        .default_value(ArgParseWrapper::DEFAULT_VIEWPORT_FOV_VALUE);
}
