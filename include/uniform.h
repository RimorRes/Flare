//
// Created by maxim on 16/08/2025.
//

#ifndef FLARE_UNIFORM_H
#define FLARE_UNIFORM_H

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <glm/glm.hpp>


struct UniformBufferObject   {
    alignas(16) glm::mat4 model[2];
    alignas(16) glm::mat4 view[2];
    alignas(16) glm::mat4 proj[2];
};


#endif //FLARE_UNIFORM_H