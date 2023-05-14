#version 150

in  vec4 color;
in vec2 texCoord;

out vec4 fColor;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_normal;
uniform sampler2D texture_specular;

void main() {
    fColor = texture(texture_diffuse, texCoord) * color;
}