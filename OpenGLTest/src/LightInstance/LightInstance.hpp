#pragma once
#include "ShaderProgram/ShaderProgram.hpp"

#include <glm/vec3.hpp>

#include <string>

class LightInstance {
private:
    static constexpr const char* POSITION_ARGUMENT_FORMAT_STR              = "u_{}_light_position";
    static constexpr const char* AMBIENT_COLOR_ARGUMENT_FORMAT_STR         = "u_{}_light_ambient_color";
    static constexpr const char* DIFFUSE_COLOR_ARGUMENT_FORMAT_STR         = "u_{}_light_diffuse_color";
    static constexpr const char* SPECULAR_COLOR_ARGUMENT_FORMAT_STR        = "u_{}_light_specular_color";
    static constexpr const char* AMBIENT_INTENSITY_ARGUMENT_FORMAT_STR     = "u_{}_light_ambient_intensity";
    static constexpr const char* DIFFUSE_INTENSITY_ARGUMENT_FORMAT_STR     = "u_{}_light_diffuse_intensity";
    static constexpr const char* SPECULAR_INTENSITY_ARGUMENT_FORMAT_STR    = "u_{}_light_specular_intensity";
    static constexpr const char* DIRECTION_ARGUMENT_FORMAT_STR             = "u_{}_light_direction";
    static constexpr const char* INNER_CUTOFF_ARGUMENT_FORMAT_STR          = "u_{}_light_inner_cutoff";
    static constexpr const char* OUTER_CUTOFF_ARGUMENT_FORMAT_STR          = "u_{}_light_outer_cutoff";
    static constexpr const char* EXPONENT_ARGUMENT_FORMAT_STR              = "u_{}_light_exponent";
    static constexpr const char* CONSTANT_ATTENUATION_ARGUMENT_FORMAT_STR  = "u_{}_light_constant_attenuation";
    static constexpr const char* LINEAR_ATTENUATION_ARGUMENT_FORMAT_STR    = "u_{}_light_linear_attenuation";
    static constexpr const char* QUADRATIC_ATTENUATION_ARGUMENT_FORMAT_STR = "u_{}_light_quadratic_attenuation";
    static constexpr const char* TYPE_ARGUMENT_FORMAT_STR                  = "u_{}_light_type";
    static constexpr const char* IS_ENABLE_ARGUMENT_FORMAT_STR            = "u_{}_is_enabled";
    static constexpr const char* IS_AMBIENT_ARGUMENT_FORMAT_STR            = "u_{}_is_ambient";
    static constexpr const char* IS_DIFFUSE_ARGUMENT_FORMAT_STR            = "u_{}_is_diffuse";
    static constexpr const char* IS_SPECULAR_ARGUMENT_FORMAT_STR           = "u_{}_is_specular";

public:
    enum class LightType {
        NONE,
        DIRECTIONAL,
        POINT,
        SPOT
    };

    LightInstance() = delete;

    explicit LightInstance(
        const std::string& name, const glm::vec3& direction, const glm::vec3& ambient,
        const glm::vec3& diffuse, const glm::vec3& specular
    );

    explicit LightInstance(
        const std::string& name, const glm::vec3& position, const glm::vec3& ambient,
        const glm::vec3& diffuse, const glm::vec3& specular, float constantAttenuation,
        float linearAttenuation, float quadraticAttenuation
    );

    explicit LightInstance(
        const std::string& name, const glm::vec3& position, const glm::vec3& direction,
        const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
        float constantAttenuation, float linearAttenuation, float quadraticAttenuation,
        float cutoff, float exponent
    );

    LightInstance(const LightInstance&) = default;

    LightInstance(LightInstance&&) noexcept = default;

    LightInstance& operator=(const LightInstance&) = default;

    LightInstance& operator=(LightInstance&&) noexcept = default;

    ~LightInstance() = default;

    const std::string& GetName() const;

    void SetName(const std::string& name);

    const glm::vec3& GetPosition() const;

    void SetPosition(const glm::vec3& position);

    const glm::vec3& GetAmbient() const;

    void SetAmbient(const glm::vec3& ambient);

    const glm::vec3& GetDiffuse() const;

    void SetDiffuse(const glm::vec3& diffuse);

    const glm::vec3& GetSpecular() const;

    void SetSpecular(const glm::vec3& specular);

    const glm::vec3& GetDirection() const;

    void SetDirection(const glm::vec3& direction);

    float GetInnerCutoff() const;

    void SetInnerCutoff(float cutoff);

    float GetOuterCutoff() const;

    void SetOuterCutoff(float cutoff);

    float GetExponent() const;

    void SetExponent(float exponent);

    float GetConstantAttenuation() const;

    void SetConstantAttenuation(float constantAttenuation);

    float GetLinearAttenuation() const;

    void SetLinearAttenuation(float linearAttenuation);

    float GetQuadraticAttenuation() const;

    void SetQuadraticAttenuation(float quadraticAttenuation);

    float GetAmbientIntensity() const;

    void SetAmbientIntensity(float ambientIntensity);

    float GetDiffuseIntensity() const;

    void SetDiffuseIntensity(float diffuseIntensity);

    float GetSpecularIntensity() const;

    void SetSpecularIntensity(float specularIntensity);

    bool IsEnable() const;

    void SetEnable(bool isEnable);

    bool IsAmbient() const;

    void SetAmbient(bool isAmbient);

    bool IsDiffuse() const;

    void SetDiffuse(bool isDiffuse);

    bool IsSpecular() const;

    void SetSpecular(bool isSpecular);

    LightInstance::LightType GetLightType() const;

    void SetLightType(LightInstance::LightType lightType);

    void UpdateLight(ShaderProgram& shaderProgram);

protected:
    std::string name_{};
    glm::vec3 position_{};
    glm::vec3 ambientColor_  = glm::vec3(1.0);
    glm::vec3 diffuseColor_  = glm::vec3(1.0);
    glm::vec3 specularColor_ = glm::vec3(1.0);
    glm::vec3 direction_     = glm::vec3(1.0);
    float innerCutoff_{};
    float outerCutoff_{};
    float exponent_{};
    float constantAttenuation_ = 1.0f;
    float linearAttenuation_{};
    float quadraticAttenuation_{};
    float ambientIntensity_  = 1.0f;
    float diffuseIntensity_  = 1.0f;
    float specularIntensity_ = 1.0f;
    LightInstance::LightType lightType_{};
    bool isEnable_{};
    bool isAmbient_  = true;
    bool isDiffuse_  = true;
    bool isSpecular_ = true;

    void InitName_(const std::string& name);

    void InitBasicLight_(const std::string& name, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);
};
