#include "ShaderInstance/ShaderInstance.hpp"

ShaderInstance::ShaderInstance(const std::filesystem::path& shaderPath, const ShaderType& shaderType)
    : shaderType_(shaderType) {
    this->ConstructHelper_(shaderPath);
}

ShaderInstance::ShaderInstance(ShaderInstance&& move) noexcept {
    this->MoveHelper_(std::move(move));
}

ShaderInstance& ShaderInstance::operator=(ShaderInstance&& move) noexcept {
    this->DestroyHelper_();
    this->MoveHelper_(std::move(move));

    return *this;
}

ShaderInstance::~ShaderInstance() noexcept {
    this->DestroyHelper_();
}

void ShaderInstance::Bind() {
    if (this->isBinded_) {
        return;
    }

    glAttachShader(this->programId_, this->id_);

    BindableDataObject::Bind();
}

void ShaderInstance::Unbind() {
    if (!this->isBinded_) {
        return;
    }

    glDetachShader(this->programId_, this->id_);

    BindableDataObject::Unbind();
}

unsigned ShaderInstance::GetProgramId() const {
    return this->programId_;
}

void ShaderInstance::SetProgramID(unsigned programId) {
    this->programId_ = programId;
}

ShaderType ShaderInstance::GetShaderType() const {
    return this->shaderType_;
}

void ShaderInstance::ConstructHelper_(const std::filesystem::path& shaderPath) {
    std::fstream shaderFile{shaderPath, std::fstream::in | std::fstream::ate};

    if (!shaderFile.is_open()) {
        throw std::runtime_error(std::format("Shader file \"{}\" opening error", shaderPath.string()));
    }

    const std::string vertexShaderCode{ShaderInstance::GetShaderCode_(shaderFile)};

    this->id_ = this->CompileShaderProgram_(this->shaderType_, vertexShaderCode.c_str());
}

void ShaderInstance::DestroyHelper_() {
    glDeleteShader(this->id_);
}

void ShaderInstance::MoveHelper_(ShaderInstance&& move) noexcept {
    std::swap(move.id_, this->id_);
    std::swap(move.isBinded_, this->isBinded_);
    std::swap(move.programId_, this->programId_);
    std::swap(move.shaderType_, this->shaderType_);
}

unsigned ShaderInstance::CompileShaderProgram_(ShaderType type, const char* source) {
    unsigned shaderId{ glCreateShader(static_cast<int>(type)) };

    glShaderSource(shaderId, 1, &source, nullptr);
    glCompileShader(shaderId);

    int result{};
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

    if (!result) {
        int length{};
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);

        char* message{static_cast<char*>(_malloca(length * sizeof(char)))};
        glGetShaderInfoLog(shaderId, length, nullptr, message);

        throw std::runtime_error(message);
    }

    return shaderId;
}

std::string ShaderInstance::GetShaderCode_(std::fstream& shaderFile) {
    const size_t shaderSize{static_cast<size_t>(shaderFile.tellg())};
    std::string shaderCode(shaderSize, ' ');

    shaderFile.seekg(0);
    shaderFile.read(shaderCode.data(), shaderSize);

    return shaderCode;
}
