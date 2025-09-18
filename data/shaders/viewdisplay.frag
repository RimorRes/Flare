#version 450

layout (binding = 0) uniform sampler2DArray samplerView;

layout (location = 0) in vec2 inUV;
layout (location = 0) out vec4 outColor;

void main()
{
    // Determine which eye based on horizontal position
    int eye = inUV.x < 0.5 ? 0 : 1;
    // Remap UV to [0,1] for each half
    vec2 uv = inUV;
    uv.x = inUV.x * 2.0;
    if (eye == 1) uv.x = (inUV.x - 0.5) * 2.0;
    outColor = texture(samplerView, vec3(uv, eye));
}