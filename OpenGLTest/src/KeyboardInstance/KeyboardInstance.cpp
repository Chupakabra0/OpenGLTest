#include "KeyboardInstance/KeyboardInstance.hpp"

#include <GLFW/glfw3.h>

void KeyboardInstance::SetPressed(KeyboardInstance::Key key) {
    this->isKeyPressed_[key] = true;
}

void KeyboardInstance::SetUnpressed(KeyboardInstance::Key key) {
    this->isKeyPressed_[key] = false;
}

bool KeyboardInstance::IsPressed(KeyboardInstance::Key key) const {
    const auto find = this->isKeyPressed_.find(key);

    return find != this->isKeyPressed_.end() ?
        find->second :
        false;
}

ControlMods KeyboardInstance::GetMods() const {
    return this->mods_;
}

void KeyboardInstance::SetMods(ControlMods mods) {
    this->mods_ = mods;
}

int ConvertKeyboardKeyToCode(KeyboardInstance::Key key) {
    switch (key) {
        case KeyboardInstance::Key::ESC:                return GLFW_KEY_ESCAPE;
        case KeyboardInstance::Key::ENTER:              return GLFW_KEY_ENTER;
        case KeyboardInstance::Key::TAB:                return GLFW_KEY_TAB;
        case KeyboardInstance::Key::BACKSPACE:          return GLFW_KEY_BACKSPACE;
        case KeyboardInstance::Key::INSERT:             return GLFW_KEY_INSERT;
        case KeyboardInstance::Key::DEL:                return GLFW_KEY_DELETE;
        case KeyboardInstance::Key::ARROW_RIGHT:        return GLFW_KEY_RIGHT;
        case KeyboardInstance::Key::ARROW_LEFT:         return GLFW_KEY_LEFT;
        case KeyboardInstance::Key::ARROW_DOWN:         return GLFW_KEY_DOWN;
        case KeyboardInstance::Key::ARROW_UP:           return GLFW_KEY_UP;
        case KeyboardInstance::Key::PAGE_UP:            return GLFW_KEY_PAGE_UP;
        case KeyboardInstance::Key::PAGE_DOWN:          return GLFW_KEY_PAGE_DOWN;
        case KeyboardInstance::Key::HOME:               return GLFW_KEY_HOME;
        case KeyboardInstance::Key::END:                return GLFW_KEY_END;
        case KeyboardInstance::Key::CAPS_LOCK:          return GLFW_KEY_CAPS_LOCK;
        case KeyboardInstance::Key::SCROLL_LOCK:        return GLFW_KEY_SCROLL_LOCK;
        case KeyboardInstance::Key::NUM_LOCK:           return GLFW_KEY_NUM_LOCK;
        case KeyboardInstance::Key::PRINT_SCREEN:       return GLFW_KEY_PRINT_SCREEN;
        case KeyboardInstance::Key::PAUSE:              return GLFW_KEY_PAUSE;
        case KeyboardInstance::Key::F1:                 return GLFW_KEY_F1;
        case KeyboardInstance::Key::F2:                 return GLFW_KEY_F2;
        case KeyboardInstance::Key::F3:                 return GLFW_KEY_F3;
        case KeyboardInstance::Key::F4:                 return GLFW_KEY_F4;
        case KeyboardInstance::Key::F5:                 return GLFW_KEY_F5;
        case KeyboardInstance::Key::F6:                 return GLFW_KEY_F6;
        case KeyboardInstance::Key::F7:                 return GLFW_KEY_F7;
        case KeyboardInstance::Key::F8:                 return GLFW_KEY_F8;
        case KeyboardInstance::Key::F9:                 return GLFW_KEY_F9;
        case KeyboardInstance::Key::F10:                return GLFW_KEY_F10;
        case KeyboardInstance::Key::F11:                return GLFW_KEY_F11;
        case KeyboardInstance::Key::F12:                return GLFW_KEY_F12;
        case KeyboardInstance::Key::F13:                return GLFW_KEY_F13;
        case KeyboardInstance::Key::F14:                return GLFW_KEY_F14;
        case KeyboardInstance::Key::F15:                return GLFW_KEY_F15;
        case KeyboardInstance::Key::F16:                return GLFW_KEY_F16;
        case KeyboardInstance::Key::F17:                return GLFW_KEY_F17;
        case KeyboardInstance::Key::F18:                return GLFW_KEY_F18;
        case KeyboardInstance::Key::F19:                return GLFW_KEY_F19;
        case KeyboardInstance::Key::F20:                return GLFW_KEY_F20;
        case KeyboardInstance::Key::F21:                return GLFW_KEY_F21;
        case KeyboardInstance::Key::F22:                return GLFW_KEY_F22;
        case KeyboardInstance::Key::F23:                return GLFW_KEY_F23;
        case KeyboardInstance::Key::F24:                return GLFW_KEY_F24;
        case KeyboardInstance::Key::F25:                return GLFW_KEY_F25;
        case KeyboardInstance::Key::NUMPAD_0:           return GLFW_KEY_KP_0;
        case KeyboardInstance::Key::NUMPAD_1:           return GLFW_KEY_KP_1;
        case KeyboardInstance::Key::NUMPAD_2:           return GLFW_KEY_KP_2;
        case KeyboardInstance::Key::NUMPAD_3:           return GLFW_KEY_KP_3;
        case KeyboardInstance::Key::NUMPAD_4:           return GLFW_KEY_KP_4;
        case KeyboardInstance::Key::NUMPAD_5:           return GLFW_KEY_KP_5;
        case KeyboardInstance::Key::NUMPAD_6:           return GLFW_KEY_KP_6;
        case KeyboardInstance::Key::NUMPAD_7:           return GLFW_KEY_KP_7;
        case KeyboardInstance::Key::NUMPAD_8:           return GLFW_KEY_KP_8;
        case KeyboardInstance::Key::NUMPAD_9:           return GLFW_KEY_KP_9;
        case KeyboardInstance::Key::NUMPAD_DECIMAL:     return GLFW_KEY_KP_DECIMAL;
        case KeyboardInstance::Key::NUMPAD_DIVIDE:      return GLFW_KEY_KP_DIVIDE;
        case KeyboardInstance::Key::NUMPAD_MULTIPLY:    return GLFW_KEY_KP_MULTIPLY;
        case KeyboardInstance::Key::NUMPAD_SUBTRACT:    return GLFW_KEY_KP_SUBTRACT;
        case KeyboardInstance::Key::NUMPAD_ADD:         return GLFW_KEY_KP_ADD;
        case KeyboardInstance::Key::NUMPAD_ENTER:       return GLFW_KEY_KP_ENTER;
        case KeyboardInstance::Key::NUMPAD_EQUAL:       return GLFW_KEY_KP_EQUAL;
        case KeyboardInstance::Key::LEFT_SHIFT:         return GLFW_KEY_LEFT_SHIFT;
        case KeyboardInstance::Key::LEFT_CTRL:          return GLFW_KEY_LEFT_CONTROL;
        case KeyboardInstance::Key::LEFT_ALT:           return GLFW_KEY_LEFT_ALT;
        case KeyboardInstance::Key::LEFT_SUPER:         return GLFW_KEY_LEFT_SUPER;
        case KeyboardInstance::Key::RIGHT_SHIFT:        return GLFW_KEY_RIGHT_SHIFT;
        case KeyboardInstance::Key::RIGHT_CTRL:         return GLFW_KEY_RIGHT_CONTROL;
        case KeyboardInstance::Key::RIGHT_ALT:          return GLFW_KEY_RIGHT_ALT;
        case KeyboardInstance::Key::RIGHT_SUPER:        return GLFW_KEY_RIGHT_SUPER;
        case KeyboardInstance::Key::MENU:               return GLFW_KEY_MENU;
        case KeyboardInstance::Key::SPACE:              return GLFW_KEY_SPACE;
        case KeyboardInstance::Key::APOSTROPHE:         return GLFW_KEY_APOSTROPHE;     /* ' */
        case KeyboardInstance::Key::COMMA:              return GLFW_KEY_COMMA;          /* , */
        case KeyboardInstance::Key::MINUS:              return GLFW_KEY_MINUS;          /* - */
        case KeyboardInstance::Key::PERIOD:             return GLFW_KEY_PERIOD;         /* . */
        case KeyboardInstance::Key::SLASH:              return GLFW_KEY_SLASH;          /* / */
        case KeyboardInstance::Key::NUMBER_0:           return GLFW_KEY_0;
        case KeyboardInstance::Key::NUMBER_1:           return GLFW_KEY_1;
        case KeyboardInstance::Key::NUMBER_2:           return GLFW_KEY_2;
        case KeyboardInstance::Key::NUMBER_3:           return GLFW_KEY_3;
        case KeyboardInstance::Key::NUMBER_4:           return GLFW_KEY_4;
        case KeyboardInstance::Key::NUMBER_5:           return GLFW_KEY_5;
        case KeyboardInstance::Key::NUMBER_6:           return GLFW_KEY_6;
        case KeyboardInstance::Key::NUMBER_7:           return GLFW_KEY_7;
        case KeyboardInstance::Key::NUMBER_8:           return GLFW_KEY_8;
        case KeyboardInstance::Key::NUMBER_9:           return GLFW_KEY_9;
        case KeyboardInstance::Key::SEMICOLON:          return GLFW_KEY_SEMICOLON;      /*; */
        case KeyboardInstance::Key::EQUAL:              return GLFW_KEY_EQUAL;          /* = */
        case KeyboardInstance::Key::A:                  return GLFW_KEY_A;
        case KeyboardInstance::Key::B:                  return GLFW_KEY_B;
        case KeyboardInstance::Key::C:                  return GLFW_KEY_C;
        case KeyboardInstance::Key::D:                  return GLFW_KEY_D;
        case KeyboardInstance::Key::E:                  return GLFW_KEY_E;
        case KeyboardInstance::Key::F:                  return GLFW_KEY_F;
        case KeyboardInstance::Key::G:                  return GLFW_KEY_G;
        case KeyboardInstance::Key::H:                  return GLFW_KEY_H;
        case KeyboardInstance::Key::I:                  return GLFW_KEY_I;
        case KeyboardInstance::Key::J:                  return GLFW_KEY_J;
        case KeyboardInstance::Key::K:                  return GLFW_KEY_K;
        case KeyboardInstance::Key::L:                  return GLFW_KEY_L;
        case KeyboardInstance::Key::M:                  return GLFW_KEY_M;
        case KeyboardInstance::Key::N:                  return GLFW_KEY_N;
        case KeyboardInstance::Key::O:                  return GLFW_KEY_O;
        case KeyboardInstance::Key::P:                  return GLFW_KEY_P;
        case KeyboardInstance::Key::Q:                  return GLFW_KEY_Q;
        case KeyboardInstance::Key::R:                  return GLFW_KEY_R;
        case KeyboardInstance::Key::S:                  return GLFW_KEY_S;
        case KeyboardInstance::Key::T:                  return GLFW_KEY_T;
        case KeyboardInstance::Key::U:                  return GLFW_KEY_U;
        case KeyboardInstance::Key::V:                  return GLFW_KEY_V;
        case KeyboardInstance::Key::W:                  return GLFW_KEY_W;
        case KeyboardInstance::Key::X:                  return GLFW_KEY_X;
        case KeyboardInstance::Key::Y:                  return GLFW_KEY_Y;
        case KeyboardInstance::Key::Z:                  return GLFW_KEY_Z;
        case KeyboardInstance::Key::LEFT_BRACKET:       return GLFW_KEY_LEFT_BRACKET;   /* [ */
        case KeyboardInstance::Key::BACKSLASH:          return GLFW_KEY_BACKSLASH;      /* \ */
        case KeyboardInstance::Key::RIGHT_BRACKET:      return GLFW_KEY_RIGHT_BRACKET;  /* ] */
        case KeyboardInstance::Key::GRAVE_ACCENT:       return GLFW_KEY_GRAVE_ACCENT;   /* ` */
        case KeyboardInstance::Key::WORLD_1:            return GLFW_KEY_WORLD_1;        /* non-US #1 */
        case KeyboardInstance::Key::WORLD_2:            return GLFW_KEY_WORLD_2;        /* non-US #2 */
        default:                                        return GLFW_KEY_UNKNOWN;
    }
}

KeyboardInstance::Key ConvertCodeToKeyboardKey(int keyCode) {
    switch (keyCode) {
        case GLFW_KEY_ESCAPE:                   return KeyboardInstance::Key::ESC;
        case GLFW_KEY_ENTER:                    return KeyboardInstance::Key::ENTER;
        case GLFW_KEY_TAB:                      return KeyboardInstance::Key::TAB;
        case GLFW_KEY_BACKSPACE:                return KeyboardInstance::Key::BACKSPACE;
        case GLFW_KEY_INSERT:                   return KeyboardInstance::Key::INSERT;
        case GLFW_KEY_DELETE:                   return KeyboardInstance::Key::DEL;
        case GLFW_KEY_RIGHT:                    return KeyboardInstance::Key::ARROW_RIGHT;
        case GLFW_KEY_LEFT:                     return KeyboardInstance::Key::ARROW_LEFT;
        case GLFW_KEY_DOWN:                     return KeyboardInstance::Key::ARROW_DOWN;
        case GLFW_KEY_UP:                       return KeyboardInstance::Key::ARROW_UP;
        case GLFW_KEY_PAGE_UP:                  return KeyboardInstance::Key::PAGE_UP;
        case GLFW_KEY_PAGE_DOWN:                return KeyboardInstance::Key::PAGE_DOWN;
        case GLFW_KEY_HOME:                     return KeyboardInstance::Key::HOME;
        case GLFW_KEY_END:                      return KeyboardInstance::Key::END;
        case GLFW_KEY_CAPS_LOCK:                return KeyboardInstance::Key::CAPS_LOCK;
        case GLFW_KEY_SCROLL_LOCK:              return KeyboardInstance::Key::SCROLL_LOCK;
        case GLFW_KEY_NUM_LOCK:                 return KeyboardInstance::Key::NUM_LOCK;
        case GLFW_KEY_PRINT_SCREEN:             return KeyboardInstance::Key::PRINT_SCREEN;
        case GLFW_KEY_PAUSE:                    return KeyboardInstance::Key::PAUSE;
        case GLFW_KEY_F1:                       return KeyboardInstance::Key::F1;
        case GLFW_KEY_F2:                       return KeyboardInstance::Key::F2;
        case GLFW_KEY_F3:                       return KeyboardInstance::Key::F3;
        case GLFW_KEY_F4:                       return KeyboardInstance::Key::F4;
        case GLFW_KEY_F5:                       return KeyboardInstance::Key::F5;
        case GLFW_KEY_F6:                       return KeyboardInstance::Key::F6;
        case GLFW_KEY_F7:                       return KeyboardInstance::Key::F7;
        case GLFW_KEY_F8:                       return KeyboardInstance::Key::F8;
        case GLFW_KEY_F9:                       return KeyboardInstance::Key::F9;
        case GLFW_KEY_F10:                      return KeyboardInstance::Key::F10;
        case GLFW_KEY_F11:                      return KeyboardInstance::Key::F11;
        case GLFW_KEY_F12:                      return KeyboardInstance::Key::F12;
        case GLFW_KEY_F13:                      return KeyboardInstance::Key::F13;
        case GLFW_KEY_F14:                      return KeyboardInstance::Key::F14;
        case GLFW_KEY_F15:                      return KeyboardInstance::Key::F15;
        case GLFW_KEY_F16:                      return KeyboardInstance::Key::F16;
        case GLFW_KEY_F17:                      return KeyboardInstance::Key::F17;
        case GLFW_KEY_F18:                      return KeyboardInstance::Key::F18;
        case GLFW_KEY_F19:                      return KeyboardInstance::Key::F19;
        case GLFW_KEY_F20:                      return KeyboardInstance::Key::F20;
        case GLFW_KEY_F21:                      return KeyboardInstance::Key::F21;
        case GLFW_KEY_F22:                      return KeyboardInstance::Key::F22;
        case GLFW_KEY_F23:                      return KeyboardInstance::Key::F23;
        case GLFW_KEY_F24:                      return KeyboardInstance::Key::F24;
        case GLFW_KEY_F25:                      return KeyboardInstance::Key::F25;
        case GLFW_KEY_KP_0:                     return KeyboardInstance::Key::NUMPAD_0;
        case GLFW_KEY_KP_1:                     return KeyboardInstance::Key::NUMPAD_1;
        case GLFW_KEY_KP_2:                     return KeyboardInstance::Key::NUMPAD_2;
        case GLFW_KEY_KP_3:                     return KeyboardInstance::Key::NUMPAD_3;
        case GLFW_KEY_KP_4:                     return KeyboardInstance::Key::NUMPAD_4;
        case GLFW_KEY_KP_5:                     return KeyboardInstance::Key::NUMPAD_5;
        case GLFW_KEY_KP_6:                     return KeyboardInstance::Key::NUMPAD_6;
        case GLFW_KEY_KP_7:                     return KeyboardInstance::Key::NUMPAD_7;
        case GLFW_KEY_KP_8:                     return KeyboardInstance::Key::NUMPAD_8;
        case GLFW_KEY_KP_9:                     return KeyboardInstance::Key::NUMPAD_9;
        case GLFW_KEY_KP_DECIMAL:               return KeyboardInstance::Key::NUMPAD_DECIMAL;
        case GLFW_KEY_KP_DIVIDE:                return KeyboardInstance::Key::NUMPAD_DIVIDE;
        case GLFW_KEY_KP_MULTIPLY:              return KeyboardInstance::Key::NUMPAD_MULTIPLY;
        case GLFW_KEY_KP_SUBTRACT:              return KeyboardInstance::Key::NUMPAD_SUBTRACT;
        case GLFW_KEY_KP_ADD:                   return KeyboardInstance::Key::NUMPAD_ADD;
        case GLFW_KEY_KP_ENTER:                 return KeyboardInstance::Key::NUMPAD_ENTER;
        case GLFW_KEY_KP_EQUAL:                 return KeyboardInstance::Key::NUMPAD_EQUAL;
        case GLFW_KEY_LEFT_SHIFT:               return KeyboardInstance::Key::LEFT_SHIFT;
        case GLFW_KEY_LEFT_CONTROL:             return KeyboardInstance::Key::LEFT_CTRL;
        case GLFW_KEY_LEFT_ALT:                 return KeyboardInstance::Key::LEFT_ALT;
        case GLFW_KEY_LEFT_SUPER:               return KeyboardInstance::Key::LEFT_SUPER;
        case GLFW_KEY_RIGHT_SHIFT:              return KeyboardInstance::Key::RIGHT_SHIFT;
        case GLFW_KEY_RIGHT_CONTROL:            return KeyboardInstance::Key::RIGHT_CTRL;
        case GLFW_KEY_RIGHT_ALT:                return KeyboardInstance::Key::RIGHT_ALT;
        case GLFW_KEY_RIGHT_SUPER:              return KeyboardInstance::Key::RIGHT_SUPER;
        case GLFW_KEY_MENU:                     return KeyboardInstance::Key::MENU;
        case GLFW_KEY_SPACE:                    return KeyboardInstance::Key::SPACE;
        case GLFW_KEY_APOSTROPHE:               return KeyboardInstance::Key::APOSTROPHE;       /* ' */
        case GLFW_KEY_COMMA:                    return KeyboardInstance::Key::COMMA;            /* , */
        case GLFW_KEY_MINUS:                    return KeyboardInstance::Key::MINUS;            /* - */
        case GLFW_KEY_PERIOD:                   return KeyboardInstance::Key::PERIOD;           /* . */
        case GLFW_KEY_SLASH:                    return KeyboardInstance::Key::SLASH;            /* / */
        case GLFW_KEY_0:                        return KeyboardInstance::Key::NUMBER_0;
        case GLFW_KEY_1:                        return KeyboardInstance::Key::NUMBER_1;
        case GLFW_KEY_2:                        return KeyboardInstance::Key::NUMBER_2;
        case GLFW_KEY_3:                        return KeyboardInstance::Key::NUMBER_3;
        case GLFW_KEY_4:                        return KeyboardInstance::Key::NUMBER_4;
        case GLFW_KEY_5:                        return KeyboardInstance::Key::NUMBER_5;
        case GLFW_KEY_6:                        return KeyboardInstance::Key::NUMBER_6;
        case GLFW_KEY_7:                        return KeyboardInstance::Key::NUMBER_7;
        case GLFW_KEY_8:                        return KeyboardInstance::Key::NUMBER_8;
        case GLFW_KEY_9:                        return KeyboardInstance::Key::NUMBER_9;
        case GLFW_KEY_SEMICOLON:                return KeyboardInstance::Key::SEMICOLON;        /*; */
        case GLFW_KEY_EQUAL:                    return KeyboardInstance::Key::EQUAL;            /* = */
        case GLFW_KEY_A:                        return KeyboardInstance::Key::A;
        case GLFW_KEY_B:                        return KeyboardInstance::Key::B;
        case GLFW_KEY_C:                        return KeyboardInstance::Key::C;
        case GLFW_KEY_D:                        return KeyboardInstance::Key::D;
        case GLFW_KEY_E:                        return KeyboardInstance::Key::E;
        case GLFW_KEY_F:                        return KeyboardInstance::Key::F;
        case GLFW_KEY_G:                        return KeyboardInstance::Key::G;
        case GLFW_KEY_H:                        return KeyboardInstance::Key::H;
        case GLFW_KEY_I:                        return KeyboardInstance::Key::I;
        case GLFW_KEY_J:                        return KeyboardInstance::Key::J;
        case GLFW_KEY_K:                        return KeyboardInstance::Key::K;
        case GLFW_KEY_L:                        return KeyboardInstance::Key::L;
        case GLFW_KEY_M:                        return KeyboardInstance::Key::M;
        case GLFW_KEY_N:                        return KeyboardInstance::Key::N;
        case GLFW_KEY_O:                        return KeyboardInstance::Key::O;
        case GLFW_KEY_P:                        return KeyboardInstance::Key::P;
        case GLFW_KEY_Q:                        return KeyboardInstance::Key::Q;
        case GLFW_KEY_R:                        return KeyboardInstance::Key::R;
        case GLFW_KEY_S:                        return KeyboardInstance::Key::S;
        case GLFW_KEY_T:                        return KeyboardInstance::Key::T;
        case GLFW_KEY_U:                        return KeyboardInstance::Key::U;
        case GLFW_KEY_V:                        return KeyboardInstance::Key::V;
        case GLFW_KEY_W:                        return KeyboardInstance::Key::W;
        case GLFW_KEY_X:                        return KeyboardInstance::Key::X;
        case GLFW_KEY_Y:                        return KeyboardInstance::Key::Y;
        case GLFW_KEY_Z:                        return KeyboardInstance::Key::Z;
        case GLFW_KEY_LEFT_BRACKET:             return KeyboardInstance::Key::LEFT_BRACKET;     /* [ */
        case GLFW_KEY_BACKSLASH:                return KeyboardInstance::Key::BACKSLASH;        /* \ */
        case GLFW_KEY_RIGHT_BRACKET:            return KeyboardInstance::Key::RIGHT_BRACKET;    /* ] */
        case GLFW_KEY_GRAVE_ACCENT:             return KeyboardInstance::Key::GRAVE_ACCENT;     /* ` */
        case GLFW_KEY_WORLD_1:                  return KeyboardInstance::Key::WORLD_1;          /* non-US #1 */
        case GLFW_KEY_WORLD_2:                  return KeyboardInstance::Key::WORLD_2;          /* non-US #2 */
        default:                                return KeyboardInstance::Key::UNKNOWN;
    }
}
