#pragma once
#include "Control.hpp"

#include <array>

class Keyboard {
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

    explicit Keyboard() = default;

    Keyboard(const Keyboard&) = default;

    Keyboard(Keyboard&&) noexcept = default;

    Keyboard& operator=(const Keyboard&) = default;

    Keyboard& operator=(Keyboard&&) noexcept = default;

    ~Keyboard() = default;

    void SetPressed(Keyboard::Key key) {
        this->isKeyPressed_[key] = true;
    }

    void SetUnpressed(Keyboard::Key key) {
        this->isKeyPressed_[key] = false;
    }

    bool IsPressed(Keyboard::Key key) const {
        const auto find = this->isKeyPressed_.find(key);

        return find != this->isKeyPressed_.end() ?
            find->second :
            false;
    }

    ControlMods GetMods() const {
        return this->mods_;
    }

    void SetMods(ControlMods mods) {
        this->mods_ = mods;
    }

private:
    std::unordered_map<Keyboard::Key, bool> isKeyPressed_{};
    ControlMods mods_{};
};

inline int ConvertKeyboardKeyToCode(Keyboard::Key key);
inline Keyboard::Key ConvertCodeToKeyboardKey(int keyCode);

#if defined(CONTROL_GLFW)
    int ConvertKeyboardKeyToCode(Keyboard::Key key) {
        switch (key) {
            case Keyboard::Key::ESC:                return GLFW_KEY_ESCAPE;
            case Keyboard::Key::ENTER:              return GLFW_KEY_ENTER;
            case Keyboard::Key::TAB:                return GLFW_KEY_TAB;
            case Keyboard::Key::BACKSPACE:          return GLFW_KEY_BACKSPACE;
            case Keyboard::Key::INSERT:             return GLFW_KEY_INSERT;
            case Keyboard::Key::DEL:                return GLFW_KEY_DELETE;
            case Keyboard::Key::ARROW_RIGHT:        return GLFW_KEY_RIGHT;
            case Keyboard::Key::ARROW_LEFT:         return GLFW_KEY_LEFT;
            case Keyboard::Key::ARROW_DOWN:         return GLFW_KEY_DOWN;
            case Keyboard::Key::ARROW_UP:           return GLFW_KEY_UP;
            case Keyboard::Key::PAGE_UP:            return GLFW_KEY_PAGE_UP;
            case Keyboard::Key::PAGE_DOWN:          return GLFW_KEY_PAGE_DOWN;
            case Keyboard::Key::HOME:               return GLFW_KEY_HOME;
            case Keyboard::Key::END:                return GLFW_KEY_END;
            case Keyboard::Key::CAPS_LOCK:          return GLFW_KEY_CAPS_LOCK;
            case Keyboard::Key::SCROLL_LOCK:        return GLFW_KEY_SCROLL_LOCK;
            case Keyboard::Key::NUM_LOCK:           return GLFW_KEY_NUM_LOCK;
            case Keyboard::Key::PRINT_SCREEN:       return GLFW_KEY_PRINT_SCREEN;
            case Keyboard::Key::PAUSE:              return GLFW_KEY_PAUSE;
            case Keyboard::Key::F1:                 return GLFW_KEY_F1;
            case Keyboard::Key::F2:                 return GLFW_KEY_F2;
            case Keyboard::Key::F3:                 return GLFW_KEY_F3;
            case Keyboard::Key::F4:                 return GLFW_KEY_F4;
            case Keyboard::Key::F5:                 return GLFW_KEY_F5;
            case Keyboard::Key::F6:                 return GLFW_KEY_F6;
            case Keyboard::Key::F7:                 return GLFW_KEY_F7;
            case Keyboard::Key::F8:                 return GLFW_KEY_F8;
            case Keyboard::Key::F9:                 return GLFW_KEY_F9;
            case Keyboard::Key::F10:                return GLFW_KEY_F10;
            case Keyboard::Key::F11:                return GLFW_KEY_F11;
            case Keyboard::Key::F12:                return GLFW_KEY_F12;
            case Keyboard::Key::F13:                return GLFW_KEY_F13;
            case Keyboard::Key::F14:                return GLFW_KEY_F14;
            case Keyboard::Key::F15:                return GLFW_KEY_F15;
            case Keyboard::Key::F16:                return GLFW_KEY_F16;
            case Keyboard::Key::F17:                return GLFW_KEY_F17;
            case Keyboard::Key::F18:                return GLFW_KEY_F18;
            case Keyboard::Key::F19:                return GLFW_KEY_F19;
            case Keyboard::Key::F20:                return GLFW_KEY_F20;
            case Keyboard::Key::F21:                return GLFW_KEY_F21;
            case Keyboard::Key::F22:                return GLFW_KEY_F22;
            case Keyboard::Key::F23:                return GLFW_KEY_F23;
            case Keyboard::Key::F24:                return GLFW_KEY_F24;
            case Keyboard::Key::F25:                return GLFW_KEY_F25;
            case Keyboard::Key::NUMPAD_0:           return GLFW_KEY_KP_0;
            case Keyboard::Key::NUMPAD_1:           return GLFW_KEY_KP_1;
            case Keyboard::Key::NUMPAD_2:           return GLFW_KEY_KP_2;
            case Keyboard::Key::NUMPAD_3:           return GLFW_KEY_KP_3;
            case Keyboard::Key::NUMPAD_4:           return GLFW_KEY_KP_4;
            case Keyboard::Key::NUMPAD_5:           return GLFW_KEY_KP_5;
            case Keyboard::Key::NUMPAD_6:           return GLFW_KEY_KP_6;
            case Keyboard::Key::NUMPAD_7:           return GLFW_KEY_KP_7;
            case Keyboard::Key::NUMPAD_8:           return GLFW_KEY_KP_8;
            case Keyboard::Key::NUMPAD_9:           return GLFW_KEY_KP_9;
            case Keyboard::Key::NUMPAD_DECIMAL:     return GLFW_KEY_KP_DECIMAL;
            case Keyboard::Key::NUMPAD_DIVIDE:      return GLFW_KEY_KP_DIVIDE;
            case Keyboard::Key::NUMPAD_MULTIPLY:    return GLFW_KEY_KP_MULTIPLY;
            case Keyboard::Key::NUMPAD_SUBTRACT:    return GLFW_KEY_KP_SUBTRACT;
            case Keyboard::Key::NUMPAD_ADD:         return GLFW_KEY_KP_ADD;
            case Keyboard::Key::NUMPAD_ENTER:       return GLFW_KEY_KP_ENTER;
            case Keyboard::Key::NUMPAD_EQUAL:       return GLFW_KEY_KP_EQUAL;
            case Keyboard::Key::LEFT_SHIFT:         return GLFW_KEY_LEFT_SHIFT;
            case Keyboard::Key::LEFT_CTRL:          return GLFW_KEY_LEFT_CONTROL;
            case Keyboard::Key::LEFT_ALT:           return GLFW_KEY_LEFT_ALT;
            case Keyboard::Key::LEFT_SUPER:         return GLFW_KEY_LEFT_SUPER;
            case Keyboard::Key::RIGHT_SHIFT:        return GLFW_KEY_RIGHT_SHIFT;
            case Keyboard::Key::RIGHT_CTRL:         return GLFW_KEY_RIGHT_CONTROL;
            case Keyboard::Key::RIGHT_ALT:          return GLFW_KEY_RIGHT_ALT;
            case Keyboard::Key::RIGHT_SUPER:        return GLFW_KEY_RIGHT_SUPER;
            case Keyboard::Key::MENU:               return GLFW_KEY_MENU;
            case Keyboard::Key::SPACE:              return GLFW_KEY_SPACE;
            case Keyboard::Key::APOSTROPHE:         return GLFW_KEY_APOSTROPHE;     /* ' */
            case Keyboard::Key::COMMA:              return GLFW_KEY_COMMA;          /* , */
            case Keyboard::Key::MINUS:              return GLFW_KEY_MINUS;          /* - */
            case Keyboard::Key::PERIOD:             return GLFW_KEY_PERIOD;         /* . */
            case Keyboard::Key::SLASH:              return GLFW_KEY_SLASH;          /* / */
            case Keyboard::Key::NUMBER_0:           return GLFW_KEY_0;
            case Keyboard::Key::NUMBER_1:           return GLFW_KEY_1;
            case Keyboard::Key::NUMBER_2:           return GLFW_KEY_2;
            case Keyboard::Key::NUMBER_3:           return GLFW_KEY_3;
            case Keyboard::Key::NUMBER_4:           return GLFW_KEY_4;
            case Keyboard::Key::NUMBER_5:           return GLFW_KEY_5;
            case Keyboard::Key::NUMBER_6:           return GLFW_KEY_6;
            case Keyboard::Key::NUMBER_7:           return GLFW_KEY_7;
            case Keyboard::Key::NUMBER_8:           return GLFW_KEY_8;
            case Keyboard::Key::NUMBER_9:           return GLFW_KEY_9;
            case Keyboard::Key::SEMICOLON:          return GLFW_KEY_SEMICOLON;      /*; */
            case Keyboard::Key::EQUAL:              return GLFW_KEY_EQUAL;          /* = */
            case Keyboard::Key::A:                  return GLFW_KEY_A;
            case Keyboard::Key::B:                  return GLFW_KEY_B;
            case Keyboard::Key::C:                  return GLFW_KEY_C;
            case Keyboard::Key::D:                  return GLFW_KEY_D;
            case Keyboard::Key::E:                  return GLFW_KEY_E;
            case Keyboard::Key::F:                  return GLFW_KEY_F;
            case Keyboard::Key::G:                  return GLFW_KEY_G;
            case Keyboard::Key::H:                  return GLFW_KEY_H;
            case Keyboard::Key::I:                  return GLFW_KEY_I;
            case Keyboard::Key::J:                  return GLFW_KEY_J;
            case Keyboard::Key::K:                  return GLFW_KEY_K;
            case Keyboard::Key::L:                  return GLFW_KEY_L;
            case Keyboard::Key::M:                  return GLFW_KEY_M;
            case Keyboard::Key::N:                  return GLFW_KEY_N;
            case Keyboard::Key::O:                  return GLFW_KEY_O;
            case Keyboard::Key::P:                  return GLFW_KEY_P;
            case Keyboard::Key::Q:                  return GLFW_KEY_Q;
            case Keyboard::Key::R:                  return GLFW_KEY_R;
            case Keyboard::Key::S:                  return GLFW_KEY_S;
            case Keyboard::Key::T:                  return GLFW_KEY_T;
            case Keyboard::Key::U:                  return GLFW_KEY_U;
            case Keyboard::Key::V:                  return GLFW_KEY_V;
            case Keyboard::Key::W:                  return GLFW_KEY_W;
            case Keyboard::Key::X:                  return GLFW_KEY_X;
            case Keyboard::Key::Y:                  return GLFW_KEY_Y;
            case Keyboard::Key::Z:                  return GLFW_KEY_Z;
            case Keyboard::Key::LEFT_BRACKET:       return GLFW_KEY_LEFT_BRACKET;   /* [ */
            case Keyboard::Key::BACKSLASH:          return GLFW_KEY_BACKSLASH;      /* \ */
            case Keyboard::Key::RIGHT_BRACKET:      return GLFW_KEY_RIGHT_BRACKET;  /* ] */
            case Keyboard::Key::GRAVE_ACCENT:       return GLFW_KEY_GRAVE_ACCENT;   /* ` */
            case Keyboard::Key::WORLD_1:            return GLFW_KEY_WORLD_1;        /* non-US #1 */
            case Keyboard::Key::WORLD_2:            return GLFW_KEY_WORLD_2;        /* non-US #2 */
            default:                                return GLFW_KEY_UNKNOWN;
        }
    }

    Keyboard::Key ConvertCodeToKeyboardKey(int keyCode) {
        switch (keyCode) {
            case GLFW_KEY_ESCAPE:                   return Keyboard::Key::ESC;
            case GLFW_KEY_ENTER:                    return Keyboard::Key::ENTER;
            case GLFW_KEY_TAB:                      return Keyboard::Key::TAB;
            case GLFW_KEY_BACKSPACE:                return Keyboard::Key::BACKSPACE;
            case GLFW_KEY_INSERT:                   return Keyboard::Key::INSERT;
            case GLFW_KEY_DELETE:                   return Keyboard::Key::DEL;
            case GLFW_KEY_RIGHT:                    return Keyboard::Key::ARROW_RIGHT;
            case GLFW_KEY_LEFT:                     return Keyboard::Key::ARROW_LEFT;
            case GLFW_KEY_DOWN:                     return Keyboard::Key::ARROW_DOWN;
            case GLFW_KEY_UP:                       return Keyboard::Key::ARROW_UP;
            case GLFW_KEY_PAGE_UP:                  return Keyboard::Key::PAGE_UP;
            case GLFW_KEY_PAGE_DOWN:                return Keyboard::Key::PAGE_DOWN;
            case GLFW_KEY_HOME:                     return Keyboard::Key::HOME;
            case GLFW_KEY_END:                      return Keyboard::Key::END;
            case GLFW_KEY_CAPS_LOCK:                return Keyboard::Key::CAPS_LOCK;
            case GLFW_KEY_SCROLL_LOCK:              return Keyboard::Key::SCROLL_LOCK;
            case GLFW_KEY_NUM_LOCK:                 return Keyboard::Key::NUM_LOCK;
            case GLFW_KEY_PRINT_SCREEN:             return Keyboard::Key::PRINT_SCREEN;
            case GLFW_KEY_PAUSE:                    return Keyboard::Key::PAUSE;
            case GLFW_KEY_F1:                       return Keyboard::Key::F1;
            case GLFW_KEY_F2:                       return Keyboard::Key::F2;
            case GLFW_KEY_F3:                       return Keyboard::Key::F3;
            case GLFW_KEY_F4:                       return Keyboard::Key::F4;
            case GLFW_KEY_F5:                       return Keyboard::Key::F5;
            case GLFW_KEY_F6:                       return Keyboard::Key::F6;
            case GLFW_KEY_F7:                       return Keyboard::Key::F7;
            case GLFW_KEY_F8:                       return Keyboard::Key::F8;
            case GLFW_KEY_F9:                       return Keyboard::Key::F9;
            case GLFW_KEY_F10:                      return Keyboard::Key::F10;
            case GLFW_KEY_F11:                      return Keyboard::Key::F11;
            case GLFW_KEY_F12:                      return Keyboard::Key::F12;
            case GLFW_KEY_F13:                      return Keyboard::Key::F13;
            case GLFW_KEY_F14:                      return Keyboard::Key::F14;
            case GLFW_KEY_F15:                      return Keyboard::Key::F15;
            case GLFW_KEY_F16:                      return Keyboard::Key::F16;
            case GLFW_KEY_F17:                      return Keyboard::Key::F17;
            case GLFW_KEY_F18:                      return Keyboard::Key::F18;
            case GLFW_KEY_F19:                      return Keyboard::Key::F19;
            case GLFW_KEY_F20:                      return Keyboard::Key::F20;
            case GLFW_KEY_F21:                      return Keyboard::Key::F21;
            case GLFW_KEY_F22:                      return Keyboard::Key::F22;
            case GLFW_KEY_F23:                      return Keyboard::Key::F23;
            case GLFW_KEY_F24:                      return Keyboard::Key::F24;
            case GLFW_KEY_F25:                      return Keyboard::Key::F25;
            case GLFW_KEY_KP_0:                     return Keyboard::Key::NUMPAD_0;
            case GLFW_KEY_KP_1:                     return Keyboard::Key::NUMPAD_1;
            case GLFW_KEY_KP_2:                     return Keyboard::Key::NUMPAD_2;
            case GLFW_KEY_KP_3:                     return Keyboard::Key::NUMPAD_3;
            case GLFW_KEY_KP_4:                     return Keyboard::Key::NUMPAD_4;
            case GLFW_KEY_KP_5:                     return Keyboard::Key::NUMPAD_5;
            case GLFW_KEY_KP_6:                     return Keyboard::Key::NUMPAD_6;
            case GLFW_KEY_KP_7:                     return Keyboard::Key::NUMPAD_7;
            case GLFW_KEY_KP_8:                     return Keyboard::Key::NUMPAD_8;
            case GLFW_KEY_KP_9:                     return Keyboard::Key::NUMPAD_9;
            case GLFW_KEY_KP_DECIMAL:               return Keyboard::Key::NUMPAD_DECIMAL;
            case GLFW_KEY_KP_DIVIDE:                return Keyboard::Key::NUMPAD_DIVIDE;
            case GLFW_KEY_KP_MULTIPLY:              return Keyboard::Key::NUMPAD_MULTIPLY;
            case GLFW_KEY_KP_SUBTRACT:              return Keyboard::Key::NUMPAD_SUBTRACT;
            case GLFW_KEY_KP_ADD:                   return Keyboard::Key::NUMPAD_ADD;
            case GLFW_KEY_KP_ENTER:                 return Keyboard::Key::NUMPAD_ENTER;
            case GLFW_KEY_KP_EQUAL:                 return Keyboard::Key::NUMPAD_EQUAL;
            case GLFW_KEY_LEFT_SHIFT:               return Keyboard::Key::LEFT_SHIFT;
            case GLFW_KEY_LEFT_CONTROL:             return Keyboard::Key::LEFT_CTRL;
            case GLFW_KEY_LEFT_ALT:                 return Keyboard::Key::LEFT_ALT;
            case GLFW_KEY_LEFT_SUPER:               return Keyboard::Key::LEFT_SUPER;
            case GLFW_KEY_RIGHT_SHIFT:              return Keyboard::Key::RIGHT_SHIFT;
            case GLFW_KEY_RIGHT_CONTROL:            return Keyboard::Key::RIGHT_CTRL;
            case GLFW_KEY_RIGHT_ALT:                return Keyboard::Key::RIGHT_ALT;
            case GLFW_KEY_RIGHT_SUPER:              return Keyboard::Key::RIGHT_SUPER;
            case GLFW_KEY_MENU:                     return Keyboard::Key::MENU;
            case GLFW_KEY_SPACE:                    return Keyboard::Key::SPACE;
            case GLFW_KEY_APOSTROPHE:               return Keyboard::Key::APOSTROPHE;       /* ' */
            case GLFW_KEY_COMMA:                    return Keyboard::Key::COMMA;            /* , */
            case GLFW_KEY_MINUS:                    return Keyboard::Key::MINUS;            /* - */
            case GLFW_KEY_PERIOD:                   return Keyboard::Key::PERIOD;           /* . */
            case GLFW_KEY_SLASH:                    return Keyboard::Key::SLASH;            /* / */
            case GLFW_KEY_0:                        return Keyboard::Key::NUMBER_0;
            case GLFW_KEY_1:                        return Keyboard::Key::NUMBER_1;
            case GLFW_KEY_2:                        return Keyboard::Key::NUMBER_2;
            case GLFW_KEY_3:                        return Keyboard::Key::NUMBER_3;
            case GLFW_KEY_4:                        return Keyboard::Key::NUMBER_4;
            case GLFW_KEY_5:                        return Keyboard::Key::NUMBER_5;
            case GLFW_KEY_6:                        return Keyboard::Key::NUMBER_6;
            case GLFW_KEY_7:                        return Keyboard::Key::NUMBER_7;
            case GLFW_KEY_8:                        return Keyboard::Key::NUMBER_8;
            case GLFW_KEY_9:                        return Keyboard::Key::NUMBER_9;
            case GLFW_KEY_SEMICOLON:                return Keyboard::Key::SEMICOLON;        /*; */
            case GLFW_KEY_EQUAL:                    return Keyboard::Key::EQUAL;            /* = */
            case GLFW_KEY_A:                        return Keyboard::Key::A;
            case GLFW_KEY_B:                        return Keyboard::Key::B;
            case GLFW_KEY_C:                        return Keyboard::Key::C;
            case GLFW_KEY_D:                        return Keyboard::Key::D;
            case GLFW_KEY_E:                        return Keyboard::Key::E;
            case GLFW_KEY_F:                        return Keyboard::Key::F;
            case GLFW_KEY_G:                        return Keyboard::Key::G;
            case GLFW_KEY_H:                        return Keyboard::Key::H;
            case GLFW_KEY_I:                        return Keyboard::Key::I;
            case GLFW_KEY_J:                        return Keyboard::Key::J;
            case GLFW_KEY_K:                        return Keyboard::Key::K;
            case GLFW_KEY_L:                        return Keyboard::Key::L;
            case GLFW_KEY_M:                        return Keyboard::Key::M;
            case GLFW_KEY_N:                        return Keyboard::Key::N;
            case GLFW_KEY_O:                        return Keyboard::Key::O;
            case GLFW_KEY_P:                        return Keyboard::Key::P;
            case GLFW_KEY_Q:                        return Keyboard::Key::Q;
            case GLFW_KEY_R:                        return Keyboard::Key::R;
            case GLFW_KEY_S:                        return Keyboard::Key::S;
            case GLFW_KEY_T:                        return Keyboard::Key::T;
            case GLFW_KEY_U:                        return Keyboard::Key::U;
            case GLFW_KEY_V:                        return Keyboard::Key::V;
            case GLFW_KEY_W:                        return Keyboard::Key::W;
            case GLFW_KEY_X:                        return Keyboard::Key::X;
            case GLFW_KEY_Y:                        return Keyboard::Key::Y;
            case GLFW_KEY_Z:                        return Keyboard::Key::Z;
            case GLFW_KEY_LEFT_BRACKET:             return Keyboard::Key::LEFT_BRACKET;     /* [ */
            case GLFW_KEY_BACKSLASH:                return Keyboard::Key::BACKSLASH;        /* \ */
            case GLFW_KEY_RIGHT_BRACKET:            return Keyboard::Key::RIGHT_BRACKET;    /* ] */
            case GLFW_KEY_GRAVE_ACCENT:             return Keyboard::Key::GRAVE_ACCENT;     /* ` */
            case GLFW_KEY_WORLD_1:                  return Keyboard::Key::WORLD_1;          /* non-US #1 */
            case GLFW_KEY_WORLD_2:                  return Keyboard::Key::WORLD_2;          /* non-US #2 */
            default:                                return Keyboard::Key::UNKNOWN;
        }
    }
#endif