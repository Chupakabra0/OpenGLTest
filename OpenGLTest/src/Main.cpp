#include "ApplicationInstance/ApplicationInstance.hpp"
#include "ArgParseWrapper/ArgParseWrapper.hpp"

#include <spdlog/spdlog.h>

int main(int argc, char** argv) {
    try {
        ArgParseWrapper argParseWrapper(argv, argc);
        
        if (!argParseWrapper.ParseAllArgs()) {
            return EXIT_SUCCESS;
        }

        const auto config = argParseWrapper.GetAppConfig();

        spdlog::set_level(LogLevelToSpdlog(IsDebug() ? LogLevel::DEBUG : LogLevel::INFO));

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
