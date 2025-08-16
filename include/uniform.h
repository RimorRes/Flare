//
// Created by maxim on 16/08/2025.
//

#ifndef FLARE_UNIFORM_H
#define FLARE_UNIFORM_H

#include <glm/glm.hpp>


struct UniformBufferObject   {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};


#endif //FLARE_UNIFORM_H