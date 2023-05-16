layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

out vec4 color;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 projection_view;

void main() {
    gl_Position = projection_view * model * vec4(aPos, 1.0f);
    color = aColor;
    texCoord = aTexCoord;
}