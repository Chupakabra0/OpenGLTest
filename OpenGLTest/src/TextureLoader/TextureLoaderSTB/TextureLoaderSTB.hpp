#pragma once
#include "TextureLoader/ITextureLoader.hpp"

class TextureLoaderSTB : public ITextureLoader {
public:
    void LoadTextureSymbols(const std::filesystem::path& filepath, std::basic_string<unsigned char>& result,
        int& height, int& width, int& channels) override;
};
