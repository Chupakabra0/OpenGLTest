#include "Application.hpp"

int main(int argc, char** argv) {
    try {
        const ApplicationConfig config {
            .WINDOW_HEIGHT         = 1080,
            .WINDOW_WIDTH          = 1920,
            .WINDOW_NAME           = "OpenGL Test",
            .CAMERA_POSITION       = glm::vec3(0.0f, 0.0f, 400.0f),
            .CAMERA_TARGET         = glm::vec3(0.0f, 0.0f, 0.0f),
            .CAMERA_AXIS_X         = glm::vec3(1.0f, 0.0f, 0.0f),
            .CAMERA_AXIS_Y         = glm::vec3(0.0f, 1.0f, 0.0f),
            .CAMERA_AXIS_Z         = glm::vec3(0.0f, 0.0f, -1.0f),
            .VIEWPORT_TOP_LEFT     = glm::vec2(0, 0),
            .VIEWPORT_BOTTOM_RIGHT = glm::vec2(config.WINDOW_WIDTH, config.WINDOW_HEIGHT),
            .VIEWPORT_FOV          = 90.0f,
            .VIEWPORT_NEAR_Z       = 0.1f,
            .VIEWPORT_FAR_Z        = 500.0f
        };

        const glm::vec3 origin = glm::zero<glm::vec3>();
        const float size       = 150.0f;
        const int segments     = 10;
        const int slices       = 10;
        const std::shared_ptr<MeshGenerator> meshGenerator = std::make_shared<UVSphereGenerator>(
            size, segments, slices, origin, glm::zero<glm::vec3>()
        );

        Application application(config, meshGenerator);

        application.Run();
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
