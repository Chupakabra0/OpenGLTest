#pragma once
#include "BindableDataObject/BindableDataObject.hpp"

#include <glad.h>

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

class ShaderInstance : public BindableDataObject {
public:
    ShaderInstance() = delete;

    explicit ShaderInstance(const std::filesystem::path& shaderPath, const ShaderType& shaderType);

    ShaderInstance(const ShaderInstance&) = delete;

    ShaderInstance(ShaderInstance&& move) noexcept;

    ShaderInstance& operator=(const ShaderInstance&) = delete;

    ShaderInstance& operator=(ShaderInstance&& move) noexcept;

    ~ShaderInstance() noexcept override;

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

    void MoveHelper_(ShaderInstance&& move) noexcept;

    unsigned CompileShaderProgram_(ShaderType type, const char* source);

    static std::string GetShaderCode_(std::fstream& shaderFile);
};
