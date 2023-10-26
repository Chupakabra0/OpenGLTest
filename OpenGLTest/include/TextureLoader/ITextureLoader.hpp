#pragma once
#include <filesystem>

struct ITextureLoader {
public:
    virtual ~ITextureLoader() = default;
    virtual void LoadTextureSymbols(const std::filesystem::path& filepath,
        std::basic_string<unsigned char>& result, int& height, int& width, int& channels) = 0;
};
