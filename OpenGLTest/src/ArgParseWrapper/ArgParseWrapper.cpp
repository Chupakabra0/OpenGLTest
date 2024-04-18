#include "ArgParseWrapper/ArgParseWrapper.hpp"

#include <ranges>

#include "ApplicationConfig/ApplicationConfig.hpp"

#include "ArgParseBuilder/CircleMeshParseBuilder/CircleMeshParseBuilder.hpp"
#include "ArgParseBuilder/CylinderMeshParseBuilder/CylinderMeshParseBuilder.hpp"
#include "ArgParseBuilder/EllipseMeshParseBuilder/EllipseMeshParseBuilder.hpp"
#include "ArgParseBuilder/IcosahedronMeshParseBuilder/IcosahedronMeshParseBuilder.hpp"
#include "ArgParseBuilder/IcosphereMeshParseBuilder/IcosphereMeshParseBuilder.hpp"
#include "ArgParseBuilder/MainParseBuilder/MainParseBuilder.hpp"
#include "ArgParseBuilder/ParallelepipedMeshParseBuilder/ParallelepipedMeshParseBuilder.hpp"
#include "ArgParseBuilder/RectangleMeshParseBuilder/RectangleMeshParseBuilder.hpp"
#include "ArgParseBuilder/TorusMeshParseBuilder/TorusMeshParseBuilder.hpp"
#include "ArgParseBuilder/UvSphereMeshParseBuilder/UvSphereMeshParseBuilder.hpp"
#include "ArgParseMeshGeneratorCreator/IArgParseMeshGeneratorCreator.hpp"

#include "ArgParseMeshGeneratorCreator/CircleMeshGeneratorCreator/CircleMeshGeneratorCreator.hpp"
#include "ArgParseMeshGeneratorCreator/CylinderMeshGeneratorCreator/CylinderMeshGeneratorCreator.hpp"
#include "ArgParseMeshGeneratorCreator/EllipseMeshGeneratorCreator/EllipseMeshGeneratorCreator.hpp"
#include "ArgParseMeshGeneratorCreator/IcosahedronMeshGeneratorCreator/IcosahedronMeshGeneratorCreator.hpp"
#include "ArgParseMeshGeneratorCreator/IcosphereMeshGeneratorCreator/IcosphereMeshGeneratorCreator.hpp"
#include "ArgParseMeshGeneratorCreator/ParallelepipedMeshGeneratorCreator/ParallelepipedMeshGeneratorCreator.hpp"
#include "ArgParseMeshGeneratorCreator/RectangleMeshGeneratorCreator/RectangleMeshGeneratorCreator.hpp"
#include "ArgParseMeshGeneratorCreator/TorusMeshGeneratorCreator/TorusMeshGeneratorCreator.hpp"
#include "ArgParseMeshGeneratorCreator/UvSphereMeshGeneratorCreator/UvSphereMeshGeneratorCreator.hpp"

#include "MeshGeneratorFactory/GenericMeshGeneratorFactory/GenericMeshGeneratorFactory.hpp"

const std::vector<std::string> ArgParseWrapper::COMMAND_ARRAY = {
    ArgParseWrapper::CIRCLE_COMMAND,
    ArgParseWrapper::CYLINDER_COMMAND,
    ArgParseWrapper::ELLIPSE_COMMAND,
    ArgParseWrapper::ICOSAHEDRON_COMMAND,
    ArgParseWrapper::ICOSPHERE_COMMAND,
    ArgParseWrapper::PARALLELEPIPED_COMMAND,
    ArgParseWrapper::RECTANGLE_COMMAND,
    ArgParseWrapper::TORUS_COMMAND,
    ArgParseWrapper::UV_SPHERE_COMMAND
};

const std::string ArgParseWrapper::DEFAULT_WINDOW_NAME_VALUE                  = "Test OpenGL";
const std::vector<float> ArgParseWrapper::DEFAULT_CAMERA_POSITION_VALUE       = std::vector{0.0f, 0.0f, 500.0f};
const std::vector<float> ArgParseWrapper::DEFAULT_CAMERA_TARET_VALUE          = std::vector{0.0f, 0.0f, 0.0f};
const std::vector<float> ArgParseWrapper::DEFAULT_CAMERA_AXIS_X_VALUE         = std::vector{1.0f, 0.0f, 0.0f};
const std::vector<float> ArgParseWrapper::DEFAULT_CAMERA_AXIS_Y_VALUE         = std::vector{0.0f, 1.0f, 0.0f};
const std::vector<float> ArgParseWrapper::DEFAULT_CAMERA_AXIS_Z_VALUE         = std::vector{0.0f, 0.0f, -1.0f};
const std::vector<float> ArgParseWrapper::DEFAULT_VIEWPORT_TOP_LEFT_VALUE     = std::vector{0.0f, 0.0f};
const std::vector<float> ArgParseWrapper::DEFAULT_VIEWPORT_BOTTOM_RIGHT_VALUE = std::vector{
    static_cast<float>(ArgParseWrapper::DEFAULT_WINDOW_WIDTH_VALUE), static_cast<float>(ArgParseWrapper::DEFAULT_WINDOW_HEIGHT_VALUE)
};

ArgParseWrapper::ArgParseWrapper(char** argv, int argc) {
    this->ConstructHelper_(argv, argc);
}

bool ArgParseWrapper::ParseAllArgs() const {
    try {
        this->argumentParser_->parse_args(this->argv_);
    
        for (auto& command : ArgParseWrapper::COMMAND_ARRAY) {
            if (this->argumentParser_->is_subcommand_used(command)) {
                return true;
            }
        }
    }
    catch (const std::exception&) {
        for (auto& command : ArgParseWrapper::COMMAND_ARRAY) {
            if (this->argumentParser_->is_subcommand_used(command)) {
                std::cout << this->argumentParser_->at<argparse::ArgumentParser>(command);
                
                return false;
            }
        }
    }

    std::cout << *this->argumentParser_;

    return false;
}

ApplicationConfig ArgParseWrapper::GetAppConfig() const {
    const auto cameraPositionTemp  = this->argumentParser_->get<std::vector<float>>(ArgParseWrapper::SHORT_CAMERA_POSITION_ARGUMENT);
    const auto cameraTargetTemp    = this->argumentParser_->get<std::vector<float>>(ArgParseWrapper::SHORT_CAMERA_TARET_ARGUMENT);
    const auto cameraAxisX         = this->argumentParser_->get<std::vector<float>>(ArgParseWrapper::SHORT_CAMERA_AXIS_X_ARGUMENT);
    const auto cameraAxisY         = this->argumentParser_->get<std::vector<float>>(ArgParseWrapper::SHORT_CAMERA_AXIS_Y_ARGUMENT);
    const auto cameraAxisZ         = this->argumentParser_->get<std::vector<float>>(ArgParseWrapper::SHORT_CAMERA_AXIS_Z_ARGUMENT);
    const auto viewportTopLeftTemp = this->argumentParser_->get<std::vector<float>>(ArgParseWrapper::SHORT_VIEWPORT_TOP_LEFT_ARGUMENT);
    const auto viewportBottomRight = this->argumentParser_->get<std::vector<float>>(ArgParseWrapper::SHORT_VIEWPORT_BOTTOM_RIGHT_ARGUMENT);

    ApplicationConfig config {
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
        .MESH_FACTORY          = std::make_shared<GenericMeshGeneratorFactory>(),
        .MESH_GENERATOR        = nullptr
    };

    config.MESH_GENERATOR = this->GetMeshGenerator_(config.MESH_FACTORY);

    return config;
}

std::shared_ptr<IMeshGenerator> ArgParseWrapper::GetMeshGenerator_(const std::shared_ptr<IMeshGeneratorFactory>& meshFactory) const {
    const std::unordered_map<std::string, std::shared_ptr<IArgParseMeshGeneratorCreator>> meshGeneratorHashMap {
        std::make_pair(
            ArgParseWrapper::CIRCLE_COMMAND,
            std::make_shared<CircleMeshGeneratorCreator>(meshFactory)
        ),
        std::make_pair(
            ArgParseWrapper::CYLINDER_COMMAND,
            std::make_shared<CylinderMeshGeneratorCreator>(meshFactory)
        ),
        std::make_pair(
            ArgParseWrapper::ELLIPSE_COMMAND,
            std::make_shared<EllipseMeshGeneratorCreator>(meshFactory)
        ),
        std::make_pair(
            ArgParseWrapper::ICOSAHEDRON_COMMAND,
            std::make_shared<IcosahedronMeshGeneratorCreator>(meshFactory)
        ),
        std::make_pair(
            ArgParseWrapper::ICOSPHERE_COMMAND,
            std::make_shared<IcosphereMeshGeneratorCreator>(meshFactory)
        ),
        std::make_pair(
            ArgParseWrapper::PARALLELEPIPED_COMMAND,
            std::make_shared<ParallelepipedMeshGeneratorCreator>(meshFactory)
        ),
        std::make_pair(
            ArgParseWrapper::RECTANGLE_COMMAND,
            std::make_shared<RectangleMeshGeneratorCreator>(meshFactory)
        ),
        std::make_pair(
            ArgParseWrapper::TORUS_COMMAND,
            std::make_shared<TorusMeshGeneratorCreator>(meshFactory)
        ),
        std::make_pair(
            ArgParseWrapper::UV_SPHERE_COMMAND,
            std::make_shared<UvSphereMeshGeneratorCreator>(meshFactory)
        )
    };

    for (auto& command : ArgParseWrapper::COMMAND_ARRAY) {
        if (this->argumentParser_->is_subcommand_used(command)) {
            return meshGeneratorHashMap.at(command)->Create(*this->argumentParser_);
        }
    }

    return nullptr;
}

void ArgParseWrapper::ConstructHelper_(char** argv, int argc) {
    this->argv_ = std::vector<std::string>(argc);
    for (int i = 0; auto& el : this->argv_) {
        el = argv[i++];
    }

    this->argumentParser_ = MainParseBuilder(this->argv_.front()).GetUniqueProduct();

    const std::unordered_map<std::string, std::shared_ptr<BaseMeshParseBuilder>> meshParseBuilderHashMap {
        std::make_pair(
            ArgParseWrapper::CIRCLE_COMMAND,
            std::make_shared<CircleMeshParseBuilder>()
        ),
        std::make_pair(
            ArgParseWrapper::CYLINDER_COMMAND,
            std::make_shared<CylinderMeshParseBuilder>()
        ),
        std::make_pair(
            ArgParseWrapper::ELLIPSE_COMMAND,
            std::make_shared<EllipseMeshParseBuilder>()
        ),
        std::make_pair(
            ArgParseWrapper::ICOSAHEDRON_COMMAND,
            std::make_shared<IcosahedronMeshParseBuilder>()
        ),
        std::make_pair(
            ArgParseWrapper::ICOSPHERE_COMMAND,
            std::make_shared<IcosphereMeshParseBuilder>()
        ),
        std::make_pair(
            ArgParseWrapper::PARALLELEPIPED_COMMAND,
            std::make_shared<ParallelepipedMeshParseBuilder>()
        ),
        std::make_pair(
            ArgParseWrapper::RECTANGLE_COMMAND,
            std::make_shared<RectangleMeshParseBuilder>()
        ),
        std::make_pair(
            ArgParseWrapper::TORUS_COMMAND,
            std::make_shared<TorusMeshParseBuilder>()
        ),
        std::make_pair(
            ArgParseWrapper::UV_SPHERE_COMMAND,
            std::make_shared<UvSphereMeshParseBuilder>()
        )
    };

    for (const auto& builder : meshParseBuilderHashMap | std::views::values) {
        this->subcomands_.emplace_back(builder->GetUniqueProduct());
        this->argumentParser_->add_subparser(*this->subcomands_.back());
    }
}
