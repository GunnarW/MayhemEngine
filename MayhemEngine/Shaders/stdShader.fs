#version 330 core

#define MAX_POINT_LIGHTS 100
#define MAX_DIRECTION_LIGHTS 100
#define MAX_SPOT_LIGHTS 100

struct Material
{
    sampler2D texture_diffuse;
    sampler2D texture_specular;
    float shininess;
};

struct PointLight
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct DirectionLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;
};

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 cameraPosition;
uniform int numberPointLights;
uniform int numberDirectionLights;
uniform int numberSpotLights;
uniform PointLight pointLights[100];
uniform DirectionLight directionLights[100];
uniform SpotLight spotLights[100];
uniform Material material;

uniform sampler2D texture_diffuse1;

const float levels = 3.0;

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPosition, vec3 viewDirection);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDirection = normalize(cameraPosition - FragPos);
    vec3 result = vec3(0.0, 0.0, 0.0);

    for (int i = 0; i < numberPointLights; i++)
    {
        result += CalcPointLight(pointLights[i], Normal, FragPos, viewDirection);
    }

    FragColor = vec4(result, 1.0);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPosition, vec3 viewDirection)
{
    vec3 lightDirection = normalize(light.position - fragPosition);
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 0.5);

    // Cel shading
    float level = floor(diff * levels);
    diff = level / levels;

    float distance = length(light.position - fragPosition);
    float attenuation = 1.0 / (light.constant + light.linear + distance + light.quadratic * distance * distance);

    vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(texture_diffuse1, TexCoords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}
