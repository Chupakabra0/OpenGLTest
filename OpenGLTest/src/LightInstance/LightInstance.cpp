#include "LightInstance/LightInstance.hpp"

#include <glm/ext/scalar_constants.hpp>

LightInstance::LightInstance(
    const std::string& name, const glm::vec3& direction, const glm::vec3& ambient,
    const glm::vec3& diffuse, const glm::vec3& specular)
    : direction_(direction), lightType_(LightInstance::LightType::DIRECTIONAL) {
    this->InitBasicLight_(name, ambient, diffuse, specular);
}

LightInstance::LightInstance(
    const std::string& name, const glm::vec3& position, const glm::vec3& ambient,
    const glm::vec3& diffuse, const glm::vec3& specular, float constantAttenuation,
    float linearAttenuation, float quadraticAttenuation)
    : position_(position), constantAttenuation_(constantAttenuation), linearAttenuation_(linearAttenuation),
      quadraticAttenuation_(quadraticAttenuation), lightType_(LightInstance::LightType::POINT) {
    this->InitBasicLight_(name, ambient, diffuse, specular);
}

LightInstance::LightInstance(const std::string& name, const glm::vec3& position, const glm::vec3& direction,
    const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float constantAttenuation,
    float linearAttenuation, float quadraticAttenuation, float cutoff, float exponent)
    : position_(position), direction_(direction), innerCutoff_(cutoff), exponent_(exponent),
      constantAttenuation_(constantAttenuation), linearAttenuation_(linearAttenuation),
      quadraticAttenuation_(quadraticAttenuation), lightType_(LightInstance::LightType::SPOT) {
    this->InitBasicLight_(name, ambient, diffuse, specular);
}

const std::string& LightInstance::GetName() const {
    return this->name_;
}

void LightInstance::SetName(const std::string& name) {
    this->name_ = name;
}

const glm::vec3& LightInstance::GetPosition() const {
    return this->position_;
}

void LightInstance::SetPosition(const glm::vec3& position) {
    this->position_ = position;
}

const glm::vec3& LightInstance::GetAmbient() const {
    return this->ambientColor_;
}

void LightInstance::SetAmbient(const glm::vec3& ambient) {
    this->ambientColor_ = ambient;
}

const glm::vec3& LightInstance::GetDiffuse() const {
    return this->diffuseColor_;
}

void LightInstance::SetDiffuse(const glm::vec3& diffuse) {
    this->diffuseColor_ = diffuse;
}

const glm::vec3& LightInstance::GetSpecular() const {
    return this->specularColor_;
}

void LightInstance::SetSpecular(const glm::vec3& specular) {
    this->specularColor_ = specular;
}

const glm::vec3& LightInstance::GetDirection() const {
    return this->direction_;
}

void LightInstance::SetDirection(const glm::vec3& direction) {
    this->direction_ = direction;
}

float LightInstance::GetInnerCutoff() const {
    return this->innerCutoff_;
}

void LightInstance::SetInnerCutoff(float cutoff) {
    this->innerCutoff_ = cutoff;
}

float LightInstance::GetOuterCutoff() const {
    return this->outerCutoff_;
}

void LightInstance::SetOuterCutoff(float cutoff) {
    this->outerCutoff_ = cutoff;
}

float LightInstance::GetExponent() const {
    return this->innerCutoff_;
}

void LightInstance::SetExponent(float exponent) {
    this->exponent_ = exponent;
}

float LightInstance::GetConstantAttenuation() const {
    return this->constantAttenuation_;
}

void LightInstance::SetConstantAttenuation(float constantAttenuation) {
    this->constantAttenuation_ = constantAttenuation;
}

float LightInstance::GetLinearAttenuation() const {
    return this->constantAttenuation_;
}

void LightInstance::SetLinearAttenuation(float linearAttenuation) {
    this->linearAttenuation_ = linearAttenuation;
}

float LightInstance::GetQuadraticAttenuation() const {
    return this->constantAttenuation_;
}

void LightInstance::SetQuadraticAttenuation(float quadraticAttenuation) {
    this->quadraticAttenuation_ = quadraticAttenuation;
}

float LightInstance::GetAmbientIntensity() const {
    return this->ambientIntensity_;
}

void LightInstance::SetAmbientIntensity(float ambientIntensity) {
    this->ambientIntensity_ = ambientIntensity;
}

float LightInstance::GetDiffuseIntensity() const {
    return this->diffuseIntensity_;
}

void LightInstance::SetDiffuseIntensity(float diffuseIntensity) {
    this->diffuseIntensity_ = diffuseIntensity;
}

float LightInstance::GetSpecularIntensity() const {
    return this->specularIntensity_;
}

void LightInstance::SetSpecularIntensity(float specularIntensity) {
    this->specularIntensity_ = specularIntensity;
}

bool LightInstance::IsEnable() const {
    return this->isEnable_;
}

void LightInstance::SetEnable(bool isEnable) {
    this->isEnable_ = isEnable;
}

bool LightInstance::IsAmbient() const {
    return this->isAmbient_;
}

void LightInstance::SetAmbient(bool isAmbient) {
    this->isAmbient_ = isAmbient;
}

bool LightInstance::IsDiffuse() const {
    return this->isDiffuse_;
}

void LightInstance::SetDiffuse(bool isDiffuse) {
    this->isDiffuse_ = isDiffuse;
}

bool LightInstance::IsSpecular() const {
    return this->isDiffuse_;
}

void LightInstance::SetSpecular(bool isSpecular) {
    this->isSpecular_ = isSpecular;
}

LightInstance::LightType LightInstance::GetLightType() const {
    return this->lightType_;
}

void LightInstance::SetLightType(LightInstance::LightType lightType) {
    this->lightType_ = lightType;
}

void LightInstance::UpdateLight(ShaderProgram& shaderProgram) {
    BindableDataObjectGuard guard{shaderProgram};
    shaderProgram.SetUniformVector(std::format(LightInstance::POSITION_ARGUMENT_FORMAT_STR, this->name_), this->position_);
    shaderProgram.SetUniformVector(std::format(LightInstance::AMBIENT_COLOR_ARGUMENT_FORMAT_STR, this->name_), this->ambientColor_);
    shaderProgram.SetUniformVector(std::format(LightInstance::DIFFUSE_COLOR_ARGUMENT_FORMAT_STR, this->name_), this->diffuseColor_);
    shaderProgram.SetUniformVector(std::format(LightInstance::SPECULAR_COLOR_ARGUMENT_FORMAT_STR, this->name_), this->specularColor_);
    shaderProgram.SetUniformVector(std::format(LightInstance::DIRECTION_ARGUMENT_FORMAT_STR, this->name_), this->direction_);
    shaderProgram.SetUniformFloat(std::format(LightInstance::INNER_CUTOFF_ARGUMENT_FORMAT_STR, this->name_), this->innerCutoff_);
    shaderProgram.SetUniformFloat(std::format(LightInstance::OUTER_CUTOFF_ARGUMENT_FORMAT_STR, this->name_), this->outerCutoff_);
    shaderProgram.SetUniformFloat(std::format(LightInstance::EXPONENT_ARGUMENT_FORMAT_STR, this->name_), this->exponent_);
    shaderProgram.SetUniformFloat(std::format(LightInstance::CONSTANT_ATTENUATION_ARGUMENT_FORMAT_STR, this->name_), this->constantAttenuation_);
    shaderProgram.SetUniformFloat(std::format(LightInstance::LINEAR_ATTENUATION_ARGUMENT_FORMAT_STR, this->name_), this->linearAttenuation_);
    shaderProgram.SetUniformFloat(std::format(LightInstance::QUADRATIC_ATTENUATION_ARGUMENT_FORMAT_STR, this->name_), this->quadraticAttenuation_);
    shaderProgram.SetUniformFloat(std::format(LightInstance::AMBIENT_INTENSITY_ARGUMENT_FORMAT_STR, this->name_), this->ambientIntensity_);
    shaderProgram.SetUniformFloat(std::format(LightInstance::DIFFUSE_INTENSITY_ARGUMENT_FORMAT_STR, this->name_), this->diffuseIntensity_);
    shaderProgram.SetUniformFloat(std::format(LightInstance::SPECULAR_INTENSITY_ARGUMENT_FORMAT_STR, this->name_), this->specularIntensity_);
    shaderProgram.SetUniformInt(std::format(LightInstance::TYPE_ARGUMENT_FORMAT_STR, this->name_), static_cast<int>(this->lightType_));
    shaderProgram.SetUniformInt(std::format(LightInstance::IS_ENABLE_ARGUMENT_FORMAT_STR, this->name_), static_cast<int>(this->isEnable_));
    shaderProgram.SetUniformInt(std::format(LightInstance::IS_AMBIENT_ARGUMENT_FORMAT_STR, this->name_), static_cast<int>(this->isAmbient_));
    shaderProgram.SetUniformInt(std::format(LightInstance::IS_DIFFUSE_ARGUMENT_FORMAT_STR, this->name_), static_cast<int>(this->isDiffuse_));
    shaderProgram.SetUniformInt(std::format(LightInstance::IS_SPECULAR_ARGUMENT_FORMAT_STR, this->name_), static_cast<int>(this->isSpecular_));
}

void LightInstance::InitName_(const std::string& name) {
    this->name_ = std::string();

    for (const char symbol : name) {
        this->name_ += symbol == ' ' ? '_' : symbol;
    }
}

void LightInstance::InitBasicLight_(
    const std::string& name, const glm::vec3& ambient, const glm::vec3& diffuse,
    const glm::vec3& specular) {
    this->InitName_(name);
    this->ambientColor_  = ambient;
    this->diffuseColor_  = diffuse;
    this->specularColor_ = specular;
}
