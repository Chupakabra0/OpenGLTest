#include "Window.hpp"

Window::Window(int height, int width, const std::string& title)
    : height_(height), width_(width), title_(title) {
    this->ConstructHelper_();
}

Window::Window(Window&& move) noexcept {
    this->MoveHelper_(std::move(move));
}

Window& Window::operator=(Window&& move) noexcept {
    this->DestroyHelper_();
    this->MoveHelper_(std::move(move));

    return *this;
}

Window::~Window() noexcept {
    this->DestroyHelper_();
    glfwTerminate();
}

int Window::GetHeight() const {
    return this->height_;
}

void Window::SetHeight(int height) {
    this->height_ = height;
}

int Window::GetWidth() const {
    return this->width_;
}

void Window::SetWidth(int width) {
    this->width_ = width;
}

const UniqueGLFWWindowPtr& Window::GetUniqueHandle() const {
    return this->windowHandle_;
}

UniqueGLFWWindowPtr& Window::GetUniqueHandle() {
    return const_cast<UniqueGLFWWindowPtr&>(const_cast<const Window*>(this)->GetUniqueHandle());
}

const GLFWwindow* Window::GetHandle() const {
    return this->windowHandle_.get();
}

GLFWwindow* Window::GetHandle() {
    return const_cast<GLFWwindow*>(const_cast<const Window*>(this)->GetHandle());
}

const std::string& Window::GetTitle() const {
    return this->title_;
}

void Window::SetTitle(const std::string& title) {
    glfwSetWindowTitle(this->windowHandle_.get(), title.c_str());
    this->title_ = title;
}

bool Window::ShouldWindowClose() const {
    return glfwWindowShouldClose(this->windowHandle_.get());
}

void Window::SwapBuffers() const {
    glfwSwapBuffers(this->windowHandle_.get());
}

void Window::PollEvents() {
    glfwPollEvents();
    this->TriggerLoop(*this);
}

void Window::WaitEvents() {
    glfwWaitEvents();
    this->TriggerLoop(*this);
}

Window* Window::GetUserWindowPtr(GLFWwindow* window) {
    auto* userWindowPtr = glfwGetWindowUserPointer(window);

    if (userWindowPtr == nullptr) {
        throw std::runtime_error("Window ptr is invalid!");
    }

    return reinterpret_cast<Window*>(userWindowPtr);
}

void Window::MouseButtonCallbackFunction_(GLFWwindow* window, int button, int action, int mods) {
    auto* userWindowPtr = Window::GetUserWindowPtr(window);

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

void Window::CursorPosCallbackFunction_(GLFWwindow* window, double xpos, double ypos) {
    auto* userWindowPtr = Window::GetUserWindowPtr(window);

    userWindowPtr->TriggerMouseMove(*userWindowPtr, xpos, ypos);
}

void Window::KeyCallbackFunction_(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto* userWindowPtr = Window::GetUserWindowPtr(window);

    userWindowPtr->TriggerKeyPress(
        *userWindowPtr,
        ConvertCodeToKeyboardKey(key),
        scancode,
        ConvertCodeToControlAction(action),
        ConvertCodeToControlMods(mods)
    );
}

void Window::ScrollCallbackFunction_(GLFWwindow* window, double xoffset, double yoffset) {
    auto* userWindowPtr = Window::GetUserWindowPtr(window);

    userWindowPtr->TriggerMouseScroll(*userWindowPtr, xoffset, yoffset);
}

void Window::FramebufferResizeCallbackFunction_(GLFWwindow* window, int width, int height) {
    auto* userWindowPtr = Window::GetUserWindowPtr(window);

    userWindowPtr->TriggerWindowResize(*userWindowPtr, width, height);
}

void Window::FrameRefreshCallbackFunction_(GLFWwindow* window) {
    auto* userWindowPtr = Window::GetUserWindowPtr(window);

    userWindowPtr->TriggerWindowRefresh(*userWindowPtr);
}

void Window::ConstructHelper_() {
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

    glfwSetMouseButtonCallback(this->windowHandle_.get(), Window::MouseButtonCallbackFunction_);
    glfwSetCursorPosCallback(this->windowHandle_.get(), Window::CursorPosCallbackFunction_);
    glfwSetKeyCallback(this->windowHandle_.get(), Window::KeyCallbackFunction_);
    glfwSetScrollCallback(this->windowHandle_.get(), Window::ScrollCallbackFunction_);
    glfwSetFramebufferSizeCallback(this->windowHandle_.get(), Window::FramebufferResizeCallbackFunction_);
    glfwSetWindowRefreshCallback(this->windowHandle_.get(), Window::FrameRefreshCallbackFunction_);
}

void Window::MoveHelper_(Window&& move) noexcept {
    std::swap(this->height_, move.height_);
    std::swap(this->width_, move.width_);
    std::swap(this->windowHandle_, move.windowHandle_);
    std::swap(this->mouseClickCallback_, move.mouseClickCallback_);
    std::swap(this->mouseMoveCallback_, move.mouseMoveCallback_);
    std::swap(this->mouseScrollCallback_, move.mouseScrollCallback_);
    std::swap(this->keyPressCallback_, move.keyPressCallback_);
    std::swap(this->windowResizeCallback_, move.windowResizeCallback_);
}

void Window::DestroyHelper_() noexcept {
    this->height_ = 0;
    this->width_  = 0;

    this->title_.clear();
    this->windowHandle_.reset();
}
