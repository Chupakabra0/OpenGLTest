#pragma once
#include "BindableDataObject/BindableDataObject.hpp"
#include "TextureLoader/ITextureLoader.hpp"

#include <filesystem>

class TextureInstance : public BindableDataObject {
public:
    TextureInstance() = delete;

    explicit TextureInstance(const std::filesystem::path& filepath, int slot, const std::shared_ptr<ITextureLoader>& textureLoader);

    TextureInstance(const TextureInstance&) = delete;

    TextureInstance(TextureInstance&&) noexcept = default;

    TextureInstance& operator=(const TextureInstance&) = delete;

    TextureInstance& operator=(TextureInstance&&) noexcept = default;

    ~TextureInstance() override;

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