#pragma once
#include "GLFW/glfw3.h"

#include <memory>
#include <string>
#include <functional>
#include <stdexcept>
#include <array>
#include <format>
#include <iostream>

using UniqueGLFWWindowPtr = std::unique_ptr<GLFWwindow, decltype([](GLFWwindow* ptr) { glfwDestroyWindow(ptr); })>;

class Mouse {
public:
    static const int MAX_BUTTONS_COUNT = 8;

    explicit Mouse() = default;

    Mouse(const Mouse&) = default;

    Mouse(Mouse&&) noexcept = default;

    Mouse& operator=(const Mouse&) = default;

    Mouse& operator=(Mouse&&) noexcept = default;

    ~Mouse() = default;

    void PushNewPos(double x, double y) {
        this->positionX2_ = this->positionX1_;
        this->positionY2_ = this->positionY1_;

        this->positionX1_ = x;
        this->positionY1_ = y;

        std::cout << std::format("X: {} Y: {}\n Xprev: {} Yprev: {}\n", this->positionX1_, this->positionY1_, this->positionX2_, this->positionY2_);
    }

    std::pair<double, double> GetCurrPos() const {
        return std::make_pair(this->positionX1_, this->positionY1_);
    }

    std::pair<double, double> GetPrevPos() const {
        return std::make_pair(this->positionX2_, this->positionY2_);
    }

    void SetClicked(int index) {
        this->isClickedArr_.at(index) = true;
    }

    void SetUnclicked(int index) {
        this->isClickedArr_.at(index) = false;
    }

    bool IsClicked(int index) const {
        return this->isClickedArr_.at(index);
    }

private:
    double positionX2_{};
    double positionY2_{};
    double positionX1_{};
    double positionY1_{};
    std::array<bool, Mouse::MAX_BUTTONS_COUNT> isClickedArr_{};
};

class Window {
public:
    using MouseButtonCallbackFunc       = std::function<void(Window&, int, int, int, double, double)>;
    using CursorPosCallbackFunc         = std::function<void(Window&, double, double)>;
    using KeyCallbackFunc               = std::function<void(Window&, int, int, int, int)>;
    using ScrollCallbackFunc            = std::function<void(Window&, double, double)>;
    using FramebufferResizeCallbackFunc = std::function<void(Window&, int, int)>;

    Window() = delete;

    explicit Window(int height, int width, const std::string& title,
        const MouseButtonCallbackFunc& mouseButtonCallbakFunction = nullptr,
        const CursorPosCallbackFunc& cursorPosCallbackFunction = nullptr,
        const KeyCallbackFunc& keyCallbackFunction = nullptr,
        const ScrollCallbackFunc& scrollCallbackFunction = nullptr,
        const FramebufferResizeCallbackFunc& framebufferResizeCallbackFunction = nullptr);

    Window(const Window&) = delete;

    Window(Window&& move) noexcept;

    Window& operator=(const Window&) = delete;

    Window& operator=(Window&& move) noexcept;

    ~Window() noexcept;

    int GetHeight() const;

    void SetHeight(int height);

    int GetWidth() const;

    void SetWidth(int width);

    const UniqueGLFWWindowPtr& GetUniqueHandle() const;

    UniqueGLFWWindowPtr& GetUniqueHandle();

    const GLFWwindow* GetHandle() const;

    GLFWwindow* GetHandle();

    const std::string& GetTitle() const;

    void SetTitle(const std::string& title);

    void SetMouseButtonCallback(MouseButtonCallbackFunc mouseButtonCallbackFunction) {
        this->mouseButtonCallbackFunction_ = mouseButtonCallbackFunction;
    }

    void SetCursorPosCallback(CursorPosCallbackFunc cursorPosCallbackFunction) {
        this->cursorPosCallbackFunction_ = cursorPosCallbackFunction;
    }

    void SetKeyCallbackFunc(KeyCallbackFunc keyCallbackFunction) {
        this->keyCallbackFunction_ = keyCallbackFunction;
    }

    void SetScrollCallbackFunc(ScrollCallbackFunc scrollCallbackFunction) {
        this->scrollCallbackFunction_ = scrollCallbackFunction;
    }

    void SetFramebufferResizeCallback(FramebufferResizeCallbackFunc framebufferResizeCallbackFunction) {
        this->framebufferResizeCallbackFunction_ = framebufferResizeCallbackFunction;
    }

    void UpdateCursorPosition() {
        double xpos{}, ypos{};
        glfwGetCursorPos(this->GetHandle(), &xpos, &ypos);
        this->mouse_.PushNewPos(xpos, ypos);
    }

    void ResetCursorPosition() {
        this->mouse_.PushNewPos(0.0, 0.0);
        this->mouse_.PushNewPos(0.0, 0.0);
    }

    bool IsMouseClicked(int index) const {
        return this->mouse_.IsClicked(index);
    }

    void SetMouseClicked(int index) {
        this->mouse_.SetClicked(index);
    }

    void SetMouseUnclicked(int index) {
        this->mouse_.SetUnclicked(index);
    }

    std::pair<double, double> GetCurrCursorPos() const {
        return this->mouse_.GetCurrPos();
    }

    std::pair<double, double> GetPrevCursorPos() const {
        return this->mouse_.GetPrevPos();
    }

    bool ShouldWindowClose() const;
    
    void SwapBuffers() const;

    void PollEvents() const;

    void WaitEvents() const;

private:
    int height_{};
    int width_{};
    Mouse mouse_{};
    UniqueGLFWWindowPtr windowHandle_{};
    MouseButtonCallbackFunc mouseButtonCallbackFunction_{};
    CursorPosCallbackFunc cursorPosCallbackFunction_{};
    KeyCallbackFunc keyCallbackFunction_{};
    ScrollCallbackFunc scrollCallbackFunction_{};
    FramebufferResizeCallbackFunc framebufferResizeCallbackFunction_{};

    std::string title_{};

    static Window* GetUserWindowPtr(GLFWwindow* window);

    static void MouseButtonCallbackFunction_(GLFWwindow* window, int button, int action, int mods);

    static void CursorPosCallbackFunction_(GLFWwindow* window, double xpos, double ypos);

    static void KeyCallbackFunction_(GLFWwindow* window, int key, int scancode, int action, int mods);

    static void ScrollCallbackFunction_(GLFWwindow* window, double xoffset, double yoffset);

    static void FramebufferResizeCallbackFunction_(GLFWwindow* window, int width, int height);

    void ConstructHelper_();

    void MoveHelper_(Window&& move) noexcept;

    void DestroyHelper_() noexcept;
};
