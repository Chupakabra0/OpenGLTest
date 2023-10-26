#pragma once
#if defined(OPENCV)
    #include "ITextureLoader.hpp"

    #include <opencv2/opencv.hpp>
    #include <opencv2/core/utils/logger.hpp>

    class TextureLoaderCV : public ITextureLoader {
    public:
         void LoadTextureSymbols(const std::filesystem::path& filepath, std::basic_string<unsigned char>& result,
             int& height, int& width, int& channels) override {
            cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);

            auto img = cv::imread(filepath.string(), cv::IMREAD_UNCHANGED);

            if (img.empty()) {
                throw std::runtime_error("Texture hasn't loaded!");
            }

            cv::flip(img, img, 0);
            cv::cvtColor(img, img, cv::COLOR_BGR2RGB);

            height   = img.rows;
            width    = img.cols;
            channels = img.channels();

            result.assign(img.data, img.data + width * height * channels);
        }
    };
#endif