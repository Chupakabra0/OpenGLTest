#pragma once
#include "glad/glad.h"

#include "DataObject.hpp"

#include <filesystem>
#include <TextureLoader/ITextureLoader.hpp>

class Texture : public BindableDataObject {
public:
    Texture() = delete;

    explicit Texture(const std::filesystem::path& filepath, int slot, const std::shared_ptr<ITextureLoader>& textureLoader);

    ~Texture() override;

    void Bind() override;

    void Unbind() override;

    void SetSlot(unsigned slot);

    unsigned GetSlot() const;

private:
    std::shared_ptr<ITextureLoader> textureLoader_;
    int height_{};
    int width_{};
    int channels{};
    int slot_{};
    std::basic_string<unsigned char> localBuffer_{};

    void ConstructHelper_(const std::filesystem::path& filepath);

    void DestroyHelper_();

    void LoadTextureImage_(const std::filesystem::path& filepath);
};