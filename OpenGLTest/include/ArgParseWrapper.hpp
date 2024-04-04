#pragma once
#include "argparse/argparse.hpp"
#include "ApplicationConfig.hpp"

class ArgParseWrapper {
public:
    static constexpr const char* CIRCLE_COMMAND         = "circle";
    static constexpr const char* CYLINDER_COMMAND       = "cylinder";
    static constexpr const char* ELLIPSE_COMMAND        = "ellipse";
    static constexpr const char* ICOSAHEDRON_COMMAND    = "icosahedron";
    static constexpr const char* ICOSPHERE_COMMAND      = "icosphere";
    static constexpr const char* PARALLELEPIPED_COMMAND = "parallelepiped";
    static constexpr const char* RECTANGLE_COMMAND      = "rectangle";
    static constexpr const char* TORUS_COMMAND          = "torus";
    static constexpr const char* UV_SPHERE_COMMAND      = "uv-sphere";

    static constexpr const char* SHORT_WINDOW_HEIGHT_ARGUMENT         = "-wh";
    static constexpr const char* SHORT_WINDOW_WIDTH_ARGUMENT          = "-ww";
    static constexpr const char* SHORT_WINDOW_NAME_ARGUMENT           = "-wn";
    static constexpr const char* SHORT_CAMERA_POSITION_ARGUMENT       = "-wn";
    static constexpr const char* SHORT_CAMERA_TARET_ARGUMENT          = "-ct";
    static constexpr const char* SHORT_CAMERA_AXIS_X_ARGUMENT         = "-cx";
    static constexpr const char* SHORT_CAMERA_AXIS_Y_ARGUMENT         = "-cy";
    static constexpr const char* SHORT_CAMERA_AXIS_Z_ARGUMENT         = "-cz";
    static constexpr const char* SHORT_VIEWPORT_TOP_LEFT_ARGUMENT     = "-vtl";
    static constexpr const char* SHORT_VIEWPORT_BOTTOM_RIGHT_ARGUMENT = "-vbr";
    static constexpr const char* SHORT_VIEWPORT_FOV_ARGUMENT          = "-f";
    static constexpr const char* SHORT_VIEWPORT_NEAR_Z_ARGUMENT       = "-n";
    static constexpr const char* SHORT_VIEWPORT_FAR_Z_ARGUMENT        = "-f";

    static constexpr const char* LONG_WINDOW_HEIGHT_ARGUMENT         = "-window-height";
    static constexpr const char* LONG_WINDOW_WIDTH_ARGUMENT          = "-window-width";
    static constexpr const char* LONG_WINDOW_NAME_ARGUMENT           = "-window-name";
    static constexpr const char* LONG_CAMERA_POSITION_ARGUMENT       = "-camera-position";
    static constexpr const char* LONG_CAMERA_TARET_ARGUMENT          = "-camera-target";
    static constexpr const char* LONG_CAMERA_AXIS_X_ARGUMENT         = "-camera-x";
    static constexpr const char* LONG_CAMERA_AXIS_Y_ARGUMENT         = "-camera-y";
    static constexpr const char* LONG_CAMERA_AXIS_Z_ARGUMENT         = "-camera-z";
    static constexpr const char* LONG_VIEWPORT_TOP_LEFT_ARGUMENT     = "-viewport-tl";
    static constexpr const char* LONG_VIEWPORT_BOTTOM_RIGHT_ARGUMENT = "-viewport-br";
    static constexpr const char* LONG_VIEWPORT_FOV_ARGUMENT          = "-fov";
    static constexpr const char* LONG_VIEWPORT_NEAR_Z_ARGUMENT       = "-near";
    static constexpr const char* LONG_VIEWPORT_FAR_Z_ARGUMENT        = "-far";

    // TODO: static consts default values of arguments

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

    std::shared_ptr<MeshGenerator> GetMeshGenerator_();

    std::shared_ptr<MeshGenerator> GetCircleGenerator_();

    std::shared_ptr<MeshGenerator> GetCylinderGenerator_();

    std::shared_ptr<MeshGenerator> GetEllipseGenerator_();

    std::shared_ptr<MeshGenerator> GetIcosahedronGenerator_();

    std::shared_ptr<MeshGenerator> GetIcosphereGenerator_();

    std::shared_ptr<MeshGenerator> GetParallelepipedGenerator_();

    std::shared_ptr<MeshGenerator> GetRectangleGenerator_();

    std::shared_ptr<MeshGenerator> GetTorusGenerator_();

    std::shared_ptr<MeshGenerator> GetUvSphereGenerator_();


    void AddOriginArgument_(std::unique_ptr<argparse::ArgumentParser>& parser) {
        parser->add_argument("-o", "--origin").help("Origin of the mesh").nargs(3).scan<'f', float>().required();
    }

    void AddColorArgument_(std::unique_ptr<argparse::ArgumentParser>& parser) {
        parser->add_argument("-c", "--color").help("Color of the mesh").nargs(3).scan<'f', float>().required();
    }

    void AddIterationsArgument_(std::unique_ptr<argparse::ArgumentParser>& parser) {
        parser->add_argument("-i", "--iterations").help("Iterations of the mesh").nargs(1).scan<'i', int>().required();
    }

    void AddSlicesArgument_(std::unique_ptr<argparse::ArgumentParser>& parser) {
        parser->add_argument("-sl", "--slices").help("Slices of the mesh").nargs(1).scan<'i', int>().required();
    }

    void AddSegmentsArgument_(std::unique_ptr<argparse::ArgumentParser>& parser) {
        parser->add_argument("-se", "--segments").help("Segments of the mesh").nargs(1).scan<'i', int>().required();
    }

    void AddRadiusArgument_(std::unique_ptr<argparse::ArgumentParser>& parser) {
        parser->add_argument("-r", "--radius").help("Radius of the mesh").nargs(1).scan<'f', float>().required();
    }

    void AddInnerRadiusArgument_(std::unique_ptr<argparse::ArgumentParser>& parser) {
        parser->add_argument("-ir", "--inner-radius").help("Inner radius of the mesh").nargs(1).scan<'f', float>().required();
    }

    void AddOuterRadiusArgument_(std::unique_ptr<argparse::ArgumentParser>& parser) {
        parser->add_argument("-or", "--outer-radius").help("Outer radius of the mesh").nargs(1).scan<'f', float>().required();
    }

    void AddHeightArgument_(std::unique_ptr<argparse::ArgumentParser>& parser) {
        parser->add_argument("-h", "--height").help("Height of the mesh").nargs(1).scan<'f', float>().required();
    }

    void AddWidthArgument_(std::unique_ptr<argparse::ArgumentParser>& parser) {
        parser->add_argument("-w", "--width").help("Height of the mesh").nargs(1).scan<'f', float>().required();
    }

    void AddDepthArgument_(std::unique_ptr<argparse::ArgumentParser>& parser) {
        parser->add_argument("-d", "--depth").help("Depth of the mesh").nargs(1).scan<'f', float>().required();
    }

    void AddAArgument_(std::unique_ptr<argparse::ArgumentParser>& parser) {
        parser->add_argument("-a", "--a-parameter").help("A parameter of the mesh").nargs(1).scan<'f', float>().required();
    }

    void AddBArgument_(std::unique_ptr<argparse::ArgumentParser>& parser) {
        parser->add_argument("-b", "--b-parameter").help("B parameter of the mesh").nargs(1).scan<'f', float>().required();
    }
};