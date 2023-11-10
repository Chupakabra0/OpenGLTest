#pragma once
#include "glad/glad.h"

#include "DataObjectGuard.hpp"
#include "VertexArrayObject.hpp"
#include "ShaderProgram.hpp"

class Renderer {
public:
    static Renderer& GetInstance();

    Renderer(const Renderer&) = delete;

    Renderer(Renderer&&) noexcept = default;

    Renderer& operator=(const Renderer&) = delete;

    Renderer& operator=(Renderer&&) noexcept = default;

    ~Renderer() noexcept;

    void ClearScreen(float red, float green, float blue, float a) const;

    void ClearScreen(float red, float green, float blue) const;

    void DrawIndecies(VertexArrayObject& vao, ShaderProgram& shader) const;
    void DrawArrays(VertexArrayObject& vao, ShaderProgram& shader) const;

    std::string GetVersionStr() const;

private:
    explicit Renderer();

    void ContructHelper_();

    void DestroyHelper_() noexcept;

    void EnableConfigs_();
};
