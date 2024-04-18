#include "WindowInstance/WindowInstance.hpp"

WindowInstance::WindowInstance(int height, int width, const std::string& title)
    : height_(height), width_(width), title_(title) {
    this->ConstructHelper_();
}

WindowInstance::WindowInstance(WindowInstance&& move) noexcept {
    this->MoveHelper_(std::move(move));
}

WindowInstance& WindowInstance::operator=(WindowInstance&& move) noexcept {
    this->DestroyHelper_();
    this->MoveHelper_(std::move(move));

    return *this;
}

WindowInstance::~WindowInstance() noexcept {
    this->DestroyHelper_();
    glfwTerminate();
}

int WindowInstance::GetHeight() const {
    return this->height_;
}

void WindowInstance::SetHeight(int height) {
    this->height_ = height;
}

int WindowInstance::GetWidth() const {
    return this->width_;
}

void WindowInstance::SetWidth(int width) {
    this->width_ = width;
}

const UniqueGLFWWindowPtr& WindowInstance::GetUniqueHandle() const {
    return this->windowHandle_;
}

UniqueGLFWWindowPtr& WindowInstance::GetUniqueHandle() {
    return const_cast<UniqueGLFWWindowPtr&>(const_cast<const WindowInstance*>(this)->GetUniqueHandle());
}

const GLFWwindow* WindowInstance::GetHandle() const {
    return this->windowHandle_.get();
}

GLFWwindow* WindowInstance::GetHandle() {
    return const_cast<GLFWwindow*>(const_cast<const WindowInstance*>(this)->GetHandle());
}

const std::string& WindowInstance::GetTitle() const {
    return this->title_;
}

void WindowInstance::SetTitle(const std::string& title) {
    glfwSetWindowTitle(this->windowHandle_.get(), title.c_str());
    this->title_ = title;
}

bool WindowInstance::ShouldWindowClose() const {
    return glfwWindowShouldClose(this->windowHandle_.get());
}

void WindowInstance::SwapBuffers() const {
    glfwSwapBuffers(this->windowHandle_.get());
}

void WindowInstance::PollEvents() {
    glfwPollEvents();
    this->TriggerLoop(*this);
}

void WindowInstance::WaitEvents() {
    glfwWaitEvents();
    this->TriggerLoop(*this);
}

WindowInstance* WindowInstance::GetUserWindowPtr(GLFWwindow* window) {
    auto* userWindowPtr = glfwGetWindowUserPointer(window);

    if (userWindowPtr == nullptr) {
        throw std::runtime_error("Window ptr is invalid!");
    }

    return reinterpret_cast<WindowInstance*>(userWindowPtr);
}

void WindowInstance::MouseButtonCallbackFunction_(GLFWwindow* window, int button, int action, int mods) {
    auto* userWindowPtr = WindowInstance::GetUserWindowPtr(window);

    double xpos{}, ypos{};
    glfwGetCursorPos(window, &xpos, &ypos);

    userWindowPtr->TriggerMouseClick(
        *userWindowPtr,
        ConvertCodeToMouseButton(button),
        ConvertCodeToControlAction(action),
        ConvertCodeToControlMods(mods),
        xpos, ypos
    );
}

void WindowInstance::CursorPosCallbackFunction_(GLFWwindow* window, double xpos, double ypos) {
    auto* userWindowPtr = WindowInstance::GetUserWindowPtr(window);

    userWindowPtr->TriggerMouseMove(*userWindowPtr, xpos, ypos);
}

void WindowInstance::KeyCallbackFunction_(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto* userWindowPtr = WindowInstance::GetUserWindowPtr(window);

    userWindowPtr->TriggerKeyPress(
        *userWindowPtr,
        ConvertCodeToKeyboardKey(key),
        scancode,
        ConvertCodeToControlAction(action),
        ConvertCodeToControlMods(mods)
    );
}

void WindowInstance::ScrollCallbackFunction_(GLFWwindow* window, double xoffset, double yoffset) {
    auto* userWindowPtr = WindowInstance::GetUserWindowPtr(window);

    userWindowPtr->TriggerMouseScroll(*userWindowPtr, xoffset, yoffset);
}

void WindowInstance::FramebufferResizeCallbackFunction_(GLFWwindow* window, int width, int height) {
    auto* userWindowPtr = WindowInstance::GetUserWindowPtr(window);

    userWindowPtr->TriggerWindowResize(*userWindowPtr, width, height);
}

void WindowInstance::FrameRefreshCallbackFunction_(GLFWwindow* window) {
    auto* userWindowPtr = WindowInstance::GetUserWindowPtr(window);

    userWindowPtr->TriggerWindowRefresh(*userWindowPtr);
}

void WindowInstance::ConstructHelper_() {
    if (!glfwInit()) {
        throw std::runtime_error("GLFW init error");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->windowHandle_ = UniqueGLFWWindowPtr{
        glfwCreateWindow(this->width_, this->height_, this->title_.c_str(), nullptr, nullptr)
    };

    glfwMakeContextCurrent(this->windowHandle_.get());
    glfwSwapInterval(0);

    glfwSetWindowUserPointer(this->windowHandle_.get(), this);

    glfwSetMouseButtonCallback(this->windowHandle_.get(), WindowInstance::MouseButtonCallbackFunction_);
    glfwSetCursorPosCallback(this->windowHandle_.get(), WindowInstance::CursorPosCallbackFunction_);
    glfwSetKeyCallback(this->windowHandle_.get(), WindowInstance::KeyCallbackFunction_);
    glfwSetScrollCallback(this->windowHandle_.get(), WindowInstance::ScrollCallbackFunction_);
    glfwSetFramebufferSizeCallback(this->windowHandle_.get(), WindowInstance::FramebufferResizeCallbackFunction_);
    glfwSetWindowRefreshCallback(this->windowHandle_.get(), WindowInstance::FrameRefreshCallbackFunction_);
}

void WindowInstance::MoveHelper_(WindowInstance&& move) noexcept {
    std::swap(this->height_, move.height_);
    std::swap(this->width_, move.width_);
    std::swap(this->windowHandle_, move.windowHandle_);
    std::swap(this->mouseClickCallback_, move.mouseClickCallback_);
    std::swap(this->mouseMoveCallback_, move.mouseMoveCallback_);
    std::swap(this->mouseScrollCallback_, move.mouseScrollCallback_);
    std::swap(this->keyPressCallback_, move.keyPressCallback_);
    std::swap(this->windowResizeCallback_, move.windowResizeCallback_);
}

void WindowInstance::DestroyHelper_() noexcept {
    this->height_ = 0;
    this->width_  = 0;

    this->title_.clear();
    this->windowHandle_.reset();
}
