#pragma once
#include "GLFW/glfw3.h"
#include "Mouse.hpp"
#include "Keyboard.hpp"
#include "Control.hpp"

#include <memory>
#include <string>
#include <functional>
#include <stdexcept>
#include <array>
#include <format>
#include <iostream>

using UniqueGLFWWindowPtr = std::unique_ptr<GLFWwindow, decltype([](GLFWwindow* ptr) { glfwDestroyWindow(ptr); })>;

class Window {
public:
    using MouseButtonCallbackFunc       = std::function<void(Window&, Mouse::Button, ControlAction, ControlMods, double, double)>;
    using CursorPosCallbackFunc         = std::function<void(Window&, double, double)>;
    using KeyCallbackFunc               = std::function<void(Window&, Keyboard::Key, int, ControlAction, int)>;
    using ScrollCallbackFunc            = std::function<void(Window&, double, double)>;
    using FramebufferResizeCallbackFunc = std::function<void(Window&, int, int)>;

    class MouseClickCallback {
    public:
        explicit MouseClickCallback() = default;

        explicit MouseClickCallback(const MouseButtonCallbackFunc& func)
            : next_(nullptr), func_(func) {

        }

        explicit MouseClickCallback(const MouseButtonCallbackFunc& func, const std::shared_ptr<MouseClickCallback>& next)
            : next_(next), func_(func) {

        }

        MouseClickCallback(const MouseClickCallback&) = default;

        MouseClickCallback(MouseClickCallback&&) noexcept = default;

        MouseClickCallback& operator=(const MouseClickCallback&) = default;

        MouseClickCallback& operator=(MouseClickCallback&&) noexcept = default;

        ~MouseClickCallback() = default;

        void Call(Window& window, Mouse::Button button, ControlAction action, ControlMods mods, double xpos, double ypos) {
            if (this->func_ != nullptr) {
                this->func_(window, button, action, mods, xpos, ypos);
            }

            if (this->next_ != nullptr) {
                this->next_->Call(window, button, action, mods, xpos, ypos);
            }
        }

        const MouseButtonCallbackFunc& GetFunc() const {
            return this->func_;
        }

        MouseButtonCallbackFunc& GetFunc() {
            return this->func_;
        }

        void SetFunc(const MouseButtonCallbackFunc& func) {
            this->func_ = func;
        }

        const std::shared_ptr<MouseClickCallback>& GetNext() const {
            return this->next_;
        }

        std::shared_ptr<MouseClickCallback>& GetNext() {
            return this->next_;
        }

        void SetNext(const std::shared_ptr<MouseClickCallback>& next) {
            this->next_ = next;
        }

    private:
        std::shared_ptr<MouseClickCallback> next_{};
        MouseButtonCallbackFunc func_{};
    };

    class MouseMoveCallback {
    public:
        explicit MouseMoveCallback() = default;

        explicit MouseMoveCallback(const CursorPosCallbackFunc& func)
            : next_(nullptr), func_(func) {

        }

        explicit MouseMoveCallback(const CursorPosCallbackFunc& func, const std::shared_ptr<MouseMoveCallback>& next)
            : next_(next), func_(func) {

        }

        MouseMoveCallback(const MouseMoveCallback&) = default;

        MouseMoveCallback(MouseMoveCallback&&) noexcept = default;

        MouseMoveCallback& operator=(const MouseMoveCallback&) = default;

        MouseMoveCallback& operator=(MouseMoveCallback&&) noexcept = default;

        ~MouseMoveCallback() = default;

        void Call(Window& window, double xpos, double ypos) {
            if (this->func_ != nullptr) {
                this->func_(window, xpos, ypos);
            }

            if (this->next_ != nullptr) {
                this->next_->Call(window, xpos, ypos);
            }
        }

        const CursorPosCallbackFunc& GetFunc() const {
            return this->func_;
        }

        CursorPosCallbackFunc& GetFunc() {
            return this->func_;
        }

        void SetFunc(const CursorPosCallbackFunc& func) {
            this->func_ = func;
        }

        const std::shared_ptr<MouseMoveCallback>& GetNext() const {
            return this->next_;
        }

        std::shared_ptr<MouseMoveCallback>& GetNext() {
            return this->next_;
        }

        void SetNext(const std::shared_ptr<MouseMoveCallback>& next) {
            this->next_ = next;
        }

    private:
        std::shared_ptr<MouseMoveCallback> next_{};
        CursorPosCallbackFunc func_{};
    };

    class MouseScrollCallback {
    public:
        explicit MouseScrollCallback() = default;

        explicit MouseScrollCallback(const ScrollCallbackFunc& func)
            : next_(nullptr), func_(func) {

        }

        explicit MouseScrollCallback(const ScrollCallbackFunc& func, const std::shared_ptr<MouseScrollCallback>& next)
            : next_(next), func_(func) {

        }

        MouseScrollCallback(const MouseScrollCallback&) = default;

        MouseScrollCallback(MouseScrollCallback&&) noexcept = default;

        MouseScrollCallback& operator=(const MouseScrollCallback&) = default;

        MouseScrollCallback& operator=(MouseScrollCallback&&) noexcept = default;

        ~MouseScrollCallback() = default;

        void Call(Window& window, double xpos, double ypos) {
            if (this->func_ != nullptr) {
                this->func_(window, xpos, ypos);
            }

            if (this->next_ != nullptr) {
                this->next_->Call(window, xpos, ypos);
            }
        }

        const ScrollCallbackFunc& GetFunc() const {
            return this->func_;
        }

        ScrollCallbackFunc& GetFunc() {
            return this->func_;
        }

        void SetFunc(const ScrollCallbackFunc& func) {
            this->func_ = func;
        }

        const std::shared_ptr<MouseScrollCallback>& GetNext() const {
            return this->next_;
        }

        std::shared_ptr<MouseScrollCallback>& GetNext() {
            return this->next_;
        }

        void SetNext(const std::shared_ptr<MouseScrollCallback>& next) {
            this->next_ = next;
        }

    private:
        std::shared_ptr<MouseScrollCallback> next_{};
        ScrollCallbackFunc func_{};
    };

    class KeyPressCallback {
    public:
        explicit KeyPressCallback() = default;

        explicit KeyPressCallback(const KeyCallbackFunc& func)
            : next_(nullptr), func_(func) {

        }

        explicit KeyPressCallback(const KeyCallbackFunc& func, const std::shared_ptr<KeyPressCallback>& next)
            : next_(next), func_(func) {

        }

        KeyPressCallback(const KeyPressCallback&) = default;

        KeyPressCallback(KeyPressCallback&&) noexcept = default;

        KeyPressCallback& operator=(const KeyPressCallback&) = default;

        KeyPressCallback& operator=(KeyPressCallback&&) noexcept = default;

        ~KeyPressCallback() = default;

        void Call(Window& window, Keyboard::Key key, int scancode, ControlAction action, int mods) {
            if (this->func_ != nullptr) {
                this->func_(window, key, scancode, action, mods);
            }

            if (this->next_ != nullptr) {
                this->next_->Call(window, key, scancode, action, mods);
            }
        }

        const KeyCallbackFunc& GetFunc() const {
            return this->func_;
        }

        KeyCallbackFunc& GetFunc() {
            return this->func_;
        }

        void SetFunc(const KeyCallbackFunc& func) {
            this->func_ = func;
        }

        const std::shared_ptr<KeyPressCallback>& GetNext() const {
            return this->next_;
        }

        std::shared_ptr<KeyPressCallback>& GetNext() {
            return this->next_;
        }

        void SetNext(const std::shared_ptr<KeyPressCallback>& next) {
            this->next_ = next;
        }

    private:
        std::shared_ptr<KeyPressCallback> next_{};
        KeyCallbackFunc func_{};
    };

    class WindowResizeCallback {
    public:
        explicit WindowResizeCallback() = default;

        explicit WindowResizeCallback(const FramebufferResizeCallbackFunc& func)
            : next_(nullptr), func_(func) {

        }

        explicit WindowResizeCallback(const FramebufferResizeCallbackFunc& func, const std::shared_ptr<WindowResizeCallback>& next)
            : next_(next), func_(func) {

        }

        WindowResizeCallback(const WindowResizeCallback&) = default;

        WindowResizeCallback(WindowResizeCallback&&) noexcept = default;

        WindowResizeCallback& operator=(const WindowResizeCallback&) = default;

        WindowResizeCallback& operator=(WindowResizeCallback&&) noexcept = default;

        ~WindowResizeCallback() = default;

        void Call(Window& window, int x, int y) {
            if (this->func_ != nullptr) {
                this->func_(window, x, y);
            }

            if (this->next_ != nullptr) {
                this->next_->Call(window, x, y);
            }
        }

        const FramebufferResizeCallbackFunc& GetFunc() const {
            return this->func_;
        }

        FramebufferResizeCallbackFunc& GetFunc() {
            return this->func_;
        }

        void SetFunc(const FramebufferResizeCallbackFunc& func) {
            this->func_ = func;
        }

        const std::shared_ptr<WindowResizeCallback>& GetNext() const {
            return this->next_;
        }

        std::shared_ptr<WindowResizeCallback>& GetNext() {
            return this->next_;
        }

        void SetNext(const std::shared_ptr<WindowResizeCallback>& next) {
            this->next_ = next;
        }

    private:
        std::shared_ptr<WindowResizeCallback> next_{};
        FramebufferResizeCallbackFunc func_{};
    };

    Window() = delete;

    explicit Window(int height, int width, const std::string& title);

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

    const std::shared_ptr<MouseClickCallback>& GetMouseClickCallback() const {
        return this->mouseClickCallback_;
    }

    std::shared_ptr<MouseClickCallback>& GetMouseClickCallback() {
        return this->mouseClickCallback_;
    }

    void SetMouseClickCallback(const std::shared_ptr<MouseClickCallback>& mouseButtonCallback) {
        this->mouseClickCallback_ = mouseButtonCallback;
    }

    const std::shared_ptr<MouseMoveCallback>& GetMouseMoveCallback() const {
        return this->mouseMoveCallback_;
    }

    std::shared_ptr<MouseMoveCallback>& GetMouseMoveCallback() {
        return this->mouseMoveCallback_;
    }

    void SetMouseMoveCallback(const std::shared_ptr<MouseMoveCallback>& mouseMoveCallback) {
        this->mouseMoveCallback_ = mouseMoveCallback;
    }

    const std::shared_ptr<MouseScrollCallback>& GetMouseScrollCallback() const {
        return this->mouseScrollCallback_;
    }

    std::shared_ptr<MouseScrollCallback>& GetMouseScrollCallback() {
        return this->mouseScrollCallback_;
    }

    void SetMouseScrollCallback(const std::shared_ptr<MouseScrollCallback>& mouseScrollCallback) {
        this->mouseScrollCallback_ = mouseScrollCallback;
    }

    const std::shared_ptr<KeyPressCallback>& GetKeyPressCallback() const {
        return this->keyPressCallback_;
    }

    std::shared_ptr<KeyPressCallback>& GetKeyPressCallback() {
        return this->keyPressCallback_;
    }

    void SetKeyPressCallback(const std::shared_ptr<KeyPressCallback>& keyPressCallback) {
        this->keyPressCallback_ = keyPressCallback;
    }

    const std::shared_ptr<WindowResizeCallback>& GetWindowResizeCallback() const {
        return this->windowResizeCallback_;
    }

    std::shared_ptr<WindowResizeCallback>& GetWindowResizeCallback() {
        return this->windowResizeCallback_;
    }

    void SetResizeCallback(const std::shared_ptr<WindowResizeCallback>& windowResizeCallback) {
        this->windowResizeCallback_ = windowResizeCallback;
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

    bool IsMouseClicked(Mouse::Button button) const {
        return this->mouse_.IsClicked(button);
    }

    void SetMouseClicked(Mouse::Button button) {
        this->mouse_.SetClicked(button);
    }

    void SetMouseUnclicked(Mouse::Button button) {
        this->mouse_.SetUnclicked(button);
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

    void TriggerMouseClick(Window& window, Mouse::Button button, ControlAction action, ControlMods mods, double xpos, double ypos) {
        this->mouseClickCallback_->Call(window, button, action, mods, xpos, ypos);
    }

    void TriggerMouseMove(Window& window, double xpos, double ypos) {
        this->mouseMoveCallback_->Call(window, xpos, ypos);
    }

    void TriggerMouseScroll(Window& window, double xpos, double ypos) {
        this->mouseScrollCallback_->Call(window, xpos, ypos);
    }

    void TriggerKeyPress(Window& window, Keyboard::Key key, int scancode, ControlAction action, int mods) {
        this->keyPressCallback_->Call(window, key, scancode, action, mods);
    }

    void TriggerWindowResize(Window& window, int x, int y) {
        window.SetWidth(x);
        window.SetHeight(y);

        this->windowResizeCallback_->Call(window, x, y);
    }

private:
    int height_{};
    int width_{};
    Mouse mouse_{};
    Keyboard keyboard_{};
    UniqueGLFWWindowPtr windowHandle_{};

    std::shared_ptr<MouseClickCallback> mouseClickCallback_{};
    std::shared_ptr<MouseMoveCallback> mouseMoveCallback_{};
    std::shared_ptr<MouseScrollCallback> mouseScrollCallback_{};
    std::shared_ptr<KeyPressCallback> keyPressCallback_{};
    std::shared_ptr<WindowResizeCallback> windowResizeCallback_{};

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
