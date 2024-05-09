#pragma once
#include <argparse/argparse.hpp>

#include "ApplicationConfig/ApplicationConfig.hpp"

class ArgParseWrapper {
public:
    static const std::vector<std::string> COMMAND_ARRAY;

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
    static constexpr const char* SHORT_CONFIG_JSON_ARGUMENT           = "-j";

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
    static constexpr const char* LONG_CONFIG_JSON_ARGUMENT            = "--json";

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
    static constexpr const char* DEFAULT_CONFIG_JSON_VALUE            = "config.json";

    ArgParseWrapper() = delete;

    explicit ArgParseWrapper(char** argv, int argc);

    ArgParseWrapper(const ArgParseWrapper&) = delete;

    ArgParseWrapper(ArgParseWrapper&&) noexcept = default;

    ArgParseWrapper& operator=(const ArgParseWrapper&) = delete;

    ArgParseWrapper& operator=(ArgParseWrapper&&) noexcept = default;

    ~ArgParseWrapper() = default;

    bool ParseAllArgs() const;

    ApplicationConfig GetAppConfig() const;

private:
    std::unique_ptr<argparse::ArgumentParser> argumentParser_{};
    std::vector<std::string> argv_{};
    std::vector<std::unique_ptr<argparse::ArgumentParser>> subcomands_{};

    void ConstructHelper_(char** argv, int argc);

    std::shared_ptr<IMeshGenerator> GetMeshGenerator_(const std::shared_ptr<IMeshGeneratorFactory>& meshFactory) const;
};
