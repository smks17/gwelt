#version 330 core

in vec3 outColor;
in vec2 outTexCoord;

uniform sampler2D outTexture;

out vec4 FragColor;

void main()
{
    FragColor = texture(outTexture, outTexCoord);
}
