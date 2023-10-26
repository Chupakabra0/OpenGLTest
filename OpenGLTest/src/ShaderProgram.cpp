#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram(Shader& vertexShader, Shader& fragmentShader) {
    this->ConstructorHelper_(vertexShader, fragmentShader);
}

ShaderProgram::ShaderProgram(Shader& vertexShader, Shader& fragmentShader, Shader& geometryShader) {
    this->ConstructorHelper_(vertexShader, fragmentShader, geometryShader);
}


ShaderProgram::ShaderProgram(ShaderProgram&&) noexcept = default;

ShaderProgram& ShaderProgram::operator=(ShaderProgram&&) noexcept = default;

ShaderProgram::~ShaderProgram() noexcept {
    this->DestroyHelper_();
}

void ShaderProgram::Bind() {
    if (this->isBinded_) {
        return;
    }

    glUseProgram(this->id_);

    BindableDataObject::Bind();
}

void ShaderProgram::Unbind() {
    if (!this->isBinded_) {
        return;
    }

    glUseProgram(0u);

    BindableDataObject::Unbind();
}

void ShaderProgram::SetUniformInt(int uniformId, int v) {
    const DataObjectGuard guard{*this};
    glUniform1i(uniformId, v);
}

void ShaderProgram::SetUniformInt(const std::string& name, int v) {
    this->SetUniformInt(this->GetUniformLocation(name), v);
}

void ShaderProgram::SetUniformFloat(int uniformId, float v) {
    const DataObjectGuard guard{*this};
    glUniform1f(uniformId, v);
}

void ShaderProgram::SetUniformFloat(const std::string& name, float v) {
    this->SetUniformFloat(this->GetUniformLocation(name), v);
}

void ShaderProgram::SetUniformPairFloat(int uniformId, float v1, float v2) {
    const DataObjectGuard guard{*this};
    glUniform2f(uniformId, v1, v2);
}

void ShaderProgram::SetUniformPairFloat(const std::string& name, float v1, float v2) {
    this->SetUniformPairFloat(this->GetUniformLocation(name), v1, v2);
}

void ShaderProgram::SetUniformTripleFloat(int uniformId, float v1, float v2, float v3) {
    const DataObjectGuard guard{*this};
    glUniform3f(uniformId, v1, v2, v3);
}

void ShaderProgram::SetUniformTripleFloat(const std::string& name, float v1, float v2, float v3) {
    this->SetUniformTripleFloat(this->GetUniformLocation(name), v1, v2, v3);
}

void ShaderProgram::SetUniformQuadroFloat(int uniformId, float v1, float v2, float v3, float v4) {
    const DataObjectGuard guard{*this};
    glUniform4f(uniformId, v1, v2, v3, v4);
}

void ShaderProgram::SetUniformQuadroFloat(const std::string& name, float v1, float v2, float v3, float v4) {
    this->SetUniformQuadroFloat(this->GetUniformLocation(name), v1, v2, v3, v4);
}

int ShaderProgram::GetUniformLocation(const std::string& name) const {
    if (!this->uniformLocationCache_.contains(name)) {
        this->uniformLocationCache_.emplace(name, glGetUniformLocation(this->id_, name.c_str()));
    }

    return this->uniformLocationCache_.at(name);
}

void ShaderProgram::ConstructorHelper_(Shader& vertexShader, Shader& fragmentShader) {
    this->id_ = this->CreateShaderProgram_(vertexShader, fragmentShader);
}

void ShaderProgram::ConstructorHelper_(Shader& vertexShader, Shader& fragmentShader, Shader& geometryShader) {
    this->id_ = this->CreateShaderProgram_(vertexShader, fragmentShader, geometryShader);
}

void ShaderProgram::DestroyHelper_() noexcept {
    glDeleteProgram(this->id_);
}

unsigned ShaderProgram::CreateShaderProgram_(Shader& vertexShader, Shader& fragmentShader) {
    unsigned programId{glCreateProgram()};

    vertexShader.SetProgramID(programId);
    fragmentShader.SetProgramID(programId);

    const DataObjectGuard vertexGuard{vertexShader};
    const DataObjectGuard fragmentGuard{fragmentShader};

    glLinkProgram(programId);
    glValidateProgram(programId);

    return programId;
}

unsigned ShaderProgram::CreateShaderProgram_(Shader& vertexShader, Shader& fragmentShader, Shader& geometryShader) {
    unsigned programId{glCreateProgram()};

    vertexShader.SetProgramID(programId);
    fragmentShader.SetProgramID(programId);
    geometryShader.SetProgramID(programId);

    const DataObjectGuard vertexGuard{vertexShader};
    const DataObjectGuard fragmentGuard{fragmentShader};
    const DataObjectGuard geometryGuard{geometryShader};

    glLinkProgram(programId);
    glValidateProgram(programId);

    return programId;
}
