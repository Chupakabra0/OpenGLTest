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
#include "MainParseBuilder.hpp"
#include "CircleMeshParseBuilder.hpp"
#include "CylinderMeshParseBuilder.hpp"
#include "EllipseMeshParseBuilder.hpp"
#include "RectangleMeshParseBuilder.hpp"
#include "ParallelepipedMeshParseBuilder.hpp"
#include "IcosahedronMeshParseBuilder.hpp"
#include "TorusMeshParseBuilder.hpp"
#include "IcosphereMeshParseBuilder.hpp"
#include "UvSphereMeshParseBuilder.hpp"

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

ArgParseWrapper::ArgParseWrapper(char** argv, int argc) {
    this->ConstructHelper_(argv, argc);
}

ArgParseWrapper::~ArgParseWrapper() {
    for (auto& el : this->meshParseBuilders_) {
        delete el;
    }
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
    catch (const std::exception&) {
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
        result = this->GetCircleGenerator_();
    }
    else if (this->argumentParser_->is_subcommand_used(ArgParseWrapper::CYLINDER_COMMAND)) {
        result = this->GetCylinderGenerator_();
    }
    else if (this->argumentParser_->is_subcommand_used(ArgParseWrapper::ELLIPSE_COMMAND)) {
        result = this->GetEllipseGenerator_();
    }
    else if (this->argumentParser_->is_subcommand_used(ArgParseWrapper::ICOSAHEDRON_COMMAND)) {
        result = this->GetIcosahedronGenerator_();
    }
    else if (this->argumentParser_->is_subcommand_used(ArgParseWrapper::ICOSPHERE_COMMAND)) {
        result = this->GetIcosphereGenerator_();
    }
    else if (this->argumentParser_->is_subcommand_used(ArgParseWrapper::PARALLELEPIPED_COMMAND)) {
        result = this->GetParallelepipedGenerator_();
    }
    else if (this->argumentParser_->is_subcommand_used(ArgParseWrapper::RECTANGLE_COMMAND)) {
        result = this->GetRectangleGenerator_();
    }
    else if (this->argumentParser_->is_subcommand_used(ArgParseWrapper::TORUS_COMMAND)) {
        result = this->GetTorusGenerator_();
    }
    else if (this->argumentParser_->is_subcommand_used(ArgParseWrapper::UV_SPHERE_COMMAND)) {
        result = this->GetUvSphereGenerator_();
    }

    return result;
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetCircleGenerator_() {
    const auto origin =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::CIRCLE_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT);
    const auto color =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::CIRCLE_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_COLOR_ARGUMENT);
    const auto radius = this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::CIRCLE_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_RADIUS_ARGUMENT);
    const auto segments = this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::CIRCLE_COMMAND)
            .get<int>(ArgParseWrapper::SHORT_SEGMENTS_ARGUMENT);

    return std::make_shared<CircleGenerator>(radius, segments, VectorToVec3(origin), VectorToVec3(color));
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetCylinderGenerator_() {
    const auto origin =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::CYLINDER_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT);
    const auto color =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::CYLINDER_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_COLOR_ARGUMENT);
    const auto height =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::CYLINDER_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_HEIGHT_ARGUMENT);
    const auto radius =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::CYLINDER_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_RADIUS_ARGUMENT);
    const auto segments =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::CYLINDER_COMMAND)
            .get<int>(ArgParseWrapper::SHORT_SEGMENTS_ARGUMENT);
    const auto slices =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::CYLINDER_COMMAND)
            .get<int>(ArgParseWrapper::SHORT_SLICES_ARGUMENT);

    return std::make_shared<CylinderGenerator>(height, radius, segments, slices, VectorToVec3(origin), VectorToVec3(color));
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetEllipseGenerator_() {
    const auto origin =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::ELLIPSE_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT);
    const auto color =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::ELLIPSE_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_COLOR_ARGUMENT);
    const auto a =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::ELLIPSE_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_A_PARAMETER_ARGUMENT);
    const auto b =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::ELLIPSE_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_B_PARAMETER_ARGUMENT);
    const auto segments =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::ELLIPSE_COMMAND)
            .get<int>(ArgParseWrapper::SHORT_SEGMENTS_ARGUMENT);

    return std::make_shared<EllipseGenerator>(a, b, segments, VectorToVec3(origin), VectorToVec3(color));
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetIcosahedronGenerator_() {
    const auto origin =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::ICOSAHEDRON_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT);
    const auto color =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::ICOSAHEDRON_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_COLOR_ARGUMENT);
    const auto radius =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::ICOSAHEDRON_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_RADIUS_ARGUMENT);

    return std::make_shared<IcosahedronGenerator>(radius, VectorToVec3(origin), VectorToVec3(color));
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetIcosphereGenerator_() {
    const auto origin =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::ICOSPHERE_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT);
    const auto color =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::ICOSPHERE_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_COLOR_ARGUMENT);
    const auto radius =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::ICOSPHERE_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_RADIUS_ARGUMENT);
    const auto iterations =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::ICOSPHERE_COMMAND)
            .get<int>(ArgParseWrapper::SHORT_ITERATIONS_ARGUMENT);

    return std::make_shared<IcosphereGenerator>(radius, iterations, VectorToVec3(origin), VectorToVec3(color));
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetParallelepipedGenerator_() {
    const auto origin =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::PARALLELEPIPED_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT);
    const auto color =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::PARALLELEPIPED_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_COLOR_ARGUMENT);
    const auto height =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::PARALLELEPIPED_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_HEIGHT_ARGUMENT);
    const auto width =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::PARALLELEPIPED_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_WIDTH_ARGUMENT);
    const auto depth =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::PARALLELEPIPED_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_DEPTH_ARGUMENT);

    return std::make_shared<ParallelepipedGenerator>(height, width, depth, VectorToVec3(origin), VectorToVec3(color));
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetRectangleGenerator_() {
    const auto origin =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::RECTANGLE_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT);
    const auto color  =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::RECTANGLE_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_COLOR_ARGUMENT);
    const auto height =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::RECTANGLE_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_HEIGHT_ARGUMENT);
    const auto width =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::RECTANGLE_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_WIDTH_ARGUMENT);

    return std::make_shared<RectangleGenerator>(height, width, VectorToVec3(origin), VectorToVec3(color));
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetTorusGenerator_() {
    const auto origin =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::TORUS_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT);
    const auto color =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::TORUS_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_COLOR_ARGUMENT);
    const auto innerRadius =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::TORUS_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_INNER_RADIUS_ARGUMENT);
    const auto outerRadius =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::TORUS_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_OUTER_RADIUS_ARGUMENT);
    const auto slices =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::TORUS_COMMAND)
            .get<int>(ArgParseWrapper::SHORT_SLICES_ARGUMENT);
    const auto segments =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::TORUS_COMMAND)
            .get<int>(ArgParseWrapper::SHORT_SEGMENTS_ARGUMENT);

    return std::make_shared<TorusGenerator>(innerRadius, outerRadius, slices, segments, VectorToVec3(origin), VectorToVec3(color));
}

std::shared_ptr<MeshGenerator> ArgParseWrapper::GetUvSphereGenerator_() {
    const auto origin =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::UV_SPHERE_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT);
    const auto color =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::UV_SPHERE_COMMAND)
            .get<std::vector<float>>(ArgParseWrapper::SHORT_COLOR_ARGUMENT);
    const auto radius =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::UV_SPHERE_COMMAND)
            .get<float>(ArgParseWrapper::SHORT_RADIUS_ARGUMENT);
    const auto slices =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::UV_SPHERE_COMMAND)
            .get<int>(ArgParseWrapper::SHORT_SLICES_ARGUMENT);
    const auto segments =
        this->argumentParser_->at<argparse::ArgumentParser>(ArgParseWrapper::UV_SPHERE_COMMAND)
            .get<int>(ArgParseWrapper::SHORT_SEGMENTS_ARGUMENT);

    return std::make_shared<UVSphereGenerator>(radius, slices, segments, VectorToVec3(origin), VectorToVec3(color));
}

void ArgParseWrapper::ConstructHelper_(char** argv, int argc) {
    this->argv_ = std::vector<std::string>(argc);
    for (int i = 0; auto & el : this->argv_) {
        el = argv[i++];
    }

    this->argumentParser_ = MainParseBuilder(this->argv_.front()).GetUniqueProduct();
    this->InitMeshParseBuilders_();

    for (int i = 0; auto & builder : this->meshParseBuilders_) {
        this->subcomands_.emplace_back(std::move(builder->GetUniqueProduct()));
        this->argumentParser_->add_subparser(*this->subcomands_[i++]);
    }
}

void ArgParseWrapper::InitMeshParseBuilders_() {
    this->meshParseBuilders_.emplace_back(new CircleMeshParseBuilder());
    this->meshParseBuilders_.emplace_back(new CylinderMeshParseBuilder());
    this->meshParseBuilders_.emplace_back(new EllipseMeshParseBuilder());
    this->meshParseBuilders_.emplace_back(new RectangleMeshParseBuilder());
    this->meshParseBuilders_.emplace_back(new ParallelepipedMeshParseBuilder());
    this->meshParseBuilders_.emplace_back(new IcosahedronMeshParseBuilder());
    this->meshParseBuilders_.emplace_back(new TorusMeshParseBuilder());
    this->meshParseBuilders_.emplace_back(new IcosphereMeshParseBuilder());
    this->meshParseBuilders_.emplace_back(new UvSphereMeshParseBuilder());
}
