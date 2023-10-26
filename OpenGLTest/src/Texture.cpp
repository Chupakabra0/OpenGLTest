#include "Texture.hpp"
#include "DataObjectGuard.hpp"
#include "VertexBufferAttributes.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>

Texture::Texture(const std::filesystem::path& filepath, int slot, const std::shared_ptr<ITextureLoader>& textureLoader)
    : textureLoader_(textureLoader), slot_(slot) {
    this->ConstructHelper_(filepath);
}

Texture::~Texture() {
    this->DestroyHelper_();
}

void Texture::Bind() {
    if (this->isBinded_) {
        return;
    }

    glActiveTexture(GL_TEXTURE0 + this->slot_);
    glBindTexture(GL_TEXTURE_2D, this->id_);

    BindableDataObject::Bind();
}

void Texture::Unbind() {
    if (!this->isBinded_) {
        return;
    }

    glBindTexture(GL_TEXTURE_2D, 0u);

    BindableDataObject::Unbind();
}

void Texture::SetSlot(unsigned slot) {
    this->slot_ = slot;
}

unsigned Texture::GetSlot() const {
    return this->slot_;
}

void Texture::ConstructHelper_(const std::filesystem::path& filepath) {
    if (this->textureLoader_ == nullptr) {
        throw std::runtime_error("Texture loader is null");
    }

    this->LoadTextureImage_(filepath);

    glGenTextures(1, &this->id_);

    DataObjectGuard guard{*this};

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(
        GL_TEXTURE_2D, 0, this->channels == 3 ? GL_RGB8 : GL_RGBA8, this->width_, this->height_, 0,
        this->channels == 3 ? GL_RGB : GL_RGBA, static_cast<int>(GetType<decltype(this->localBuffer_)::value_type>()),
        this->localBuffer_.data()
    );
}

void Texture::DestroyHelper_() {
    glDeleteTextures(1, &this->id_);
}

void Texture::LoadTextureImage_(const std::filesystem::path& filepath) {
    if (this->textureLoader_ == nullptr) {
        throw std::runtime_error("Texture loader is null");
    }

    this->textureLoader_->LoadTextureSymbols(
        filepath, this->localBuffer_, this->height_,
        this->width_, this->channels
    );
}
