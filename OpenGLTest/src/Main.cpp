#include "Application.hpp"
#include "ArgParseWrapper.hpp"

int main(int argc, char** argv) {
    try {
        spdlog::set_level(LogLevelToSpdlog(IsDebug() ? LogLevel::DEBUG : LogLevel::INFO));

        SPDLOG_INFO("Logger initialized");
        SPDLOG_INFO("Application configuration is loading");

        const ApplicationConfig config {
            .WINDOW_HEIGHT         = 1080,
            .WINDOW_WIDTH          = 1920,
            .WINDOW_NAME           = "OpenGL Test",
            .CAMERA_POSITION       = glm::vec3(0.0f, 0.0f, 500.0f),
            .CAMERA_TARGET         = glm::vec3(0.0f, 0.0f, 0.0f),
            .CAMERA_AXIS_X         = glm::vec3(1.0f, 0.0f, 0.0f),
            .CAMERA_AXIS_Y         = glm::vec3(0.0f, 1.0f, 0.0f),
            .CAMERA_AXIS_Z         = glm::vec3(0.0f, 0.0f, -1.0f),
            .VIEWPORT_TOP_LEFT     = glm::vec2(0, 0),
            .VIEWPORT_BOTTOM_RIGHT = glm::vec2(config.WINDOW_WIDTH, config.WINDOW_HEIGHT),
            .VIEWPORT_FOV          = 45.0f,
            .VIEWPORT_NEAR_Z       = 0.1f,
            .VIEWPORT_FAR_Z        = 1000.0f
        };

        SPDLOG_INFO("Application configuration loaded");
        SPDLOG_INFO("Console args parser has started");

        ArgParseWrapper argParseWrapper(argv, argc);
        argParseWrapper.ParseAllArgs();

        SPDLOG_INFO("Console args parsed");
        SPDLOG_INFO("Mesh generator is creating");

        SPDLOG_INFO("Mesh generator created");
        SPDLOG_INFO("Application initialization started");

        //Application application(config, meshGenerator);

        SPDLOG_INFO("Application initialization ended");

        //application.Run();
    }
    catch (const std::exception& ex) {
        SPDLOG_CRITICAL(ex.what());

        return EXIT_FAILURE;
    }

    SPDLOG_INFO("Application ended");

    return EXIT_SUCCESS;
}
