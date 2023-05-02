in  vec4 vPosition;
in  vec4 vColor;
out vec4 color;

uniform mat4 model_view;

void main() {
    gl_Position = model_view * vPosition / vPosition.w;
    color = vColor;
}