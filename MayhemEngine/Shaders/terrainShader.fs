#version 330 core

#define MAX_POINT_LIGHTS 100
#define MAX_DIRECTION_LIGHTS 100
#define MAX_SPOT_LIGHTS 100

struct Material
{
    sampler2D texture_diffuse;
    sampler2D texture_specular;
    sampler2D texture_slope;
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
uniform PointLight pointLights[10];
uniform DirectionLight directionLights[10];
uniform SpotLight spotLights[10];
uniform Material material;

const float maxSlope = 0.4;
const float levels = 3.0;
const bool celShading = true;
const float colorBitDepth = 6;

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPosition, vec3 viewDirection);
vec3 CalcDirectionLight(DirectionLight light, vec3 normal, vec3 viewDirection);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPosition, vec3 viewDirection);
vec3 CalcColorBitDepth(vec3 color);

bool isSlopeTexture;

void calcDefaultTexture()
{
    vec3 downDirection = vec3(0.0, -1.0, 0.0);
    float slope = dot(Normal, downDirection);
    isSlopeTexture = !(slope > maxSlope || slope < -maxSlope);
}

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDirection = normalize(cameraPosition - FragPos);
    vec3 result = vec3(0.0, 0.0, 0.0);

    calcDefaultTexture();

    for (int i = 0; i < numberPointLights; i++)
    {
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDirection);
    }

    for (int i = 0; i < numberDirectionLights; i++)
    {
       result += CalcDirectionLight(directionLights[i], norm, viewDirection);
    }

    for (int i = 0; i < numberSpotLights; i++)
    {
        result += CalcSpotLight(spotLights[i], norm, FragPos, viewDirection);
    }

    FragColor = vec4(result, 1.0);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPosition, vec3 viewDirection)
{
    vec3 lightDirection = normalize(light.position - fragPosition);
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 1.0);

    // Cel shading
    if (celShading)
    {
        float level = floor(diff * levels);
        diff = level / levels;
    }

    float distance = length(light.position - fragPosition);
    float attenuation = 1.0 / (light.constant + light.linear + distance + light.quadratic * distance * distance);

    vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.texture_diffuse, TexCoords));

    if (isSlopeTexture)
    {
        ambient = light.ambient * vec3(texture(material.texture_slope, TexCoords));
        diffuse = light.diffuse * diff * vec3(texture(material.texture_slope, TexCoords));
        specular = light.specular * spec * vec3(texture(material.texture_slope, TexCoords));
    }

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 CalcDirectionLight(DirectionLight light, vec3 normal, vec3 viewDirection)
{
    vec3 lightDirection = normalize(-light.direction);
    float diff = max(dot(normal, lightDirection), 0.0);

    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 1.0);

    // Cel shading
    if (celShading)
    {
        float level = floor(diff * levels);
        diff = level / levels;
    }

    vec3 ambient = light.ambient * CalcColorBitDepth(vec3(texture(material.texture_diffuse, TexCoords)));
    vec3 diffuse = light.diffuse * diff * CalcColorBitDepth(vec3(texture(material.texture_diffuse, TexCoords)));
    vec3 specular = light.specular * spec * CalcColorBitDepth(vec3(texture(material.texture_diffuse, TexCoords)));

    if (isSlopeTexture)
    {
        ambient = light.ambient * CalcColorBitDepth(vec3(texture(material.texture_slope, TexCoords)));
        diffuse = light.diffuse * diff * CalcColorBitDepth(vec3(texture(material.texture_slope, TexCoords)));
        specular = light.specular * spec * CalcColorBitDepth(vec3(texture(material.texture_slope, TexCoords)));
    }
    return (ambient + specular + diffuse);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPosition, vec3 viewDirection)
{
    vec3 lightDirection = normalize(light.position - fragPosition);

    float diff = max(dot(normal, lightDirection), 0.0);

    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 1.0);

    float distance = length(light.position - fragPosition);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    float theta = dot(lightDirection, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // Cel shading
    if (celShading)
    {
        float level = floor(diff * levels);
        diff = level / levels;
    }

    vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.texture_diffuse, TexCoords));

    if (isSlopeTexture)
    {
        ambient = light.ambient * vec3(texture(material.texture_slope, TexCoords));
        diffuse = light.diffuse * diff * vec3(texture(material.texture_slope, TexCoords));
        specular = light.specular * spec * vec3(texture(material.texture_slope, TexCoords));
    }

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}

vec3 CalcColorBitDepth(vec3 color)
{
    vec3 level = vec3(
        floor(color.x * colorBitDepth),
        floor(color.y * colorBitDepth),
        floor(color.z * colorBitDepth)
    );
    return color;
}
