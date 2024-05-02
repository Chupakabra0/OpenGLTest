#include "ImguiWrapper/ImguiWrapper.hpp"
#include "BindableDataObjectGuard/BindableDataObjectGuard.hpp"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <fstream>
#include <regex>
#include <filesystem>

ImguiWrapper::ImguiWrapper(WindowInstance& window, const std::string& title, float x, float y, float xPivot, float yPivot)
    : title_(title), x_(x), y_(y), xPivot_(xPivot), yPivot_(yPivot) {
    this->ConstructorHelper_(window);
}

void ImguiWrapper::ConstructorHelper_(WindowInstance& window) {
    if (ImGui::CreateContext() == nullptr) {
        throw std::runtime_error("Imgui context creation error");
    }

    this->io_ = UniqueImguiIo(&ImGui::GetIO());
    this->io_->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    this->io_->IniFilename = nullptr;
    //this->io_->ConfigDragClickToInputText |= ImGuiSliderFlags_AlwaysClamp;

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

const ImGuiIO* ImguiWrapper::GetIO() const {
    return this->io_.get();
}

ImGuiIO* ImguiWrapper::GetIO() {
    return this->io_.get();
}

void ImguiWrapper::DrawAll() {
    BindableDataObjectGuard guard{*this};

    this->BeginDrawingWindow_();

    for (const auto& element : this->elements_) {
        element->Draw();
    }

    this->EndDrawingWindow_();
}

void ImguiWrapper::AddElement(const std::string& name, const std::shared_ptr<IImguiElement>& uiElement) {
    //if (this->indexMap_.contains(name)) {
    //    *this->indexMap_.at(name) = uiElement;
    //}
    //else {
        this->elements_.emplace_back(uiElement);
    //    this->indexMap_.emplace(name, this->elements_.rbegin().base());
    //}
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
            str = "Size=450,500";
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

void ImguiWrapper::BeginDrawingWindow_() {
    ImGui::SetNextWindowPos(ImVec2(this->x_, this->y_), ImGuiCond_Appearing, ImVec2(this->xPivot_, this->yPivot_));
    ImGui::Begin(this->title_.c_str());
}

void ImguiWrapper::EndDrawingWindow_() {
    ImGui::End();
}
