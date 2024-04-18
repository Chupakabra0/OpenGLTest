#include "ArgParseMeshGeneratorCreator/BaseArgParseMeshGeneratorCreator/BaseArgParseMeshGeneratorCreator.hpp"

BaseArgParseMeshGeneratorCreator::BaseArgParseMeshGeneratorCreator(const std::shared_ptr<IMeshGeneratorFactory>& meshGeneratorFactory)
    : meshGeneratorFactory_(meshGeneratorFactory) {
    if (this->meshGeneratorFactory_ == nullptr) {
        throw std::runtime_error("Mesh factory is null");
    }
}
