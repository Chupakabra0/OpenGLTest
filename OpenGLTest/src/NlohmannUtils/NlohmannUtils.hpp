#pragma once
#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

namespace nlohmann {
    template<class T>
    concept VecType = std::is_same_v<T, glm::vec2> || std::is_same_v<T, glm::vec3> || std::is_same_v<T, glm::vec4>;

    template<class Vec> requires VecType<Vec>
    struct adl_serializer<Vec> {
        static void to_json(json& json, Vec vec) {
            if constexpr (typeid(Vec) == typeid(glm::vec2)) {
                json = nlohmann::json{
                    { "X", vec.x },
                    { "Y", vec.y }
                };
            }
            else if constexpr (typeid(Vec) == typeid(glm::vec3)) {
                json = nlohmann::json{
                    { "X", vec.x },
                    { "Y", vec.y },
                    { "Z", vec.z },
                };
            }
            else if constexpr (typeid(Vec) == typeid(glm::vec4)) {
                json = nlohmann::json{
                    { "X", vec.x },
                    { "Y", vec.y },
                    { "Z", vec.z },
                    { "W", vec.w },
                };
            }
        }

        static void from_json(const json& json, Vec& vec) {
            if constexpr (typeid(Vec) == typeid(glm::vec2)) {
                json.at("X").get_to(vec.x);
                json.at("Y").get_to(vec.y);
            }
            else if constexpr (typeid(Vec) == typeid(glm::vec3)) {
                json.at("X").get_to(vec.x);
                json.at("Y").get_to(vec.y);
                json.at("Z").get_to(vec.z);
            }
            else if constexpr (typeid(Vec) == typeid(glm::vec4)) {
                json.at("X").get_to(vec.x);
                json.at("Y").get_to(vec.y);
                json.at("Z").get_to(vec.z);
                json.at("W").get_to(vec.w);
            }
        }
    };
}
