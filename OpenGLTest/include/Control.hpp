#pragma once

enum class ControlAction : short {
    RELEASE = 0,
    PRESS   = 1,
    REPEAT  = 2
};

inline int ConvertControlActionToCode(ControlAction action);
inline ControlAction ConvertCodeToControlAction(int buttonCode);

#if defined(CONTROL_GLFW)
    int ConvertControlActionToCode(ControlAction action) {
        return static_cast<int>(action);
    }

    ControlAction ConvertCodeToControlAction(int buttonCode) {
        return static_cast<ControlAction>(buttonCode);
    }
#endif


enum class ControlMods : short {
    NONE      = 0,
    SHIFT     = 1,
    CTRL      = 2,
    ALT       = 4,
    SUPER     = 8,
    CAPS_LOCK = 16,
    NUM_LOCK  = 32
};

inline int ConvertControlModsToCode(ControlMods mods);
inline ControlMods ConvertCodeToControlMods(int modsCode);

#if defined(CONTROL_GLFW)
    int ConvertControlModsToCode(ControlMods mods) {
        return static_cast<int>(mods);
    }

    ControlMods ConvertCodeToControlMods(int modsCode) {
        return static_cast<ControlMods>(modsCode);
    }
#endif
