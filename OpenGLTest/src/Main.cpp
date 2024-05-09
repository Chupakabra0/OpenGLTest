#include <spdlog/spdlog.h>

#include "ApplicationInstance/ApplicationInstance.hpp"
#include "ApplicationConfigCreator/ApplicationConfigCreator.hpp"

int main(int argc, char** argv) {
    try {
        spdlog::set_level(LogLevelToSpdlog(IsDebug() ? LogLevel::DEBUG : LogLevel::INFO));

        constexpr const char* defaultConfigJsonFilename = "configs\\config.json";
        const ApplicationConfig config = ApplicationConfigCreator(argc < 2 ? defaultConfigJsonFilename : argv[1]).CreateApplicationConfig();

        SPDLOG_INFO("Logger initialized");
        SPDLOG_INFO("Application initialization started");

        ApplicationInstance application(config);

        SPDLOG_INFO("Application initialization ended");

        application.Run();
    }
    catch (const std::exception& ex) {
        SPDLOG_CRITICAL(ex.what());

        return EXIT_FAILURE;
    }

    SPDLOG_INFO("Application ended");

    return EXIT_SUCCESS;
}
