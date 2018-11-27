#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture_diffuse1;
uniform vec3 cameraPosition;

void main()
{
    FragColor = texture(texture_diffuse1, TexCoords);
}
