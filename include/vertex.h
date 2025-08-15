//
// Created by maxim on 14/08/2025.
//

#ifndef FLARE_VERTEX_H
#define FLARE_VERTEX_H

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>

#include <array>


struct Vertex {
    glm::vec2 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription getBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions();
};

#endif //FLARE_VERTEX_H