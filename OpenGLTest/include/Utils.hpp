#pragma once
#include "glad/glad.h"

#include <glm/glm.hpp>
#include <glm/gtx/normal.hpp>

#include <cmath>

enum class ValueType : int {
    NIL = 0,
    FLOAT = GL_FLOAT,
    DOUBLE = GL_DOUBLE,
    INT = GL_INT,
    UINT = GL_UNSIGNED_INT,
    CHAR = GL_BYTE,
    UCHAR = GL_UNSIGNED_BYTE,
    SHORT = GL_SHORT,
    USHORT = GL_UNSIGNED_SHORT
};

inline int GetSizeOfType(ValueType type) {
    switch (type) {
    case ValueType::FLOAT:
        return sizeof(float);
    case ValueType::DOUBLE:
        return sizeof(double);
    case ValueType::INT:
        return sizeof(int);
    case ValueType::UINT:
        return sizeof(unsigned);
    case ValueType::CHAR:
        return sizeof(char);
    case ValueType::UCHAR:
        return sizeof(unsigned char);
    case ValueType::SHORT:
        return sizeof(short);
    case ValueType::USHORT:
        return sizeof(unsigned short);
    default:
        return 0;
    }
}

template<class T>
ValueType GetType() {
    return ValueType::NIL;
}

template<>
inline ValueType GetType<int>() {
    return ValueType::INT;
}

template<>
inline ValueType GetType<unsigned>() {
    return ValueType::UINT;
}

template<>
inline ValueType GetType<char>() {
    return ValueType::CHAR;
}

template<>
inline ValueType GetType<unsigned char>() {
    return ValueType::UCHAR;
}

template<>
inline ValueType GetType<float>() {
    return ValueType::FLOAT;
}

template<>
inline ValueType GetType<double>() {
    return ValueType::DOUBLE;
}

template<>
inline ValueType GetType<short>() {
    return ValueType::SHORT;
}

template<>
inline ValueType GetType<unsigned short>() {
    return ValueType::USHORT;
}

enum class Normalize : bool {
    NOT_NORMALIZE,
    NORMALIZE
};

inline bool isFloatEqual(float x, float y, float epsilon = std::numeric_limits<float>::epsilon()) {
    return std::abs(x - y) <= epsilon;
}

inline bool isFloatNotEqual(float x, float y, float epsilon = std::numeric_limits<float>::epsilon()) {
    return !isFloatEqual(x, y, epsilon);
}

inline bool isFloatGreater(float x, float y, float epsilon = std::numeric_limits<float>::epsilon()) {
    return x - y > epsilon;
}

inline bool isFloatLessEqual(float x, float y, float epsilon = std::numeric_limits<float>::epsilon()) {
    return !isFloatGreater(x, y, epsilon);
}

inline bool isFloatLess(float x, float y, float epsilon = std::numeric_limits<float>::epsilon()) {
    return isFloatGreater(y, x, epsilon);
}

inline bool isFloatGreaterEqual(float x, float y, float epsilon = std::numeric_limits<float>::epsilon()) {
    return !isFloatLess(x, y, epsilon);
}

inline glm::vec3 CalculateNormal(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c) {
    return glm::normalize(glm::triangleNormal(a, b, c));
}
