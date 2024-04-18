#include "ImguiWrapper.hpp"

#include <fstream>
#include <regex>
#include <filesystem>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

ImguiWrapper::ImguiWrapper(WindowInstance& window) {
    this->ConstructorHelper_(window);
}

void ImguiWrapper::ConstructorHelper_(WindowInstance& window) {
    if (ImGui::CreateContext() == nullptr) {
        throw std::runtime_error("Imgui context creation error");
    }

    this->io_ = &ImGui::GetIO();
    this->io_->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window.GetHandle(), true);
    ImGui_ImplOpenGL3_Init("#version 460 core");

    this->CorrectImguiIni_();
}

void ImguiWrapper::DestroyHelper_() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

ImguiWrapper& ImguiWrapper::GetInstance(WindowInstance& window) {
    static ImguiWrapper imgui{ window };
    return imgui;
}

ImguiWrapper::~ImguiWrapper() {
    this->DestroyHelper_();
}

void ImguiWrapper::Bind() {
    if (this->isBinded_) {
        return;
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    BindableDataObject::Bind();
}

void ImguiWrapper::Unbind() {
    if (!this->isBinded_) {
        return;
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    BindableDataObject::Unbind();
}

ImGuiIO* ImguiWrapper::GetIO() const {
    return this->io_;
}

void ImguiWrapper::CorrectImguiIni_() {
    const std::string ioFilename{"imgui.ini"};
    const std::string tempFilename{ioFilename + ".temp"};

    std::fstream in(ioFilename, std::fstream::in);
    if (!in.is_open()) {
        return;
    }

    std::fstream out(tempFilename, std::fstream::out | std::ios::trunc);
    if (!out.is_open()) {
        return;
    }

    //const std::regex windowRegex{"^\\[Window\\]\\[.*\\]$"};
    const std::regex collapsedRegex{R"(^Collapsed\s*=\s*(\d+?(\.\d+)?)$)"};
    const std::regex sizeRegex{R"(^Size\s*=\s*(\d+?(\.\d+)?)\s*,\s*(\d+?(\.\d+)?)$)"};
    bool isCollapsedWritten = false;

    std::string str{};

    while (std::getline(in, str)) {
        if (std::regex_match(str, collapsedRegex)) {
            str = "Collapsed=1";
            isCollapsedWritten = true;
        }
        else if (std::regex_match(str, sizeRegex)) {
            str = "Size=400,250";
        }

        out << str << '\n';
    }

    if (!isCollapsedWritten) {
        out << "Collapsed=1\n";
    }

    out << std::flush;

    out.close();
    in.close();

    std::filesystem::remove(ioFilename);
    std::filesystem::rename(tempFilename, ioFilename);
}
