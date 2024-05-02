#include "TextureLoader/TextureLoaderSTB/TextureLoaderSTB.hpp"

#include <stb/stb_image.h>

inline void TextureLoaderSTB::LoadTextureSymbols(const std::filesystem::path& filepath, std::basic_string<unsigned char>& result,
    int& height, int& width, int& channels) {
    stbi_set_flip_vertically_on_load(true);

    unsigned char* temp = stbi_load(
        filepath.string().c_str(), &width, &height, &channels, 3
    );

    if (temp == nullptr) {
        throw std::runtime_error("Texture hasn't loaded!");
    }

    result.assign(temp, std::next(temp, static_cast<size_t>(width * height * channels)));
    stbi_image_free(temp);
}
