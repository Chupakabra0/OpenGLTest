#pragma once
#include "argparse/argparse.hpp"
#include "ApplicationConfig.hpp"

#include <glm/gtx/string_cast.hpp>

class ArgParseWrapper {
private:
    static const std::vector<const char* const*> COMMAND_ARRAY;

    static constexpr const char* CIRCLE_COMMAND                       = "circle";
    static constexpr const char* CYLINDER_COMMAND                     = "cylinder";
    static constexpr const char* ELLIPSE_COMMAND                      = "ellipse";
    static constexpr const char* ICOSAHEDRON_COMMAND                  = "icosahedron";
    static constexpr const char* ICOSPHERE_COMMAND                    = "icosphere";
    static constexpr const char* PARALLELEPIPED_COMMAND               = "parallelepiped";
    static constexpr const char* RECTANGLE_COMMAND                    = "rectangle";
    static constexpr const char* TORUS_COMMAND                        = "torus";
    static constexpr const char* UV_SPHERE_COMMAND                    = "uv-sphere";

    static constexpr const char* SHORT_WINDOW_HEIGHT_ARGUMENT         = "-wh";
    static constexpr const char* SHORT_WINDOW_WIDTH_ARGUMENT          = "-ww";
    static constexpr const char* SHORT_WINDOW_NAME_ARGUMENT           = "-wn";
    static constexpr const char* SHORT_CAMERA_POSITION_ARGUMENT       = "-cp";
    static constexpr const char* SHORT_CAMERA_TARET_ARGUMENT          = "-ct";
    static constexpr const char* SHORT_CAMERA_AXIS_X_ARGUMENT         = "-cx";
    static constexpr const char* SHORT_CAMERA_AXIS_Y_ARGUMENT         = "-cy";
    static constexpr const char* SHORT_CAMERA_AXIS_Z_ARGUMENT         = "-cz";
    static constexpr const char* SHORT_VIEWPORT_TOP_LEFT_ARGUMENT     = "-vtl";
    static constexpr const char* SHORT_VIEWPORT_BOTTOM_RIGHT_ARGUMENT = "-vbr";
    static constexpr const char* SHORT_VIEWPORT_FOV_ARGUMENT          = "-f";
    static constexpr const char* SHORT_VIEWPORT_NEAR_Z_ARGUMENT       = "-nz";
    static constexpr const char* SHORT_VIEWPORT_FAR_Z_ARGUMENT        = "-fz";
    static constexpr const char* SHORT_ORIGIN_ARGUMENT                = "-o";
    static constexpr const char* SHORT_COLOR_ARGUMENT                 = "-c";
    static constexpr const char* SHORT_ITERATIONS_ARGUMENT            = "-i";
    static constexpr const char* SHORT_SLICES_ARGUMENT                = "-sl";
    static constexpr const char* SHORT_SEGMENTS_ARGUMENT              = "-se";
    static constexpr const char* SHORT_RADIUS_ARGUMENT                = "-r";
    static constexpr const char* SHORT_INNER_RADIUS_ARGUMENT          = "-ir";
    static constexpr const char* SHORT_OUTER_RADIUS_ARGUMENT          = "-or";
    static constexpr const char* SHORT_HEIGHT_ARGUMENT                = "-h";
    static constexpr const char* SHORT_WIDTH_ARGUMENT                 = "-w";
    static constexpr const char* SHORT_DEPTH_ARGUMENT                 = "-d";
    static constexpr const char* SHORT_A_PARAMETER_ARGUMENT           = "-a";
    static constexpr const char* SHORT_B_PARAMETER_ARGUMENT           = "-b";

    static constexpr const char* LONG_WINDOW_HEIGHT_ARGUMENT          = "--window-height";
    static constexpr const char* LONG_WINDOW_WIDTH_ARGUMENT           = "--window-width";
    static constexpr const char* LONG_WINDOW_NAME_ARGUMENT            = "--window-name";
    static constexpr const char* LONG_CAMERA_POSITION_ARGUMENT        = "--camera-position";
    static constexpr const char* LONG_CAMERA_TARET_ARGUMENT           = "--camera-target";
    static constexpr const char* LONG_CAMERA_AXIS_X_ARGUMENT          = "--camera-x";
    static constexpr const char* LONG_CAMERA_AXIS_Y_ARGUMENT          = "--camera-y";
    static constexpr const char* LONG_CAMERA_AXIS_Z_ARGUMENT          = "--camera-z";
    static constexpr const char* LONG_VIEWPORT_TOP_LEFT_ARGUMENT      = "--viewport-tl";
    static constexpr const char* LONG_VIEWPORT_BOTTOM_RIGHT_ARGUMENT  = "--viewport-br";
    static constexpr const char* LONG_VIEWPORT_FOV_ARGUMENT           = "--fov";
    static constexpr const char* LONG_VIEWPORT_NEAR_Z_ARGUMENT        = "--near";
    static constexpr const char* LONG_VIEWPORT_FAR_Z_ARGUMENT         = "--far";
    static constexpr const char* LONG_ORIGIN_ARGUMENT                 = "--origin";
    static constexpr const char* LONG_COLOR_ARGUMENT                  = "--color";
    static constexpr const char* LONG_ITERATIONS_ARGUMENT             = "--iterations";
    static constexpr const char* LONG_SLICES_ARGUMENT                 = "--slices";
    static constexpr const char* LONG_SEGMENTS_ARGUMENT               = "--segments";
    static constexpr const char* LONG_RADIUS_ARGUMENT                 = "--radius";
    static constexpr const char* LONG_INNER_RADIUS_ARGUMENT           = "--inner-radius";
    static constexpr const char* LONG_OUTER_RADIUS_ARGUMENT           = "--outer-radius";
    static constexpr const char* LONG_HEIGHT_ARGUMENT                 = "--height";
    static constexpr const char* LONG_WIDTH_ARGUMENT                  = "--width";
    static constexpr const char* LONG_DEPTH_ARGUMENT                  = "--depth";
    static constexpr const char* LONG_A_PARAMETER_ARGUMENT            = "--a-parameter";
    static constexpr const char* LONG_B_PARAMETER_ARGUMENT            = "--b-parameter";

    static constexpr int DEFAULT_WINDOW_HEIGHT_VALUE                  = 1080;
    static constexpr int DEFAULT_WINDOW_WIDTH_VALUE                   = 1920;
    static const std::string DEFAULT_WINDOW_NAME_VALUE;
    static const std::vector<float> DEFAULT_CAMERA_POSITION_VALUE;
    static const std::vector<float> DEFAULT_CAMERA_TARET_VALUE;
    static const std::vector<float> DEFAULT_CAMERA_AXIS_X_VALUE;
    static const std::vector<float> DEFAULT_CAMERA_AXIS_Y_VALUE;
    static const std::vector<float> DEFAULT_CAMERA_AXIS_Z_VALUE;
    static const std::vector<float> DEFAULT_VIEWPORT_TOP_LEFT_VALUE;
    static const std::vector<float> DEFAULT_VIEWPORT_BOTTOM_RIGHT_VALUE;
    static constexpr float DEFAULT_VIEWPORT_FOV_VALUE                 = 45.0f;
    static constexpr float DEFAULT_VIEWPORT_NEAR_Z_VALUE              = 0.1f;
    static constexpr float DEFAULT_VIEWPORT_FAR_Z_VALUE               = 1000.0f;

public:
    ArgParseWrapper() = delete;

    explicit ArgParseWrapper(char** argv, int argc) {
        this->ConstructHelper_(argv, argc);
    }

    ArgParseWrapper(const ArgParseWrapper&) = delete;

    ArgParseWrapper(ArgParseWrapper&&) noexcept = default;

    ArgParseWrapper& operator=(const ArgParseWrapper&) = delete;

    ArgParseWrapper& operator=(ArgParseWrapper&&) noexcept = default;

    ~ArgParseWrapper() = default;

    bool ParseAllArgs();

    ApplicationConfig GetAppConfig();

private:
    std::vector<std::string> argv_{};
    std::unique_ptr<argparse::ArgumentParser> argumentParser_{};

    void ConstructHelper_(char** argv, int argc);

    std::unique_ptr<argparse::ArgumentParser> CreateIcosphereParser_();

    std::unique_ptr<argparse::ArgumentParser> CreateParallelepipedParser_();

    std::unique_ptr<argparse::ArgumentParser> CreateRectangleParser_();

    std::unique_ptr<argparse::ArgumentParser> CreateTorusParser_();

    std::unique_ptr<argparse::ArgumentParser> CreateUVSphereParser_();

    std::unique_ptr<argparse::ArgumentParser> CreateCircleParser_();

    std::unique_ptr<argparse::ArgumentParser> CreateCylinderParser_();

    std::unique_ptr<argparse::ArgumentParser> CreateEllipseParser_();

    std::unique_ptr<argparse::ArgumentParser> CreateIcosahedronParser_();

    // TODO remake it into factories
    std::shared_ptr<MeshGenerator> GetMeshGenerator_();

    std::shared_ptr<MeshGenerator> GetCircleGenerator_(argparse::ArgumentParser& parser);

    std::shared_ptr<MeshGenerator> GetCylinderGenerator_(argparse::ArgumentParser& parser);

    std::shared_ptr<MeshGenerator> GetEllipseGenerator_(argparse::ArgumentParser& parser);

    std::shared_ptr<MeshGenerator> GetIcosahedronGenerator_(argparse::ArgumentParser& parser);

    std::shared_ptr<MeshGenerator> GetIcosphereGenerator_(argparse::ArgumentParser& parser);

    std::shared_ptr<MeshGenerator> GetParallelepipedGenerator_(argparse::ArgumentParser& parser);

    std::shared_ptr<MeshGenerator> GetRectangleGenerator_(argparse::ArgumentParser& parser);

    std::shared_ptr<MeshGenerator> GetTorusGenerator_(argparse::ArgumentParser& parser);

    std::shared_ptr<MeshGenerator> GetUvSphereGenerator_(argparse::ArgumentParser& parser);


    void AddOriginArgument_(std::unique_ptr<argparse::ArgumentParser>& parser) {
        parser->add_argument(ArgParseWrapper::SHORT_ORIGIN_ARGUMENT, ArgParseWrapper::LONG_ORIGIN_ARGUMENT)
            .help("Origin of the mesh").nargs(3).scan<'f', float>().required();
    }

    void AddColorArgument_(std::unique_ptr<argparse::ArgumentParser>& parser) {
        parser->add_argument(ArgParseWrapper::SHORT_COLOR_ARGUMENT, ArgParseWrapper::LONG_COLOR_ARGUMENT)
            .help("Color of the mesh").nargs(3).scan<'f', float>().required();
    }

    void AddIterationsArgument_(std::unique_ptr<argparse::ArgumentParser>& parser) {
        parser->add_argument(ArgParseWrapper::SHORT_ITERATIONS_ARGUMENT,ArgParseWrapper::LONG_ITERATIONS_ARGUMENT)
            .help("Iterations of the mesh").nargs(1).scan<'i', int>().required();
    }

    void AddSlicesArgument_(std::unique_ptr<argparse::ArgumentParser>& parser) {
        parser->add_argument(ArgParseWrapper::SHORT_SLICES_ARGUMENT, ArgParseWrapper::LONG_SLICES_ARGUMENT)
            .help("Slices of the mesh").nargs(1).scan<'i', int>().required();
    }

    void AddSegmentsArgument_(std::unique_ptr<argparse::ArgumentParser>& parser) {
        parser->add_argument(ArgParseWrapper::SHORT_SEGMENTS_ARGUMENT, ArgParseWrapper::LONG_SEGMENTS_ARGUMENT)
            .help("Segments of the mesh").nargs(1).scan<'i', int>().required();
    }

    void AddRadiusArgument_(std::unique_ptr<argparse::ArgumentParser>& parser) {
        parser->add_argument(ArgParseWrapper::SHORT_RADIUS_ARGUMENT, ArgParseWrapper::LONG_RADIUS_ARGUMENT)
            .help("Radius of the mesh").nargs(1).scan<'f', float>().required();
    }

    void AddInnerRadiusArgument_(std::unique_ptr<argparse::ArgumentParser>& parser) {
        parser->add_argument(ArgParseWrapper::SHORT_INNER_RADIUS_ARGUMENT, ArgParseWrapper::LONG_INNER_RADIUS_ARGUMENT)
            .help("Inner radius of the mesh").nargs(1).scan<'f', float>().required();
    }

    void AddOuterRadiusArgument_(std::unique_ptr<argparse::ArgumentParser>& parser) {
        parser->add_argument(ArgParseWrapper::SHORT_OUTER_RADIUS_ARGUMENT, ArgParseWrapper::LONG_OUTER_RADIUS_ARGUMENT)
            .help("Outer radius of the mesh").nargs(1).scan<'f', float>().required();
    }

    void AddHeightArgument_(std::unique_ptr<argparse::ArgumentParser>& parser) {
        parser->add_argument(ArgParseWrapper::SHORT_HEIGHT_ARGUMENT, ArgParseWrapper::LONG_HEIGHT_ARGUMENT)
            .help("Height of the mesh").nargs(1).scan<'f', float>().required();
    }

    void AddWidthArgument_(std::unique_ptr<argparse::ArgumentParser>& parser) {
        parser->add_argument(ArgParseWrapper::SHORT_WIDTH_ARGUMENT, ArgParseWrapper::LONG_WIDTH_ARGUMENT)
            .help("Height of the mesh").nargs(1).scan<'f', float>().required();
    }

    void AddDepthArgument_(std::unique_ptr<argparse::ArgumentParser>& parser) {
        parser->add_argument(ArgParseWrapper::SHORT_DEPTH_ARGUMENT, ArgParseWrapper::LONG_DEPTH_ARGUMENT)
            .help("Depth of the mesh").nargs(1).scan<'f', float>().required();
    }

    void AddAArgument_(std::unique_ptr<argparse::ArgumentParser>& parser) {
        parser->add_argument(ArgParseWrapper::SHORT_A_PARAMETER_ARGUMENT, ArgParseWrapper::LONG_A_PARAMETER_ARGUMENT)
            .help("A parameter of the mesh").nargs(1).scan<'f', float>().required();
    }

    void AddBArgument_(std::unique_ptr<argparse::ArgumentParser>& parser) {
        parser->add_argument(ArgParseWrapper::SHORT_B_PARAMETER_ARGUMENT, ArgParseWrapper::LONG_B_PARAMETER_ARGUMENT)
            .help("B parameter of the mesh").nargs(1).scan<'f', float>().required();
    }
};