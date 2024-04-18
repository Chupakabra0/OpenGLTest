#pragma once
#include <glm/vec3.hpp>

struct MaterialInstance {
public:
    glm::vec3 ambient{};
    glm::vec3 diffuse{};
    glm::vec3 specular{};
    float shininess{};
};
