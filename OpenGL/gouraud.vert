#version 150
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec4 vColor;
layout (location = 2) in vec2 vTexCoord;
layout (location = 3) in vec3 vNormal;

out vec4 color;

uniform mat4 modelView;
uniform mat4 projection;
uniform vec4 lightPosition;   // point light
uniform vec4 lightDirection;  // directional light

uniform float shininess;
uniform sampler2D texture_diffuse;
uniform sampler2D texture_normal;
uniform sampler2D texture_specular;

vec3 calDirectLight();
vec3 calPointLight();

void main() {
    vec4 result = calDirectLight() + calPointLight();

    fColor = vec4(result.xyz, 1.0);
    gl_Position = projection * modelView * vec4(vPosition, 1.0f);
}

vec4 calDirectLight() {
    vec4 light_ambient = vec4(0.2f, 0.2f, 0.2f, 1.0f);
    vec4 light_diffuse = vec4(0.4f, 0.4f, 0.4f, 1.0f);
    vec4 light_specular = vec4(0.5f, 0.5f, 0.5f, 1.0f);

    vec3 pos = (modelView * vec4(vPosition, 1.0f)).xyz;
    vec3 L = normalize(lightDirection).xyz;
    vec3 E = normalize(-pos);
    vec3 H = normalize(L + E);
    vec3 N = normalize(modelView * vec4(vNormal, 0.0)).xyz;

    float kd = max(dot(L, N), 0.0);
    float ks = pow(max(dot(N, H), 0.0), shininess);

    vec4 ambient = light_ambient * texture(texture_diffuse, texCoord);
    vec4 diffuse = light_diffuse * kd * texture(texture_diffuse, texCoord);
    vec4 specular = light_specular * ks * texture(texture_specular, texCoord);

    if(dot(L, N) < 0.0) {
        specular = vec4(0.0, 0.0, 0.0, 1.0);
    }

    vec4 result = ambient + diffuse + specular;
    return result;
}

vec4 calPointLight() {
    vec4 light_ambient = vec4(0.8f, 0.8f, 0.8f, 1.0f);
    vec4 light_diffuse = vec4(0.3f, 0.3f, 0.3f, 1.0f);
    vec4 light_specular = vec4(1.0f, 1.0f, 1.0f, 1.0f);

    vec3 pos = (modelView * vec4(vPosition, 1.0f)).xyz;
    vec3 L = normalize(lightPosition.xyz - pos);
    vec3 E = normalize(-pos);
    vec3 H = normalize(L + E);
    vec3 N = normalize(modelView * vec4(vNormal, 0.0)).xyz;

    float kd = max(dot(L, N), 0.0);
    float ks = pow(max(dot(N, H), 0.0), shininess);

    vec4 ambient = light_ambient * texture(texture_diffuse, texCoord);
    vec4 diffuse = light_diffuse * kd * texture(texture_diffuse, texCoord);
    vec4 specular = light_specular * ks * texture(texture_specular, texCoord);

    if(dot(L, N) < 0.0) {
        specular = vec4(0.0, 0.0, 0.0, 1.0);
    }

    float constant = 1.0f;
    float linear = 0.0003f;
    float quadratic = 0.0001f;

    float distance = length(lightPosition.xyz - pos);
    float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));    

    vec4 result = (ambient + diffuse + specular) * attenuation;
    return result;
}
