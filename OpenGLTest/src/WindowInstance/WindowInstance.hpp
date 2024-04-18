#pragma once
#include <GLFW/glfw3.h>

#include <memory>
#include <string>
#include <functional>
#include <stdexcept>

#include "Control/Control.hpp"
#include "KeyboardInstance/KeyboardInstance.hpp"
#include "MouseInstance/MouseInstance.hpp"

using UniqueGLFWWindowPtr = std::unique_ptr<GLFWwindow, decltype([](GLFWwindow* ptr) { glfwDestroyWindow(ptr); })>;

class WindowInstance {
public:
    using MouseButtonCallbackFunc       = std::function<void(WindowInstance&, MouseInstance::Button, ControlAction, ControlMods, double, double)>;
    using CursorPosCallbackFunc         = std::function<void(WindowInstance&, double, double)>;
    using KeyCallbackFunc               = std::function<void(WindowInstance&, KeyboardInstance::Key, int, ControlAction, ControlMods)>;
    using ScrollCallbackFunc            = std::function<void(WindowInstance&, double, double)>;
    using FrameResizeCallbackFunc       = std::function<void(WindowInstance&, int, int)>;
    using FrameRefreshCallbackFunc      = std::function<void(WindowInstance&)>;
    using LoopCallbackFunc              = std::function<void(WindowInstance&)>;

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

        void Call(WindowInstance& window, MouseInstance::Button button, ControlAction action, ControlMods mods, double xpos, double ypos) {
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

        void Call(WindowInstance& window, double xpos, double ypos) {
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

        void Call(WindowInstance& window, double xpos, double ypos) {
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

        void Call(WindowInstance& window, KeyboardInstance::Key key, int scancode, ControlAction action, ControlMods mods) {
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

        explicit WindowResizeCallback(const FrameResizeCallbackFunc& func)
            : next_(nullptr), func_(func) {

        }

        explicit WindowResizeCallback(const FrameResizeCallbackFunc& func, const std::shared_ptr<WindowResizeCallback>& next)
            : next_(next), func_(func) {

        }

        WindowResizeCallback(const WindowResizeCallback&) = default;

        WindowResizeCallback(WindowResizeCallback&&) noexcept = default;

        WindowResizeCallback& operator=(const WindowResizeCallback&) = default;

        WindowResizeCallback& operator=(WindowResizeCallback&&) noexcept = default;

        ~WindowResizeCallback() = default;

        void Call(WindowInstance& window, int x, int y) {
            if (this->func_ != nullptr) {
                this->func_(window, x, y);
            }

            if (this->next_ != nullptr) {
                this->next_->Call(window, x, y);
            }
        }

        const FrameResizeCallbackFunc& GetFunc() const {
            return this->func_;
        }

        FrameResizeCallbackFunc& GetFunc() {
            return this->func_;
        }

        void SetFunc(const FrameResizeCallbackFunc& func) {
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
        FrameResizeCallbackFunc func_{};
    };

    class WindowRefreshCallback {
    public:
        explicit WindowRefreshCallback() = default;

        explicit WindowRefreshCallback(const FrameRefreshCallbackFunc& func)
            : next_(nullptr), func_(func) {

        }

        explicit WindowRefreshCallback(const FrameRefreshCallbackFunc& func, const std::shared_ptr<WindowRefreshCallback>& next)
            : next_(next), func_(func) {

        }

        WindowRefreshCallback(const WindowRefreshCallback&) = default;

        WindowRefreshCallback(WindowRefreshCallback&&) noexcept = default;

        WindowRefreshCallback& operator=(const WindowRefreshCallback&) = default;

        WindowRefreshCallback& operator=(WindowRefreshCallback&&) noexcept = default;

        ~WindowRefreshCallback() = default;

        void Call(WindowInstance& window) {
            if (this->func_ != nullptr) {
                this->func_(window);
            }

            if (this->next_ != nullptr) {
                this->next_->Call(window);
            }
        }

        const FrameRefreshCallbackFunc& GetFunc() const {
            return this->func_;
        }

        FrameRefreshCallbackFunc& GetFunc() {
            return this->func_;
        }

        void SetFunc(const FrameRefreshCallbackFunc& func) {
            this->func_ = func;
        }

        const std::shared_ptr<WindowRefreshCallback>& GetNext() const {
            return this->next_;
        }

        std::shared_ptr<WindowRefreshCallback>& GetNext() {
            return this->next_;
        }

        void SetNext(const std::shared_ptr<WindowRefreshCallback>& next) {
            this->next_ = next;
        }

    private:
        std::shared_ptr<WindowRefreshCallback> next_{};
        FrameRefreshCallbackFunc func_{};
    };

    class LoopCallback {
    public:
        explicit LoopCallback() = default;

        explicit LoopCallback(const LoopCallbackFunc& func)
            : next_(nullptr), func_(func) {

        }

        explicit LoopCallback(const LoopCallbackFunc& func, const std::shared_ptr<LoopCallback>& next)
            : next_(next), func_(func) {

        }

        LoopCallback(const LoopCallback&) = default;

        LoopCallback(LoopCallback&&) noexcept = default;

        LoopCallback& operator=(const LoopCallback&) = default;

        LoopCallback& operator=(LoopCallback&&) noexcept = default;

        ~LoopCallback() = default;

        void Call(WindowInstance& window) {
            if (this->func_ != nullptr) {
                this->func_(window);
            }

            if (this->next_ != nullptr) {
                this->next_->Call(window);
            }
        }

        const LoopCallbackFunc& GetFunc() const {
            return this->func_;
        }

        LoopCallbackFunc& GetFunc() {
            return this->func_;
        }

        void SetFunc(const LoopCallbackFunc& func) {
            this->func_ = func;
        }

        const std::shared_ptr<LoopCallback>& GetNext() const {
            return this->next_;
        }

        std::shared_ptr<LoopCallback>& GetNext() {
            return this->next_;
        }

        void SetNext(const std::shared_ptr<LoopCallback>& next) {
            this->next_ = next;
        }

    private:
        std::shared_ptr<LoopCallback> next_{};
        LoopCallbackFunc func_{};
    };

    WindowInstance() = delete;

    explicit WindowInstance(int height, int width, const std::string& title);

    WindowInstance(const WindowInstance&) = delete;

    WindowInstance(WindowInstance&& move) noexcept;

    WindowInstance& operator=(const WindowInstance&) = delete;

    WindowInstance& operator=(WindowInstance&& move) noexcept;

    ~WindowInstance() noexcept;

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

    const std::shared_ptr<WindowResizeCallback>& GetResizeCallback() const {
        return this->windowResizeCallback_;
    }

    std::shared_ptr<WindowResizeCallback>& GetResizeCallback() {
        return this->windowResizeCallback_;
    }

    void SetResizeCallback(const std::shared_ptr<WindowResizeCallback>& windowResizeCallback) {
        this->windowResizeCallback_ = windowResizeCallback;
    }

    const std::shared_ptr<WindowRefreshCallback>& GetRefreshCallback() const {
        return this->windowRefreshCallback_;
    }

    std::shared_ptr<WindowRefreshCallback>& GetRefreshCallback() {
        return this->windowRefreshCallback_;
    }

    void SetRefreshCallback(const std::shared_ptr<WindowRefreshCallback>& windowRefreshCallback) {
        this->windowRefreshCallback_ = windowRefreshCallback;
    }

    const std::shared_ptr<LoopCallback>& GetLoopCallback() const {
        return this->loopCallback_;
    }

    std::shared_ptr<LoopCallback>& GetLoopCallback() {
        return this->loopCallback_;
    }

    void SetLoopCallback(const std::shared_ptr<LoopCallback>& loopCallback) {
        this->loopCallback_ = loopCallback;
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

    bool IsMouseClicked(MouseInstance::Button button) const {
        return this->mouse_.IsClicked(button);
    }

    void SetMouseClicked(MouseInstance::Button button) {
        this->mouse_.SetClicked(button);
    }

    void SetMouseUnclicked(MouseInstance::Button button) {
        this->mouse_.SetUnclicked(button);
    }

    bool IsKeyPressed(KeyboardInstance::Key key) const {
        return this->keyboard_.IsPressed(key);
    }

    void SetKeyPressed(KeyboardInstance::Key key) {
        this->keyboard_.SetPressed(key);
    }

    void SetKeyUnpressed(KeyboardInstance::Key key) {
        this->keyboard_.SetUnpressed(key);
    }

    std::pair<double, double> GetCurrCursorPos() const {
        return this->mouse_.GetCurrPos();
    }

    std::pair<double, double> GetPrevCursorPos() const {
        return this->mouse_.GetPrevPos();
    }

    bool ShouldWindowClose() const;
    
    void SwapBuffers() const;

    void PollEvents();

    void WaitEvents();

    void TriggerMouseClick(WindowInstance& window, MouseInstance::Button button, ControlAction action, ControlMods mods, double xpos, double ypos) {
        if (this->mouseClickCallback_ == nullptr) {
            return;
        }

        this->mouseClickCallback_->Call(window, button, action, mods, xpos, ypos);
    }

    void TriggerMouseMove(WindowInstance& window, double xpos, double ypos) {
        if (this->mouseMoveCallback_ == nullptr) {
            return;
        }

        this->mouseMoveCallback_->Call(window, xpos, ypos);
    }

    void TriggerMouseScroll(WindowInstance& window, double xpos, double ypos) {
        if (this->mouseScrollCallback_ == nullptr) {
            return;
        }

        this->mouseScrollCallback_->Call(window, xpos, ypos);
    }

    void TriggerKeyPress(WindowInstance& window, KeyboardInstance::Key key, int scancode, ControlAction action, ControlMods mods) {
        if (this->keyPressCallback_ == nullptr) {
            return;
        }

        this->keyPressCallback_->Call(window, key, scancode, action, mods);
    }

    void TriggerWindowResize(WindowInstance& window, int x, int y) {
        window.SetWidth(x);
        window.SetHeight(y);

        if (this->windowResizeCallback_ == nullptr) {
            return;
        }

        this->windowResizeCallback_->Call(window, x, y);
    }

    void TriggerWindowRefresh(WindowInstance& window) {
        if (this->windowRefreshCallback_ == nullptr) {
            return;
        }

        this->windowRefreshCallback_->Call(window);
    }

    void TriggerLoop(WindowInstance& window) {
        if (this->loopCallback_ == nullptr) {
            return;
        }

        this->loopCallback_->Call(window);
    }

private:
    int height_{};
    int width_{};
    MouseInstance mouse_{};
    KeyboardInstance keyboard_{};
    UniqueGLFWWindowPtr windowHandle_{};

    std::shared_ptr<MouseClickCallback> mouseClickCallback_{};
    std::shared_ptr<MouseMoveCallback> mouseMoveCallback_{};
    std::shared_ptr<MouseScrollCallback> mouseScrollCallback_{};
    std::shared_ptr<KeyPressCallback> keyPressCallback_{};
    std::shared_ptr<WindowResizeCallback> windowResizeCallback_{};
    std::shared_ptr<WindowRefreshCallback> windowRefreshCallback_{};
    std::shared_ptr<LoopCallback> loopCallback_{};

    std::string title_{};

    static WindowInstance* GetUserWindowPtr(GLFWwindow* window);

    static void MouseButtonCallbackFunction_(GLFWwindow* window, int button, int action, int mods);

    static void CursorPosCallbackFunction_(GLFWwindow* window, double xpos, double ypos);

    static void KeyCallbackFunction_(GLFWwindow* window, int key, int scancode, int action, int mods);

    static void ScrollCallbackFunction_(GLFWwindow* window, double xoffset, double yoffset);

    static void FramebufferResizeCallbackFunction_(GLFWwindow* window, int width, int height);

    static void FrameRefreshCallbackFunction_(GLFWwindow* window);

    void ConstructHelper_();

    void MoveHelper_(WindowInstance&& move) noexcept;

    void DestroyHelper_() noexcept;
};
