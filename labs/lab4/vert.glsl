#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
uniform mat4 View;
uniform mat4 Model;
uniform mat4 proj;
uniform mat4 rotx;
uniform mat4 roty;
uniform mat4 rotz;

mat4 rot = rotx * roty * rotz;


vec4 canon = vec4(aPos, 1.0);
vec4 trans = proj * View * Model * rot * canon;

void main() {
    gl_Position = trans;
    ourColor = aColor;
}
