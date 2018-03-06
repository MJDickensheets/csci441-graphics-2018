#version 330 core
in vec3 ourColor;
in vec3 Normal;
in vec3 FragPos;

out vec4 fragColor;

uniform vec3 light;
uniform vec3 viewPos;
uniform mat4 model;
uniform mat4 camera;
uniform mat4 projection;
uniform float shiny;

vec3 lightColor = vec3(1.0, 1.0, 1.0);

float ambientStrength = 0.1;
vec3 ambient = ambientStrength * lightColor;

vec3 norm = normalize(Normal);
vec3 lightDir = normalize(light - FragPos);

float diff = max(dot(norm, lightDir), 0.0);
vec3 diffuse = diff * lightColor;

float specularStrength = 0.5;
vec3 viewDir = normalize(viewPos - FragPos);
vec3 reflectDir = -lightDir + 2 * dot(lightDir, norm) * norm;

float spec = pow(max(dot(viewDir, reflectDir), 0.0), shiny);
vec3 specular = specularStrength * spec * lightColor;

vec3 result = (ambient + diffuse + specular) * ourColor;
void main() {
    fragColor = vec4(result, 1.0f);
}
