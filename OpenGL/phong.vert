layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec4 vColor;
layout (location = 2) in vec2 vTexCoord;
layout (location = 3) in vec3 vNormal;

out vec3 fN;
out vec3 fE;
out vec3 fL_d;
out vec3 fL_p;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 lightPosition;   // point light
uniform vec4 lightDirection;  // directional light
uniform vec3 viewPos;

void main() {
    vec3 fragPos = vec3(model * vec4(vPosition, 1.0));

    fN = transpose(inverse(mat3(model))) * vNormal; // vNormal;
    fE = viewPos - fragPos;
    fL_d = -lightDirection.xyz;
    fL_p = lightPosition.xyz - fragPos;

    texCoord = vTexCoord;
    gl_Position =  projection * view * model * vec4(vPosition, 1.0f);
}