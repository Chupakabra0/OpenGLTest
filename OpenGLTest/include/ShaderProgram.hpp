#pragma once
#include "Shader.hpp"
#include "DataObjectGuard.hpp"

#include <glm/glm.hpp>

#include <fstream>
#include <unordered_map>

class ShaderProgram : public BindableDataObject {
public:
    ShaderProgram() = delete;

    explicit ShaderProgram(Shader& vertexShader, Shader& fragmentShader);

    explicit ShaderProgram(Shader& vertexShader, Shader& fragmentShader, Shader& geometryShader);

    ShaderProgram(const ShaderProgram&) = delete;

    ShaderProgram(ShaderProgram&&) noexcept;

    ShaderProgram& operator=(const ShaderProgram&) = delete;

    ShaderProgram& operator=(ShaderProgram&&) noexcept;

    ~ShaderProgram() noexcept;

    void Bind() override;

    void Unbind() override;

    void SetUniformInt(int uniformId, int v);

    void SetUniformInt(const std::string& name, int v);

    template<glm::length_t N, class T, glm::qualifier Q>
    void SetUniformVector(int uniformId, const glm::vec<N, T, Q>& v) {
        const DataObjectGuard guard{*this};

        if constexpr (N == 1) {
            this->SetUniformFloat(uniformId, v.x);
        }
        else if constexpr (N == 2) {
            this->SetUniformPairFloat(uniformId, v.x, v.y);
        }
        else if constexpr (N == 3) {
            this->SetUniformTripleFloat(uniformId, v.x, v.y, v.z);
        }
        else {
            this->SetUniformQuadroFloat(uniformId, v.x, v.y, v.z, v.w);
        }
    }

    template<glm::length_t N, class T, glm::qualifier Q>
    void SetUniformVector(const std::string& name, const glm::vec<N, T, Q>& v) {
        return this->SetUniformVector(this->GetUniformLocation(name), v);
    }

    template<glm::length_t M, glm::length_t N, class T, glm::qualifier Q>
    void SetUniformMatrix(int uniformId, const glm::mat<M, N, T, Q>& m) {
        const DataObjectGuard guard{*this};
        glUniformMatrix4fv(uniformId, 1, GL_FALSE, &m[0][0]);
    }
    
    template<glm::length_t M, glm::length_t N, class T, glm::qualifier Q>
    void SetUniformMatrix(const std::string& name, const glm::mat<M, N, T, Q>& m) {
        this->SetUniformMatrix(this->GetUniformLocation(name), m);
    }

    void SetUniformFloat(int uniformId, float v);

    void SetUniformFloat(const std::string& name, float v);

    void SetUniformPairFloat(int uniformId, float v1, float v2);

    void SetUniformPairFloat(const std::string& name, float v1, float v2);

    void SetUniformTripleFloat(int uniformId, float v1, float v2, float v3);

    void SetUniformTripleFloat(const std::string& name, float v1, float v2, float v3);

    void SetUniformQuadroFloat(int uniformId, float v1, float v2, float v3, float v4);

    void SetUniformQuadroFloat(const std::string& name, float v1, float v2, float v3, float v4);

    int GetUniformLocation(const std::string& name) const;

private:
    mutable std::unordered_map<std::string, int> uniformLocationCache_;

    void ConstructorHelper_(Shader& vertexShader, Shader& fragmentShader);
    void ConstructorHelper_(Shader& vertexShader, Shader& fragmentShader, Shader& geometryShader);

    void DestroyHelper_() noexcept;

    unsigned CreateShaderProgram_(Shader& vertexShader, Shader& fragmentShader);
    unsigned CreateShaderProgram_(Shader& vertexShader, Shader& fragmentShader, Shader& geometryShader);
};
