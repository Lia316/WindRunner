layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec4 vColor;
layout (location = 2) in vec2 vTexCoord;
layout (location = 3) in vec3 vNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 lightPosition;   // point light
uniform vec4 lightDirection;  // directional light
uniform vec3 viewPos;

uniform float shininess;
uniform sampler2D texture_diffuse;
uniform sampler2D texture_normal;
uniform sampler2D texture_specular;

out vec4 color;

vec4 calDirectLight();
vec4 calPointLight();

void main() {
    vec4 result = calDirectLight() + calPointLight();
    //vec4 result = calDirectLight();
    //vec4 result = calPointLight();

    color = vec4(result.xyz, 1.0);
    gl_Position = projection * view * model * vec4(vPosition, 1.0f);
}

vec4 calDirectLight() {
    vec4 light_ambient = vec4(0.1f, 0.1f, 0.1f, 1.0f);
    vec4 light_diffuse = vec4(0.2f, 0.2f, 0.2f, 1.0f);
    vec4 light_specular = vec4(0.5f, 0.5f, 0.5f, 1.0f);

    vec3 pos = (model * vec4(vPosition, 1.0f)).xyz;
    vec3 L = normalize(-lightDirection).xyz;
    vec3 E = normalize(viewPos - pos);
    vec3 H = normalize(L + E);
    vec3 N = normalize(transpose(inverse(model)) * vec4(vNormal, 0.0f)).xyz;    

    float kd = max(dot(L, N), 0.0); 
    float ks = pow(max(dot(N, H), 0.0), shininess);

    vec4 ambient = light_ambient * texture(texture_diffuse, vTexCoord); 
    vec4 diffuse = light_diffuse * kd * texture(texture_diffuse, vTexCoord);
    vec4 specular = light_specular * ks * texture(texture_specular, vTexCoord);

    if(dot(L, N) < 0.0) {
        specular = vec4(0.0, 0.0, 0.0, 1.0);
    }

    vec4 result = ambient + diffuse + specular;
    return vec4(result.xyz, 1.0);
}

vec4 calPointLight() {
    vec4 light_ambient = vec4(0.9f, 0.9f, 0.9f, 1.0f);
    vec4 light_diffuse = vec4(0.7f, 0.7f, 0.7f, 1.0f);
    vec4 light_specular = vec4(1.0f, 1.0f, 1.0f, 1.0f);

    vec3 pos = (model * vec4(vPosition, 1.0f)).xyz;
    vec3 L = normalize(lightPosition.xyz - pos);
    vec3 E = normalize(viewPos - pos);
    vec3 H = normalize(L + E);
    vec3 N = normalize(transpose(inverse(model)) * vec4(vNormal, 0.0f)).xyz;

    float kd = max(dot(L, N), 0.0);
    float ks = pow(max(dot(N, H), 0.0), shininess);

    vec4 ambient = light_ambient * texture(texture_diffuse, vTexCoord);
    vec4 diffuse = light_diffuse * kd * texture(texture_diffuse, vTexCoord);
    vec4 specular = light_specular * ks * texture(texture_specular, vTexCoord);

    if(dot(L, N) < 0.0) {
        specular = vec4(0.0, 0.0, 0.0, 1.0);
    }

    float constant = 1.0f;
    float linear = 0.0003f;
    float quadratic = 0.0001f;
    float distance = length(lightPosition.xyz - pos);
    float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));    

    vec4 result = (ambient + diffuse + specular) * attenuation;
    return vec4(result.xyz, 1.0);
}