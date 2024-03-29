#version 150

in vec3 fN;
in vec3 fE;
in vec3 fL_d;
in vec3 fL_p;
in vec3 fragPos;
in vec2 texCoord;

uniform float shininess;
uniform sampler2D texture_diffuse;
uniform sampler2D texture_normal;
uniform sampler2D texture_specular;

out vec4 fColor;

vec4 calDirectLight();
vec4 calPointLight();

void main() {
    vec4 result = calDirectLight() + calPointLight();
    //vec4 result = calDirectLight();
    //vec4 result = calPointLight();

    fColor = vec4(result.xyz, 1.0f);
}

vec4 calDirectLight() {
    vec4 light_ambient = vec4(0.05f, 0.05f, 0.05f, 1.0f);
    vec4 light_diffuse = vec4(0.2f, 0.2f, 0.2f, 1.0f);
    vec4 light_specular = vec4(0.5f, 0.5f, 0.5f, 1.0f);

    vec3 N = normalize(fN);
    vec3 T = dFdx(fragPos);
    vec3 B = dFdy(fragPos);
    vec3 E = normalize(fE);
    vec3 L = normalize(fL_d);
    vec3 H = normalize(L + E);

    mat3 TBN = transpose(mat3(T, B, N)); 
    vec3 normMap = texture(texture_normal, texCoord).rgb; 
    normMap = normMap * 2.0 - 1.0;
    vec3 N_mapped = normalize(TBN * normMap);

    float kd = max(dot(L, N_mapped), 0.0);
    float ks = pow(max(dot(N_mapped, H), 0.0), shininess);

    vec4 ambient = light_ambient * texture(texture_diffuse, texCoord);
    vec4 diffuse = light_diffuse * kd * texture(texture_diffuse, texCoord);
    vec4 specular = light_specular * ks * texture(texture_specular, texCoord);
    
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

    vec3 N = normalize(fN);
    vec3 T = dFdx(fragPos);
    vec3 B = dFdy(fragPos);
    vec3 E = normalize(fE);
    vec3 L = normalize(fL_p);
    vec3 H = normalize(L + E);

    mat3 TBN = transpose(mat3(T, B, N)); 
    vec3 normMap = texture(texture_normal, texCoord).rgb; 
    normMap = normMap * 2.0 - 1.0;
    vec3 N_mapped = normalize(TBN * normMap);

    float kd = max(dot(L, N_mapped), 0.0);
    float ks = pow(max(dot(N_mapped, H), 0.0), shininess);

    vec4 ambient = light_ambient * texture(texture_diffuse, texCoord);
    vec4 diffuse = light_diffuse * kd * texture(texture_diffuse, texCoord);
    vec4 specular = light_specular * ks * texture(texture_specular, texCoord);

    if(dot(L, N) < 0.0) {
        specular = vec4(0.0, 0.0, 0.0, 1.0);
    }

    float constant = 1.0f;
    float linear = 0.0003f;
    float quadratic = 0.0001f;
    float distance = length(fL_p);
    float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));    

    vec4 result = (ambient + diffuse + specular) * attenuation;
    return result;
}