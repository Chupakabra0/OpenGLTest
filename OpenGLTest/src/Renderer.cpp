#include "Renderer.hpp"

Renderer& Renderer::GetInstance() {
    static Renderer renderer;
    return renderer;
}

Renderer::~Renderer() noexcept {
    this->DestroyHelper_();
}

void Renderer::ClearScreen(float red, float green, float blue, float a) const {
    glClearColor(red, green, blue, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::ClearScreen(float red, float green, float blue) const {
    this->ClearScreen(red, green, blue, 1.0f);
}

void Renderer::DrawIndecies(VertexArrayObject& vao, ShaderProgram& shader) const {
    const DataObjectGuard guardVAO{vao};
    const DataObjectGuard guardShader{shader};

    if (vao.GetIBO() == nullptr) {
        throw std::runtime_error("Error: IBO is nullptr!");
    }

    glDrawElements(GL_TRIANGLES, vao.GetIBO()->GetIndexCount(), static_cast<int>(vao.GetIBO()->GetIndexType()), nullptr);
}

void Renderer::DrawArrays(VertexArrayObject& vao, ShaderProgram& shader) const {
    const DataObjectGuard guardVAO{vao};
    const DataObjectGuard guardShader{shader};

    glDrawArrays(GL_TRIANGLES, 0, vao.GetAttributeElement(VertexBufferAttributesType::POSITION).totalDataCount);
}

std::string Renderer::GetVersionStr() const {
    return std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
}

Renderer::Renderer() {
    this->ContructHelper_();
}

void Renderer::ContructHelper_() {
    if (!gladLoadGL()) {
        throw std::runtime_error("GLAD init error!");
    }

    this->EnableConfigs_();
}

void Renderer::DestroyHelper_() noexcept {

}

void Renderer::EnableConfigs_() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
}
