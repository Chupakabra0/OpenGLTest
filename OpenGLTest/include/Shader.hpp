#pragma once
#include "DataObject.hpp"

#include "glad/glad.h"

#include <filesystem>
#include <fstream>

enum class ShaderType : int {
    COMPUTE_SHADER         = GL_COMPUTE_SHADER,
    VERTEX_SHADER          = GL_VERTEX_SHADER,
    TESS_CONTROL_SHADER    = GL_TESS_CONTROL_SHADER,
    TESS_EVALUATION_SHADER = GL_TESS_EVALUATION_SHADER,
    GEOMETRY_SHADER        = GL_GEOMETRY_SHADER,
    FRAGMENT_SHADER        = GL_FRAGMENT_SHADER
};

class Shader : public BindableDataObject {
public:
    Shader() = delete;

    explicit Shader(const std::filesystem::path& shaderPath, const ShaderType& shaderType);

    Shader(const Shader&) = delete;

    Shader(Shader&& move) noexcept;

    Shader& operator=(const Shader&) = delete;

    Shader& operator=(Shader&& move) noexcept;

    ~Shader() noexcept override;

    void Bind() override;

    void Unbind() override;

    unsigned GetProgramId() const;

    void SetProgramID(unsigned programId);

    ShaderType GetShaderType() const;

private:
    unsigned programId_{};
    ShaderType shaderType_{};

    void ConstructHelper_(const std::filesystem::path& shaderPath);

    void DestroyHelper_();

    void MoveHelper_(Shader&& move) noexcept;

    unsigned CompileShaderProgram_(ShaderType type, const char* source);

    static std::string GetShaderCode_(std::fstream& shaderFile);
};
