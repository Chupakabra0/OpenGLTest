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

// TODO: replace all literals with static consts

bool ArgParseWrapper::ParseAllArgs() {
    try {
        this->argumentParser_->parse_args(this->argv_);
    }
    catch (const std::exception& exception) {
        if (this->argumentParser_->is_subcommand_used("circle")) {
            std::cout << this->argumentParser_->at<argparse::ArgumentParser>("circle");
        }
        else if (this->argumentParser_->is_subcommand_used("cylinder")) {
            std::cout << this->argumentParser_->at<argparse::ArgumentParser>("cylinder");
        }
        else if (this->argumentParser_->is_subcommand_used("ellipse")) {
            std::cout << this->argumentParser_->at<argparse::ArgumentParser>("ellipse");
        }
        else if (this->argumentParser_->is_subcommand_used("icosahedron")) {
            std::cout << this->argumentParser_->at<argparse::ArgumentParser>("icosahedron");
        }
        else if (this->argumentParser_->is_subcommand_used("icosphere")) {
            std::cout << this->argumentParser_->at<argparse::ArgumentParser>("icosphere");
        }
        else if (this->argumentParser_->is_subcommand_used("parallelepiped")) {
            std::cout << this->argumentParser_->at<argparse::ArgumentParser>("parallelepiped");
        }
        else if (this->argumentParser_->is_subcommand_used("rectangle")) {
            std::cout << this->argumentParser_->at<argparse::ArgumentParser>("rectangle");
        }
        else if (this->argumentParser_->is_subcommand_used("torus")) {
            std::cout << this->argumentParser_->at<argparse::ArgumentParser>("torus");
        }
        else if (this->argumentParser_->is_subcommand_used("uv-sphere")) {
            std::cout << this->argumentParser_->at<argparse::ArgumentParser>("uv-sphere");
        }
        else {
            std::cout << *this->argumentParser_;
        }

        return false;
    }

    return true;
}

ApplicationConfig ArgParseWrapper::GetAppConfig() {
    ApplicationConfig config {
        .WINDOW_HEIGHT         = this->argumentParser_->get<int>("-wh"),
        .WINDOW_WIDTH          = this->argumentParser_->get<int>("-ww"),
        .WINDOW_NAME           = this->argumentParser_->get<std::string>("-wn"),
        .CAMERA_POSITION       = this->argumentParser_->get<glm::vec3>("-cp"),
        .CAMERA_TARGET         = this->argumentParser_->get<glm::vec3>("-ct"),
        .CAMERA_AXIS_X         = this->argumentParser_->get<glm::vec3>("-cx"),
        .CAMERA_AXIS_Y         = this->argumentParser_->get<glm::vec3>("-cy"),
        .CAMERA_AXIS_Z         = this->argumentParser_->get<glm::vec3>("-cz"),
        .VIEWPORT_TOP_LEFT     = this->argumentParser_->get<glm::vec2>("-vtl"),
        .VIEWPORT_BOTTOM_RIGHT = this->argumentParser_->get<glm::vec2>("-vbr"),
        .VIEWPORT_FOV          = this->argumentParser_->get<float>("-f"),
        .VIEWPORT_NEAR_Z       = this->argumentParser_->get<float>("-vn"),
        .VIEWPORT_FAR_Z        = this->argumentParser_->get<float>("-vf"),
        .MESH_GENERATOR        = this->GetMeshGenerator_()
    };

    return config;
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetMeshGenerator_() {
    std::shared_ptr<MeshGenerator> result{};
    
    if (this->argumentParser_->is_subcommand_used("circle")) {
        result = this->GetCircleGenerator_();
    }
    else if (this->argumentParser_->is_subcommand_used("cylinder")) {
        result = this->GetCylinderGenerator_();
    }
    else if (this->argumentParser_->is_subcommand_used("ellipse")) {
        result = this->GetEllipseGenerator_();
    }
    else if (this->argumentParser_->is_subcommand_used("icosahedron")) {
        result = this->GetIcosahedronGenerator_();
    }
    else if (this->argumentParser_->is_subcommand_used("icosphere")) {
        result = this->GetIcosphereGenerator_();
    }
    else if (this->argumentParser_->is_subcommand_used("parallelepiped")) {
        result = this->GetParallelepipedGenerator_();
    }
    else if (this->argumentParser_->is_subcommand_used("rectangle")) {
        result = this->GetRectangleGenerator_();
    }
    else if (this->argumentParser_->is_subcommand_used("torus")) {
        result = this->GetTorusGenerator_();
    }
    else if (this->argumentParser_->is_subcommand_used("uv-sphere")) {
        result = this->GetUvSphereGenerator_();
    }

    return result;
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetCircleGenerator_() {
    const glm::vec3 origin = this->argumentParser_->at<glm::vec3>("-o");
    const glm::vec3 color  = this->argumentParser_->at<glm::vec3>("-c");
    const float radius     = this->argumentParser_->at<float>("-r");
    const int segments     = this->argumentParser_->at<int>("-se");

    return std::make_shared<CircleGenerator>(radius, segments, origin, color);
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetCylinderGenerator_() {
    const glm::vec3 origin = this->argumentParser_->at<glm::vec3>("-o");
    const glm::vec3 color  = this->argumentParser_->at<glm::vec3>("-c");
    const float height     = this->argumentParser_->at<float>("-h");
    const float radius     = this->argumentParser_->at<float>("-r");
    const int segments     = this->argumentParser_->at<int>("-se");
    const int slices       = this->argumentParser_->at<int>("-sl");

    return std::make_shared<CylinderGenerator>(height, radius, segments, slices, origin, color);
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetEllipseGenerator_() {
    const glm::vec3 origin = this->argumentParser_->at<glm::vec3>("-o");
    const glm::vec3 color  = this->argumentParser_->at<glm::vec3>("-c");
    const float a          = this->argumentParser_->at<float>("-a");
    const float b          = this->argumentParser_->at<float>("-b");
    const int segments     = this->argumentParser_->at<int>("-se");

    return std::make_shared<EllipseGenerator>(a, b, segments, origin, color);
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetIcosahedronGenerator_() {
    const glm::vec3 origin = this->argumentParser_->at<glm::vec3>("-o");
    const glm::vec3 color  = this->argumentParser_->at<glm::vec3>("-c");
    const float radius     = this->argumentParser_->at<float>("-r");

    return std::make_shared<IcosahedronGenerator>(radius, origin, color);
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetIcosphereGenerator_() {
    const glm::vec3 origin = this->argumentParser_->at<glm::vec3>("-o");
    const glm::vec3 color  = this->argumentParser_->at<glm::vec3>("-c");
    const float radius     = this->argumentParser_->at<float>("-r");
    const int iterations   = this->argumentParser_->at<float>("-i");

    return std::make_shared<IcosphereGenerator>(radius, iterations, origin, color);
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetParallelepipedGenerator_() {
    const glm::vec3 origin = this->argumentParser_->at<glm::vec3>("-o");
    const glm::vec3 color  = this->argumentParser_->at<glm::vec3>("-c");
    const float height     = this->argumentParser_->at<float>("-h");
    const float width      = this->argumentParser_->at<float>("-w");
    const float depth      = this->argumentParser_->at<float>("-d");

    return std::make_shared<ParallelepipedGenerator>(height, width, depth, origin, color);
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetRectangleGenerator_() {
    const glm::vec3 origin = this->argumentParser_->at<glm::vec3>("-o");
    const glm::vec3 color  = this->argumentParser_->at<glm::vec3>("-c");
    const float height     = this->argumentParser_->at<float>("-h");
    const float width      = this->argumentParser_->at<float>("-w");

    return std::make_shared<RectangleGenerator>(height, width, origin, color);
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetTorusGenerator_() {
    const glm::vec3 origin  = this->argumentParser_->at<glm::vec3>("-o");
    const glm::vec3 color   = this->argumentParser_->at<glm::vec3>("-c");
    const float innerRadius = this->argumentParser_->at<float>("-ir");
    const float outerRadius = this->argumentParser_->at<float>("-or");
    const int slices        = this->argumentParser_->at<float>("-sl");
    const int segments      = this->argumentParser_->at<float>("-se");

    return std::make_shared<TorusGenerator>(innerRadius, outerRadius, slices, segments, origin, color);
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetTorusGenerator_() {
    const glm::vec3 origin = this->argumentParser_->at<glm::vec3>("-o");
    const glm::vec3 color  = this->argumentParser_->at<glm::vec3>("-c");
    const float radius     = this->argumentParser_->at<float>("-r");
    const int slices       = this->argumentParser_->at<float>("-sl");
    const int segments     = this->argumentParser_->at<float>("-se");

    return std::make_shared<UVSphereGenerator>(radius, slices, segments, origin, color);
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

    this->argumentParser_->add_argument("-wh", "--window-height")
        .help("Height of application window")
        .nargs(1).scan<'i', int>()
        .default_value(1080);

    this->argumentParser_->add_argument("-ww", "--window-width")
        .help("Width of application window")
        .nargs(1).scan<'i', int>()
        .default_value(1920);

    this->argumentParser_->add_argument("-wn", "--window-name")
        .help("Title of application window")
        .nargs(1)
        .default_value("OpenGL Test");

    this->argumentParser_->add_argument("-cp", "--camera-position")
        .help("Initial camera position")
        .nargs(3).scan<'f', float>()
        .default_value(glm::vec3{ 0.0f, 0.0f, 500.0f });

    this->argumentParser_->add_argument("-ct", "--camera-target")
        .help("Initial camera target")
        .nargs(3).scan<'f', float>()
        .default_value(glm::vec3{ 0.0f, 0.0f, 0.0f });

    this->argumentParser_->add_argument("-cx", "--camera-axis-x")
        .help("Initial basis Ox vector of camera")
        .nargs(3).scan<'f', float>()
        .default_value(glm::vec3{ 1.0f, 0.0f, 0.0f });

    this->argumentParser_->add_argument("-cy", "--camera-axis-y")
        .help("Initial basis Oy vector of camera")
        .nargs(3).scan<'f', float>()
        .default_value(glm::vec3{ 0.0f, 1.0f, 0.0f });

    this->argumentParser_->add_argument("-cz", "--camera-axis-z")
        .help("Initial basis Oz vector of camera")
        .nargs(3).scan<'f', float>()
        .default_value(glm::vec3{ 0.0f, 0.0f, -1.0f });

    this->argumentParser_->add_argument("-vn", "--viewport-near")
        .help("Distance to the nearest viewport plane")
        .nargs(1).scan<'f', float>()
        .default_value(0.1f);

    this->argumentParser_->add_argument("-vf", "--viewport-far")
        .help("Distance to the farthest viewport plane")
        .nargs(1).scan<'f', float>()
        .default_value(1000.0f);

    this->argumentParser_->add_argument("-vtl", "--viewport-tl")
        .help("Viewport top left point")
        .nargs(2).scan<'f', float>()
        .default_value(glm::zero<glm::vec2>());

    this->argumentParser_->add_argument("-vbr", "--viewport-br")
        .help("Viewport bottom right point")
        .nargs(2).scan<'f', float>()
        .default_value(
            glm::vec2{
                this->argumentParser_->get<float>("-ww"),
                this->argumentParser_->get<float>("-wh")
            }
        );

    this->argumentParser_->add_argument("-f", "--fov")
        .help("Angle of observable field camera view in degrees")
        .nargs(1).scan<'f', float>()
        .default_value(45.0f);
}

std::unique_ptr<argparse::ArgumentParser> ArgParseWrapper::CreateCircleParser_() {
    auto parser = std::make_unique<argparse::ArgumentParser>("circle");

    parser->add_description("Generate circle mesh");

    this->AddOriginArgument_(parser);
    this->AddColorArgument_(parser);
    this->AddRadiusArgument_(parser);
    this->AddSegmentsArgument_(parser);

    return parser;
}

std::unique_ptr<argparse::ArgumentParser> ArgParseWrapper::CreateCylinderParser_() {
    auto parser = std::make_unique<argparse::ArgumentParser>("cylinder");

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
    auto parser = std::make_unique<argparse::ArgumentParser>("ellipse");

    parser->add_description("Generate ellipse mesh");

    this->AddOriginArgument_(parser);
    this->AddColorArgument_(parser);
    this->AddAArgument_(parser);
    this->AddBArgument_(parser);
    this->AddSegmentsArgument_(parser);

    return parser;
}

std::unique_ptr<argparse::ArgumentParser> ArgParseWrapper::CreateIcosahedronParser_() {
    auto parser = std::make_unique<argparse::ArgumentParser>("icosahedron");

    parser->add_description("Generate icosahedron mesh");

    this->AddOriginArgument_(parser);
    this->AddColorArgument_(parser);
    this->AddRadiusArgument_(parser);

    return parser;
}

std::unique_ptr<argparse::ArgumentParser> ArgParseWrapper::CreateIcosphereParser_() {
    auto parser = std::make_unique<argparse::ArgumentParser>("icosphere");

    parser->add_description("Generate icosphere mesh");

    this->AddOriginArgument_(parser);
    this->AddColorArgument_(parser);
    this->AddRadiusArgument_(parser);
    this->AddIterationsArgument_(parser);

    return parser;
}

std::unique_ptr<argparse::ArgumentParser> ArgParseWrapper::CreateParallelepipedParser_() {
    auto parser = std::make_unique<argparse::ArgumentParser>("parallelepiped");

    parser->add_description("Generate parallelepiped mesh");

    this->AddOriginArgument_(parser);
    this->AddColorArgument_(parser);
    this->AddHeightArgument_(parser);
    this->AddWidthArgument_(parser);
    this->AddDepthArgument_(parser);

    return parser;
}

std::unique_ptr<argparse::ArgumentParser> ArgParseWrapper::CreateRectangleParser_() {
    auto parser = std::make_unique<argparse::ArgumentParser>("rectangle");

    parser->add_description("Generate rectangle mesh");

    this->AddOriginArgument_(parser);
    this->AddColorArgument_(parser);
    this->AddHeightArgument_(parser);
    this->AddWidthArgument_(parser);

    return parser;
}

std::unique_ptr<argparse::ArgumentParser> ArgParseWrapper::CreateTorusParser_() {
    auto parser = std::make_unique<argparse::ArgumentParser>("torus");

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
    auto parser = std::make_unique<argparse::ArgumentParser>("uv-sphere");

    parser->add_description("Generate uv-sphere mesh");

    this->AddOriginArgument_(parser);
    this->AddColorArgument_(parser);
    this->AddRadiusArgument_(parser);
    this->AddSlicesArgument_(parser);
    this->AddSegmentsArgument_(parser);

    return parser;
}
