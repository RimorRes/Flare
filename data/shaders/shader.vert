#version 450

#extension GL_EXT_multiview : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 model[2];
    mat4 view[2];
    mat4 proj[2];
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;

void main() {
    int eye = int(gl_ViewIndex); // 0 for left, 1 for right
    gl_Position = ubo.proj[eye] * ubo.view[eye] * ubo.model[eye] * vec4(inPosition, 1.0);
    fragColor = inColor;
    fragTexCoord = inTexCoord;
}