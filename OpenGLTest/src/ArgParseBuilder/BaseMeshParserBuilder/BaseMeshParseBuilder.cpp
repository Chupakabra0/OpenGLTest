#include "ArgParseBuilder/BaseMeshParserBuilder/BaseMeshParseBuilder.hpp"
#include "ArgParseWrapper/ArgParseWrapper.hpp"

BaseMeshParseBuilder::BaseMeshParseBuilder(const std::string& name)
    : ArgParseBuilder(name) {
    this->Reset();
}

void BaseMeshParseBuilder::AddOriginArgument_() {
    this->argumentParser_->add_argument(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT, ArgParseWrapper::LONG_ORIGIN_ARGUMENT)
        .help("Coordinate of mesh's origin in Cartesian XYZ system").nargs(3).scan<'f', float>().required();
}

void BaseMeshParseBuilder::AddColorArgument_() {
    this->argumentParser_->add_argument(ArgParseWrapper::SHORT_COLOR_ARGUMENT, ArgParseWrapper::LONG_COLOR_ARGUMENT)
        .help("Color of the mesh in normalized RGB format (0.0 min — color, 1.0 — max color)").nargs(3).scan<'f', float>().required();
}

void BaseMeshParseBuilder::AddSlicesArgument_() {
    this->argumentParser_->add_argument(ArgParseWrapper::SHORT_SLICES_ARGUMENT, ArgParseWrapper::LONG_SLICES_ARGUMENT)
        .help("Slices of the mesh").nargs(1).scan<'i', int>().required();
}

void BaseMeshParseBuilder::AddSegmentsArgument_() {
    this->argumentParser_->add_argument(ArgParseWrapper::SHORT_SEGMENTS_ARGUMENT, ArgParseWrapper::LONG_SEGMENTS_ARGUMENT)
        .help("Segments of the mesh").nargs(1).scan<'i', int>().required();
}

void BaseMeshParseBuilder::AddRadiusArgument_() {
    this->argumentParser_->add_argument(ArgParseWrapper::SHORT_RADIUS_ARGUMENT, ArgParseWrapper::LONG_RADIUS_ARGUMENT)
        .help("Radius of the mesh").nargs(1).scan<'f', float>().required();
}

void BaseMeshParseBuilder::AddHeightArgument_() {
    this->argumentParser_->add_argument(ArgParseWrapper::SHORT_HEIGHT_ARGUMENT, ArgParseWrapper::LONG_HEIGHT_ARGUMENT)
        .help("Height of the mesh").nargs(1).scan<'f', float>().required();
}

void BaseMeshParseBuilder::AddWidthArgument_() {
    this->argumentParser_->add_argument(ArgParseWrapper::SHORT_WIDTH_ARGUMENT, ArgParseWrapper::LONG_WIDTH_ARGUMENT)
        .help("Height of the mesh").nargs(1).scan<'f', float>().required();
}

void BaseMeshParseBuilder::AddDepthArgument_() {
    this->argumentParser_->add_argument(ArgParseWrapper::SHORT_DEPTH_ARGUMENT, ArgParseWrapper::LONG_DEPTH_ARGUMENT)
        .help("Depth of the mesh").nargs(1).scan<'f', float>().required();
}

void BaseMeshParseBuilder::AddDesc_(const std::string& desc) {
    this->argumentParser_->add_description(desc);
}
