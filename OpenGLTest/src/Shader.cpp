#include "Shader.hpp"

Shader::Shader(const std::filesystem::path& shaderPath, const ShaderType& shaderType)
    : shaderType_(shaderType) {
    this->ConstructHelper_(shaderPath);
}

Shader::Shader(Shader&& move) noexcept {
    this->MoveHelper_(std::move(move));
}

Shader& Shader::operator=(Shader&& move) noexcept {
    this->DestroyHelper_();
    this->MoveHelper_(std::move(move));

    return *this;
}

Shader::~Shader() noexcept {
    this->DestroyHelper_();
}

void Shader::Bind() {
    if (this->isBinded_) {
        return;
    }

    glAttachShader(this->programId_, this->id_);

    BindableDataObject::Bind();
}

void Shader::Unbind() {
    if (!this->isBinded_) {
        return;
    }

    glDetachShader(this->programId_, this->id_);

    BindableDataObject::Unbind();
}

unsigned Shader::GetProgramId() const {
    return this->programId_;
}

void Shader::SetProgramID(unsigned programId) {
    this->programId_ = programId;
}

ShaderType Shader::GetShaderType() const {
    return this->shaderType_;
}

void Shader::ConstructHelper_(const std::filesystem::path& shaderPath) {
    std::fstream shaderFile{shaderPath, std::fstream::in | std::fstream::ate};

    if (!shaderFile.is_open()) {
        throw std::runtime_error(std::format("Shader file \"{}\" opening error", shaderPath.string()));
    }

    const std::string vertexShaderCode{Shader::GetShaderCode_(shaderFile)};

    this->id_ = this->CompileShaderProgram_(this->shaderType_, vertexShaderCode.c_str());
}

void Shader::DestroyHelper_() {
    glDeleteShader(this->id_);
}

void Shader::MoveHelper_(Shader&& move) noexcept {
    std::swap(move.id_, this->id_);
    std::swap(move.isBinded_, this->isBinded_);
    std::swap(move.programId_, this->programId_);
    std::swap(move.shaderType_, this->shaderType_);
}

unsigned Shader::CompileShaderProgram_(ShaderType type, const char* source) {
    unsigned shaderId{ glCreateShader(static_cast<int>(type)) };

    glShaderSource(shaderId, 1, &source, nullptr);
    glCompileShader(shaderId);

    int result{};
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

    if (!result) {
        int length{};
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);

        char* message{ reinterpret_cast<char*>(_malloca(length * sizeof(char))) };
        glGetShaderInfoLog(shaderId, length, nullptr, message);

        throw std::runtime_error(message);
    }

    return shaderId;
}

std::string Shader::GetShaderCode_(std::fstream& shaderFile) {
    const size_t shaderSize{ static_cast<size_t>(shaderFile.tellg()) };
    std::string shaderCode(shaderSize, ' ');

    shaderFile.seekg(0);
    shaderFile.read(shaderCode.data(), shaderSize);

    return shaderCode;
}
