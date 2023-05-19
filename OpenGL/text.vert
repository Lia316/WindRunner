layout(location = 0) in vec2 vPosition;
layout(location = 1) in vec2 vTexCoord;

out vec2 texCoord;

void main() {
	vec2 pos = vPosition - vec2(400,300);
	pos /= vec2(400,300);
	gl_Position =  vec4(pos, 0 ,1);
	
	texCoord = vTexCoord;
}

