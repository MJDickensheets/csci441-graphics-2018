#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec3 aColor;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 camera;
uniform mat4 inv;

out vec3 Normal;
out vec3 ourColor;
out vec3 FragPos;

void main() {
    gl_Position = projection * camera * model * vec4(aPos, 1.0);
    ourColor = aColor;
    Normal =  vec3(inv * vec4(aNorm, 1.0));
    FragPos = vec3(model * vec4(aPos, 1.0));
}
