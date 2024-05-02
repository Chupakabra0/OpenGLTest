#pragma once
#include "Control/Control.hpp"

#include <unordered_map>

class KeyboardInstance {
public:
    static const int MAX_KEYS_COUNT = 348;

    enum class Key : short {
        UNKNOWN,

        F1, F2, F3, F4, F5,
        F6, F7, F8, F9, F10,
        F11, F12, F13, F14, F15,
        F16, F17, F18, F19, F20,
        F21, F22, F23, F24, F25,

        NUMBER_1, NUMBER_2, NUMBER_3,
        NUMBER_4, NUMBER_5, NUMBER_6,
        NUMBER_7, NUMBER_8, NUMBER_9,
        NUMBER_0, NUMPAD_1, NUMPAD_2,
        NUMPAD_3, NUMPAD_4, NUMPAD_5,
        NUMPAD_6, NUMPAD_7, NUMPAD_8,
        NUMPAD_9, NUMPAD_0,

        Q, W, E, R, T,
        Y, U, I, O, P,
        A, S, D, F, G,
        H, J, K, L, Z,
        X, C, V, B, N,
        M,

        SPACE, APOSTROPHE, COMMA,
        MINUS, PERIOD, SLASH,
        SEMICOLON, EQUAL, MENU,
        LEFT_BRACKET, RIGHT_BRACKET, BACKSLASH,
        GRAVE_ACCENT, WORLD_1, WORLD_2,
        ENTER, TAB, BACKSPACE,
        INSERT, DEL, ARROW_RIGHT,
        ARROW_LEFT, ARROW_DOWN, ARROW_UP,
        PAGE_UP, PAGE_DOWN, HOME,
        END, CAPS_LOCK, SCROLL_LOCK,
        NUM_LOCK, PRINT_SCREEN, PAUSE,
        ESC,

        NUMPAD_DECIMAL, NUMPAD_DIVIDE, NUMPAD_MULTIPLY,
        NUMPAD_SUBTRACT, NUMPAD_ADD, NUMPAD_ENTER,
        NUMPAD_EQUAL,

        LEFT_SHIFT, LEFT_CTRL, LEFT_ALT, LEFT_SUPER,
        RIGHT_SHIFT, RIGHT_CTRL, RIGHT_ALT, RIGHT_SUPER,
    };

    explicit KeyboardInstance() = default;

    KeyboardInstance(const KeyboardInstance&) = default;

    KeyboardInstance(KeyboardInstance&&) noexcept = default;

    KeyboardInstance& operator=(const KeyboardInstance&) = default;

    KeyboardInstance& operator=(KeyboardInstance&&) noexcept = default;

    ~KeyboardInstance() = default;

    void SetPressed(KeyboardInstance::Key key);

    void SetUnpressed(KeyboardInstance::Key key);

    bool IsPressed(KeyboardInstance::Key key) const;

    ControlMods GetMods() const;

    void SetMods(ControlMods mods);

private:
    std::unordered_map<KeyboardInstance::Key, bool> isKeyPressed_{};
    ControlMods mods_{};
};

int ConvertKeyboardKeyToCode(KeyboardInstance::Key key);
KeyboardInstance::Key ConvertCodeToKeyboardKey(int keyCode);
