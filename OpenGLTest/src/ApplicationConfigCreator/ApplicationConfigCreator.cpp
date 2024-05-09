#include "ApplicationConfigCreator/ApplicationConfigCreator.hpp"

ApplicationConfig ApplicationConfigCreator::CreateApplicationConfig() {
    const nlohmann::json json = nlohmann::json::parse(this->configFileStream_);
    ApplicationConfig config  = json.at("CONFIG").get<ApplicationConfig>();

    return config;
}
