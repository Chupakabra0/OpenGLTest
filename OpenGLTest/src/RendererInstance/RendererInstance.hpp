#pragma once

#include "VertexArrayObject/VertexArrayObject.hpp"
#include "ShaderProgram/ShaderProgram.hpp"

class RendererInstance {
public:
    static RendererInstance& GetInstance();

    RendererInstance(const RendererInstance&) = delete;

    RendererInstance(RendererInstance&&) noexcept = default;

    RendererInstance& operator=(const RendererInstance&) = delete;

    RendererInstance& operator=(RendererInstance&&) noexcept = default;

    ~RendererInstance() noexcept;

    void ClearScreen(float red, float green, float blue, float a) const;

    void ClearScreen(float red, float green, float blue) const;

    void DrawIndecies(VertexArrayObject& vao, ShaderProgram& shader) const;
    void DrawArrays(VertexArrayObject& vao, ShaderProgram& shader) const;

    std::string GetVersionStr() const;

private:
    explicit RendererInstance();

    void ContructHelper_();

    void DestroyHelper_() noexcept;

    void EnableConfigs_();
};
