in vec2 texCoord;
out vec4 color;

uniform sampler2D texture_sample;

void main() {
	color = texture(texture_sample, texCoord);
}