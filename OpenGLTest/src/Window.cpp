#include "Window.hpp"

Window::Window(int height, int width, const std::string& title,
    const MouseButtonCallbackFunc& mouseButtonCallbakFunction /*= nullptr*/,
    const CursorPosCallbackFunc& cursorPosCallbackFunction /*= nullptr*/,
    const KeyCallbackFunc& keyCallbackFunction /*= nullptr*/,
    const ScrollCallbackFunc& scrollCallbackFunction /*= nullptr*/,
    const FramebufferResizeCallbackFunc& framebufferResizeCallbackFunction /*= nullptr*/)
    : height_(height), width_(width), title_(title),
    mouseButtonCallbackFunction_(mouseButtonCallbakFunction),
    cursorPosCallbackFunction_(cursorPosCallbackFunction),
    keyCallbackFunction_(keyCallbackFunction),
    scrollCallbackFunction_(scrollCallbackFunction),
    framebufferResizeCallbackFunction_(framebufferResizeCallbackFunction) {
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

void Window::PollEvents() const {
    glfwPollEvents();
}

void Window::WaitEvents() const {
    glfwWaitEvents();
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

    if (userWindowPtr == nullptr || !userWindowPtr->mouseButtonCallbackFunction_) {
        return;
    }

    double xpos{}, ypos{};
    glfwGetCursorPos(window, &xpos, &ypos);

    userWindowPtr->mouseButtonCallbackFunction_(*userWindowPtr, button, action, mods, xpos, ypos);
}

void Window::CursorPosCallbackFunction_(GLFWwindow* window, double xpos, double ypos) {
    auto* userWindowPtr = Window::GetUserWindowPtr(window);

    if (userWindowPtr == nullptr || !userWindowPtr->cursorPosCallbackFunction_) {
        return;
    }

    userWindowPtr->cursorPosCallbackFunction_(*userWindowPtr, xpos, ypos);
}

void Window::KeyCallbackFunction_(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto* userWindowPtr = Window::GetUserWindowPtr(window);

    if (userWindowPtr == nullptr || !userWindowPtr->keyCallbackFunction_) {
        return;
    }

    userWindowPtr->keyCallbackFunction_(*userWindowPtr, key, scancode, action, mods);
}

void Window::ScrollCallbackFunction_(GLFWwindow* window, double xoffset, double yoffset) {
    auto* userWindowPtr = Window::GetUserWindowPtr(window);

    if (userWindowPtr == nullptr || !userWindowPtr->scrollCallbackFunction_) {
        return;
    }

    userWindowPtr->scrollCallbackFunction_(*userWindowPtr, xoffset, yoffset);
}

void Window::FramebufferResizeCallbackFunction_(GLFWwindow* window, int width, int height) {
    auto* userWindowPtr = Window::GetUserWindowPtr(window);

    if (userWindowPtr == nullptr || !userWindowPtr->scrollCallbackFunction_) {
        return;
    }

    userWindowPtr->framebufferResizeCallbackFunction_(*userWindowPtr, width, height);
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
}

void Window::MoveHelper_(Window&& move) noexcept {
    std::swap(this->height_, move.height_);
    std::swap(this->width_, move.width_);
    std::swap(this->windowHandle_, move.windowHandle_);
    std::swap(this->mouseButtonCallbackFunction_, move.mouseButtonCallbackFunction_);
    std::swap(this->keyCallbackFunction_, move.keyCallbackFunction_);
    std::swap(this->scrollCallbackFunction_, move.scrollCallbackFunction_);
}

void Window::DestroyHelper_() noexcept {
    this->height_ = 0;
    this->width_  = 0;

    this->title_.clear();
    this->windowHandle_.reset();

    this->mouseButtonCallbackFunction_ = nullptr;
    this->keyCallbackFunction_ = nullptr;
    this->scrollCallbackFunction_ = nullptr;
}
