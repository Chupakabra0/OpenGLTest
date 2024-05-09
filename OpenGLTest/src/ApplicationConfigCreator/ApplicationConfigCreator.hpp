#pragma once
#include "ApplicationConfig/ApplicationConfig.hpp"

#include <nlohmann/json.hpp>

#include <fstream>
#include <format>

class ApplicationConfigCreator {
public:
    ApplicationConfigCreator() = delete;

    explicit ApplicationConfigCreator(const std::filesystem::path& configFilepath)
        : configFileStream_(configFilepath, std::fstream::in) {
        if (!configFileStream_.is_open()) {
            throw std::runtime_error(std::format("Config file {} does not exist!", configFilepath.string()));
        }
    }

    ApplicationConfigCreator(const ApplicationConfigCreator&) = delete;

    ApplicationConfigCreator(ApplicationConfigCreator&&) noexcept = default;

    ApplicationConfigCreator& operator=(const ApplicationConfigCreator&) = delete;

    ApplicationConfigCreator& operator=(ApplicationConfigCreator&&) noexcept = default;

    ~ApplicationConfigCreator() = default;

    ApplicationConfig CreateApplicationConfig();

private:
    std::fstream configFileStream_{};
};
