#include "ArgParseWrapper.hpp"
#include "MeshGenerators/CircleGenerator.hpp"
#include "MeshGenerators/CylinderGenerator.hpp"
#include "MeshGenerators/EllipseGenerator.hpp"
#include "MeshGenerators/IcosahedronGenerator.hpp"
#include "MeshGenerators/IcosphereGenerator.hpp"
#include "MeshGenerators/ParallelepipedGenerator.hpp"
#include "MeshGenerators/RectangleGenerator.hpp"
#include "MeshGenerators/TorusGenerator.hpp"
#include "MeshGenerators/UVSphereGenerator.hpp"

const std::vector<const char* const*> ArgParseWrapper::COMMAND_ARRAY = {
    &ArgParseWrapper::CIRCLE_COMMAND,
    &ArgParseWrapper::CYLINDER_COMMAND,
    &ArgParseWrapper::ELLIPSE_COMMAND,
    &ArgParseWrapper::ICOSAHEDRON_COMMAND,
    &ArgParseWrapper::ICOSPHERE_COMMAND,
    &ArgParseWrapper::PARALLELEPIPED_COMMAND,
    &ArgParseWrapper::RECTANGLE_COMMAND,
    &ArgParseWrapper::TORUS_COMMAND,
    &ArgParseWrapper::UV_SPHERE_COMMAND
};

const std::string ArgParseWrapper::DEFAULT_WINDOW_NAME_VALUE                  = "Test OpenGL";
const std::vector<float> ArgParseWrapper::DEFAULT_CAMERA_POSITION_VALUE       = std::vector<float>{0.0f, 0.0f, 500.0f};
const std::vector<float> ArgParseWrapper::DEFAULT_CAMERA_TARET_VALUE          = std::vector<float>{0.0f, 0.0f, 0.0f};
const std::vector<float> ArgParseWrapper::DEFAULT_CAMERA_AXIS_X_VALUE         = std::vector<float>{1.0f, 0.0f, 0.0f};
const std::vector<float> ArgParseWrapper::DEFAULT_CAMERA_AXIS_Y_VALUE         = std::vector<float>{0.0f, 1.0f, 0.0f};
const std::vector<float> ArgParseWrapper::DEFAULT_CAMERA_AXIS_Z_VALUE         = std::vector<float>{0.0f, 0.0f, -1.0f};
const std::vector<float> ArgParseWrapper::DEFAULT_VIEWPORT_TOP_LEFT_VALUE     = std::vector<float>{0.0f, 0.0f};
const std::vector<float> ArgParseWrapper::DEFAULT_VIEWPORT_BOTTOM_RIGHT_VALUE = std::vector<float>{ArgParseWrapper::DEFAULT_WINDOW_WIDTH_VALUE, ArgParseWrapper::DEFAULT_WINDOW_HEIGHT_VALUE};

glm::vec3 VectorToVec3(const std::vector<float>& vec) {
    if (vec.size() < 3) {
        throw std::runtime_error("Convert to glm::vec3 error");
    }

    return glm::vec3(vec[0], vec[1], vec[2]);
}

glm::vec2 VectorToVec2(const std::vector<float>& vec) {
    if (vec.size() < 2) {
        throw std::runtime_error("Convert to glm::vec2 error");
    }

    return glm::vec2(vec[0], vec[1]);
}

bool ArgParseWrapper::ParseAllArgs() {
    try {
        this->argumentParser_->parse_args(this->argv_);
    
        for (auto& command : ArgParseWrapper::COMMAND_ARRAY) {
            if (command != nullptr && this->argumentParser_->is_subcommand_used(*command)) {
                return true;
            }
        }
    }
    catch (const std::exception& exception) {
        for (auto& command : ArgParseWrapper::COMMAND_ARRAY) {
            if (command != nullptr && this->argumentParser_->is_subcommand_used(*command)) {
                std::cout << this->argumentParser_->at<argparse::ArgumentParser>(*command);
                
                return false;
            }
        }
    }

    std::cout << *this->argumentParser_;

    return false;
}

ApplicationConfig ArgParseWrapper::GetAppConfig() {
    const auto cameraPositionTemp  = this->argumentParser_->get<std::vector<float>>(ArgParseWrapper::SHORT_CAMERA_POSITION_ARGUMENT);
    const auto cameraTargetTemp    = this->argumentParser_->get<std::vector<float>>(ArgParseWrapper::SHORT_CAMERA_TARET_ARGUMENT);
    const auto cameraAxisX         = this->argumentParser_->get<std::vector<float>>(ArgParseWrapper::SHORT_CAMERA_AXIS_X_ARGUMENT);
    const auto cameraAxisY         = this->argumentParser_->get<std::vector<float>>(ArgParseWrapper::SHORT_CAMERA_AXIS_Y_ARGUMENT);
    const auto cameraAxisZ         = this->argumentParser_->get<std::vector<float>>(ArgParseWrapper::SHORT_CAMERA_AXIS_Z_ARGUMENT);
    const auto viewportTopLeftTemp = this->argumentParser_->get<std::vector<float>>(ArgParseWrapper::SHORT_VIEWPORT_TOP_LEFT_ARGUMENT);
    const auto viewportBottomRight = this->argumentParser_->get<std::vector<float>>(ArgParseWrapper::SHORT_VIEWPORT_BOTTOM_RIGHT_ARGUMENT);

    const ApplicationConfig config {
        .WINDOW_HEIGHT         = this->argumentParser_->get<int>(ArgParseWrapper::SHORT_WINDOW_HEIGHT_ARGUMENT),
        .WINDOW_WIDTH          = this->argumentParser_->get<int>(ArgParseWrapper::SHORT_WINDOW_WIDTH_ARGUMENT),
        .WINDOW_NAME           = this->argumentParser_->get<std::string>(ArgParseWrapper::SHORT_WINDOW_NAME_ARGUMENT),
        .CAMERA_POSITION       = VectorToVec3(cameraPositionTemp),
        .CAMERA_TARGET         = VectorToVec3(cameraTargetTemp),
        .CAMERA_AXIS_X         = VectorToVec3(cameraAxisX),
        .CAMERA_AXIS_Y         = VectorToVec3(cameraAxisY),
        .CAMERA_AXIS_Z         = VectorToVec3(cameraAxisZ),
        .VIEWPORT_TOP_LEFT     = VectorToVec2(viewportTopLeftTemp),
        .VIEWPORT_BOTTOM_RIGHT = VectorToVec2(viewportBottomRight),
        .VIEWPORT_FOV          = this->argumentParser_->get<float>(ArgParseWrapper::SHORT_VIEWPORT_FOV_ARGUMENT),
        .VIEWPORT_NEAR_Z       = this->argumentParser_->get<float>(ArgParseWrapper::SHORT_VIEWPORT_NEAR_Z_ARGUMENT),
        .VIEWPORT_FAR_Z        = this->argumentParser_->get<float>(ArgParseWrapper::SHORT_VIEWPORT_FAR_Z_ARGUMENT),
        .MESH_GENERATOR        = this->GetMeshGenerator_()
    };

    return config;
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetMeshGenerator_() {
    std::shared_ptr<MeshGenerator> result{};
    
    // TODO: change this if-nightmare just like in ParseAllArgs was done
    if (this->argumentParser_->is_subcommand_used(ArgParseWrapper::CIRCLE_COMMAND)) {
        result = this->GetCircleGenerator_(this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::CIRCLE_COMMAND));
    }
    else if (this->argumentParser_->is_subcommand_used(ArgParseWrapper::CYLINDER_COMMAND)) {
        result = this->GetCylinderGenerator_(this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::CYLINDER_COMMAND));
    }
    else if (this->argumentParser_->is_subcommand_used(ArgParseWrapper::ELLIPSE_COMMAND)) {
        result = this->GetEllipseGenerator_(this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::ELLIPSE_COMMAND));
    }
    else if (this->argumentParser_->is_subcommand_used(ArgParseWrapper::ICOSAHEDRON_COMMAND)) {
        result = this->GetIcosahedronGenerator_(this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::ICOSAHEDRON_COMMAND));
    }
    else if (this->argumentParser_->is_subcommand_used(ArgParseWrapper::ICOSPHERE_COMMAND)) {
        result = this->GetIcosphereGenerator_(this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::ICOSPHERE_COMMAND));
    }
    else if (this->argumentParser_->is_subcommand_used(ArgParseWrapper::PARALLELEPIPED_COMMAND)) {
        result = this->GetParallelepipedGenerator_(this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::PARALLELEPIPED_COMMAND));
    }
    else if (this->argumentParser_->is_subcommand_used(ArgParseWrapper::RECTANGLE_COMMAND)) {
        result = this->GetRectangleGenerator_(this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::RECTANGLE_COMMAND));
    }
    else if (this->argumentParser_->is_subcommand_used(ArgParseWrapper::TORUS_COMMAND)) {
        result = this->GetTorusGenerator_(this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::TORUS_COMMAND));
    }
    else if (this->argumentParser_->is_subcommand_used(ArgParseWrapper::UV_SPHERE_COMMAND)) {
        result = this->GetUvSphereGenerator_(this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::UV_SPHERE_COMMAND));
    }

    return result;
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetCircleGenerator_(argparse::ArgumentParser& parser) {
    const auto origin   = parser.get<std::vector<float>>(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT);
    const auto color    = parser.get<std::vector<float>>(ArgParseWrapper::SHORT_COLOR_ARGUMENT);
    const auto radius   = parser.get<float>(ArgParseWrapper::SHORT_RADIUS_ARGUMENT);
    const auto segments = parser.get<int>(ArgParseWrapper::SHORT_SEGMENTS_ARGUMENT);

    return std::make_shared<CircleGenerator>(radius, segments, VectorToVec3(origin), VectorToVec3(color));
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetCylinderGenerator_(argparse::ArgumentParser& parser) {
    const auto origin   = parser.get<std::vector<float>>(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT);
    const auto color    = parser.get<std::vector<float>>(ArgParseWrapper::SHORT_COLOR_ARGUMENT);
    const auto height   = parser.get<float>(ArgParseWrapper::SHORT_HEIGHT_ARGUMENT);
    const auto radius   = parser.get<float>(ArgParseWrapper::SHORT_RADIUS_ARGUMENT);
    const auto segments = parser.get<int>(ArgParseWrapper::SHORT_SEGMENTS_ARGUMENT);
    const auto slices   = parser.get<int>(ArgParseWrapper::SHORT_SLICES_ARGUMENT);

    return std::make_shared<CylinderGenerator>(height, radius, segments, slices, VectorToVec3(origin), VectorToVec3(color));
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetEllipseGenerator_(argparse::ArgumentParser& parser) {
    const auto origin   = parser.get<std::vector<float>>(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT);
    const auto color    = parser.get<std::vector<float>>(ArgParseWrapper::SHORT_COLOR_ARGUMENT);
    const auto a        = parser.get<float>(ArgParseWrapper::SHORT_A_PARAMETER_ARGUMENT);
    const auto b        = parser.get<float>(ArgParseWrapper::SHORT_B_PARAMETER_ARGUMENT);
    const auto segments = parser.get<int>(ArgParseWrapper::SHORT_SEGMENTS_ARGUMENT);

    return std::make_shared<EllipseGenerator>(a, b, segments, VectorToVec3(origin), VectorToVec3(color));
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetIcosahedronGenerator_(argparse::ArgumentParser& parser) {
    const auto origin = parser.get<std::vector<float>>(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT);
    const auto color  = parser.get<std::vector<float>>(ArgParseWrapper::SHORT_COLOR_ARGUMENT);
    const auto radius = parser.get<float>(ArgParseWrapper::SHORT_RADIUS_ARGUMENT);

    return std::make_shared<IcosahedronGenerator>(radius, VectorToVec3(origin), VectorToVec3(color));
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetIcosphereGenerator_(argparse::ArgumentParser& parser) {
    const auto origin     = parser.get<std::vector<float>>(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT);
    const auto color      = parser.get<std::vector<float>>(ArgParseWrapper::SHORT_COLOR_ARGUMENT);
    const auto radius     = parser.get<float>(ArgParseWrapper::SHORT_RADIUS_ARGUMENT);
    const auto iterations = parser.get<int>(ArgParseWrapper::SHORT_ITERATIONS_ARGUMENT);

    return std::make_shared<IcosphereGenerator>(radius, iterations, VectorToVec3(origin), VectorToVec3(color));
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetParallelepipedGenerator_(argparse::ArgumentParser& parser) {
    const auto origin = parser.get<std::vector<float>>(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT);
    const auto color  = parser.get<std::vector<float>>(ArgParseWrapper::SHORT_COLOR_ARGUMENT);
    const auto height = parser.get<float>(ArgParseWrapper::SHORT_HEIGHT_ARGUMENT);
    const auto width  = parser.get<float>(ArgParseWrapper::SHORT_WIDTH_ARGUMENT);
    const auto depth  = parser.get<float>(ArgParseWrapper::SHORT_DEPTH_ARGUMENT);

    return std::make_shared<ParallelepipedGenerator>(height, width, depth, VectorToVec3(origin), VectorToVec3(color));
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetRectangleGenerator_(argparse::ArgumentParser& parser) {
    const auto origin = parser.get<std::vector<float>>(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT);
    const auto color  = parser.get<std::vector<float>>(ArgParseWrapper::SHORT_COLOR_ARGUMENT);
    const auto height = parser.get<float>(ArgParseWrapper::SHORT_HEIGHT_ARGUMENT);
    const auto width  = parser.get<float>(ArgParseWrapper::SHORT_WIDTH_ARGUMENT);

    return std::make_shared<RectangleGenerator>(height, width, VectorToVec3(origin), VectorToVec3(color));
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetTorusGenerator_(argparse::ArgumentParser& parser) {
    const auto origin      = parser.get<std::vector<float>>(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT);
    const auto color       = parser.get<std::vector<float>>(ArgParseWrapper::SHORT_COLOR_ARGUMENT);
    const auto innerRadius = parser.get<float>(ArgParseWrapper::SHORT_INNER_RADIUS_ARGUMENT);
    const auto outerRadius = parser.get<float>(ArgParseWrapper::SHORT_OUTER_RADIUS_ARGUMENT);
    const auto slices      = parser.get<int>(ArgParseWrapper::SHORT_SLICES_ARGUMENT);
    const auto segments    = parser.get<int>(ArgParseWrapper::SHORT_SEGMENTS_ARGUMENT);

    return std::make_shared<TorusGenerator>(innerRadius, outerRadius, slices, segments, VectorToVec3(origin), VectorToVec3(color));
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetUvSphereGenerator_(argparse::ArgumentParser& parser) {
    const auto origin   = parser.get<std::vector<float>>(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT);
    const auto color    = parser.get<std::vector<float>>(ArgParseWrapper::SHORT_COLOR_ARGUMENT);
    const auto radius   = parser.get<float>(ArgParseWrapper::SHORT_RADIUS_ARGUMENT);
    const auto slices   = parser.get<int>(ArgParseWrapper::SHORT_SLICES_ARGUMENT);
    const auto segments = parser.get<int>(ArgParseWrapper::SHORT_SEGMENTS_ARGUMENT);

    return std::make_shared<UVSphereGenerator>(radius, slices, segments, VectorToVec3(origin), VectorToVec3(color));
}

void ArgParseWrapper::ConstructHelper_(char** argv, int argc) {
    this->argv_ = std::vector<std::string>(argc);
    for (int i = 0; auto & el : this->argv_) {
        el = argv[i++];
    }

    this->argumentParser_ = std::make_unique<argparse::ArgumentParser>(*argv);

    static std::vector<std::unique_ptr<argparse::ArgumentParser>> subparsers{};

    subparsers.emplace_back(std::move(this->CreateCircleParser_()));
    subparsers.emplace_back(std::move(this->CreateCylinderParser_()));
    subparsers.emplace_back(std::move(this->CreateEllipseParser_()));
    subparsers.emplace_back(std::move(this->CreateIcosahedronParser_()));
    subparsers.emplace_back(std::move(this->CreateIcosphereParser_()));
    subparsers.emplace_back(std::move(this->CreateParallelepipedParser_()));
    subparsers.emplace_back(std::move(this->CreateRectangleParser_()));
    subparsers.emplace_back(std::move(this->CreateTorusParser_()));
    subparsers.emplace_back(std::move(this->CreateUVSphereParser_()));

    for (auto& subparser : subparsers) {
        this->argumentParser_->add_subparser(*subparser);
    }

    this->argumentParser_->add_argument(
        ArgParseWrapper::SHORT_WINDOW_HEIGHT_ARGUMENT,
        ArgParseWrapper::LONG_WINDOW_HEIGHT_ARGUMENT)
        .help("Height of application window")
        .nargs(1).scan<'i', int>()
        .default_value(ArgParseWrapper::DEFAULT_WINDOW_HEIGHT_VALUE);

    this->argumentParser_->add_argument(
        ArgParseWrapper::SHORT_WINDOW_WIDTH_ARGUMENT,
        ArgParseWrapper::LONG_WINDOW_WIDTH_ARGUMENT)
        .help("Width of application window")
        .nargs(1).scan<'i', int>()
        .default_value(ArgParseWrapper::DEFAULT_WINDOW_WIDTH_VALUE);

    this->argumentParser_->add_argument(
        ArgParseWrapper::SHORT_WINDOW_NAME_ARGUMENT,
        ArgParseWrapper::LONG_WINDOW_NAME_ARGUMENT)
        .help("Title of application window")
        .default_value(ArgParseWrapper::DEFAULT_WINDOW_NAME_VALUE);

    this->argumentParser_->add_argument(
        ArgParseWrapper::SHORT_CAMERA_POSITION_ARGUMENT,
        ArgParseWrapper::LONG_CAMERA_POSITION_ARGUMENT)
        .help("Initial camera position")
        .nargs(3).scan<'f', float>()
        .default_value(ArgParseWrapper::DEFAULT_CAMERA_POSITION_VALUE);

    this->argumentParser_->add_argument(
        ArgParseWrapper::SHORT_CAMERA_TARET_ARGUMENT,
        ArgParseWrapper::LONG_CAMERA_TARET_ARGUMENT)
        .help("Initial camera target")
        .nargs(3).scan<'f', float>()
        .default_value(ArgParseWrapper::DEFAULT_CAMERA_TARET_VALUE);

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

    this->argumentParser_->add_argument(
        ArgParseWrapper::SHORT_VIEWPORT_NEAR_Z_ARGUMENT,
        ArgParseWrapper::LONG_VIEWPORT_NEAR_Z_ARGUMENT)
        .help("Distance to the nearest viewport plane")
        .nargs(1).scan<'f', float>()
        .default_value(ArgParseWrapper::DEFAULT_VIEWPORT_NEAR_Z_VALUE);

    this->argumentParser_->add_argument(
        ArgParseWrapper::SHORT_VIEWPORT_FAR_Z_ARGUMENT,
        ArgParseWrapper::LONG_VIEWPORT_FAR_Z_ARGUMENT)
        .help("Distance to the farthest viewport plane")
        .nargs(1).scan<'f', float>()
        .default_value(ArgParseWrapper::DEFAULT_VIEWPORT_FAR_Z_VALUE);

    this->argumentParser_->add_argument(
        ArgParseWrapper::SHORT_VIEWPORT_TOP_LEFT_ARGUMENT,
        ArgParseWrapper::LONG_VIEWPORT_TOP_LEFT_ARGUMENT)
        .help("Viewport top left point")
        .nargs(2).scan<'f', float>()
        .default_value(ArgParseWrapper::DEFAULT_VIEWPORT_TOP_LEFT_VALUE);

    this->argumentParser_->add_argument(
        ArgParseWrapper::SHORT_VIEWPORT_BOTTOM_RIGHT_ARGUMENT,
        ArgParseWrapper::LONG_VIEWPORT_BOTTOM_RIGHT_ARGUMENT)
        .help("Viewport bottom right point")
        .nargs(2).scan<'f', float>()
        .default_value(ArgParseWrapper::DEFAULT_VIEWPORT_BOTTOM_RIGHT_VALUE);

    this->argumentParser_->add_argument(
        ArgParseWrapper::SHORT_VIEWPORT_FOV_ARGUMENT,
        ArgParseWrapper::LONG_VIEWPORT_FOV_ARGUMENT)
        .help("Angle of observable field camera view in degrees")
        .nargs(1).scan<'f', float>()
        .default_value(ArgParseWrapper::DEFAULT_VIEWPORT_FOV_VALUE);
}

std::unique_ptr<argparse::ArgumentParser> ArgParseWrapper::CreateCircleParser_() {
    auto parser = std::make_unique<argparse::ArgumentParser>(ArgParseWrapper::CIRCLE_COMMAND);

    parser->add_description("Generate circle mesh");

    this->AddOriginArgument_(parser);
    this->AddColorArgument_(parser);
    this->AddRadiusArgument_(parser);
    this->AddSegmentsArgument_(parser);

    return parser;
}

std::unique_ptr<argparse::ArgumentParser> ArgParseWrapper::CreateCylinderParser_() {
    auto parser = std::make_unique<argparse::ArgumentParser>(ArgParseWrapper::CYLINDER_COMMAND);

    parser->add_description("Generate cylinder mesh");

    this->AddOriginArgument_(parser);
    this->AddColorArgument_(parser);
    this->AddHeightArgument_(parser);
    this->AddRadiusArgument_(parser);
    this->AddSegmentsArgument_(parser);
    this->AddSlicesArgument_(parser);

    return parser;
}

std::unique_ptr<argparse::ArgumentParser> ArgParseWrapper::CreateEllipseParser_() {
    auto parser = std::make_unique<argparse::ArgumentParser>(ArgParseWrapper::ELLIPSE_COMMAND);

    parser->add_description("Generate ellipse mesh");

    this->AddOriginArgument_(parser);
    this->AddColorArgument_(parser);
    this->AddAArgument_(parser);
    this->AddBArgument_(parser);
    this->AddSegmentsArgument_(parser);

    return parser;
}

std::unique_ptr<argparse::ArgumentParser> ArgParseWrapper::CreateIcosahedronParser_() {
    auto parser = std::make_unique<argparse::ArgumentParser>(ArgParseWrapper::ICOSAHEDRON_COMMAND);

    parser->add_description("Generate icosahedron mesh");

    this->AddOriginArgument_(parser);
    this->AddColorArgument_(parser);
    this->AddRadiusArgument_(parser);

    return parser;
}

std::unique_ptr<argparse::ArgumentParser> ArgParseWrapper::CreateIcosphereParser_() {
    auto parser = std::make_unique<argparse::ArgumentParser>(ArgParseWrapper::ICOSPHERE_COMMAND);

    parser->add_description("Generate icosphere mesh");

    this->AddOriginArgument_(parser);
    this->AddColorArgument_(parser);
    this->AddRadiusArgument_(parser);
    this->AddIterationsArgument_(parser);

    return parser;
}

std::unique_ptr<argparse::ArgumentParser> ArgParseWrapper::CreateParallelepipedParser_() {
    auto parser = std::make_unique<argparse::ArgumentParser>(ArgParseWrapper::PARALLELEPIPED_COMMAND);

    parser->add_description("Generate parallelepiped mesh");

    this->AddOriginArgument_(parser);
    this->AddColorArgument_(parser);
    this->AddHeightArgument_(parser);
    this->AddWidthArgument_(parser);
    this->AddDepthArgument_(parser);

    return parser;
}

std::unique_ptr<argparse::ArgumentParser> ArgParseWrapper::CreateRectangleParser_() {
    auto parser = std::make_unique<argparse::ArgumentParser>(ArgParseWrapper::RECTANGLE_COMMAND);

    parser->add_description("Generate rectangle mesh");

    this->AddOriginArgument_(parser);
    this->AddColorArgument_(parser);
    this->AddHeightArgument_(parser);
    this->AddWidthArgument_(parser);

    return parser;
}

std::unique_ptr<argparse::ArgumentParser> ArgParseWrapper::CreateTorusParser_() {
    auto parser = std::make_unique<argparse::ArgumentParser>(ArgParseWrapper::TORUS_COMMAND);

    parser->add_description("Generate torus mesh");

    this->AddOriginArgument_(parser);
    this->AddColorArgument_(parser);
    this->AddInnerRadiusArgument_(parser);
    this->AddOuterRadiusArgument_(parser);
    this->AddSlicesArgument_(parser);
    this->AddSegmentsArgument_(parser);

    return parser;
}

std::unique_ptr<argparse::ArgumentParser> ArgParseWrapper::CreateUVSphereParser_() {
    auto parser = std::make_unique<argparse::ArgumentParser>(ArgParseWrapper::UV_SPHERE_COMMAND);

    parser->add_description("Generate uv-sphere mesh");

    this->AddOriginArgument_(parser);
    this->AddColorArgument_(parser);
    this->AddRadiusArgument_(parser);
    this->AddSlicesArgument_(parser);
    this->AddSegmentsArgument_(parser);

    return parser;
}
