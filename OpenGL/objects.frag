out vec4 fColor;

struct DirectionalLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 fragPos;
in vec3 normal;
in vec2 texCoord;

uniform vec3 viewPos;
uniform DirectionalLight directLight;
uniform PointLight pointLight;
uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;
uniform float shininess;

vec3 calDirectLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 calPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {    
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);
    
    vec3 result = calDirectLight(directLight, norm, viewDir) + calPointLight(pointLights[i], norm, fragPos, viewDir);     
    
    fColor = vec4(result, 1.0);
}

vec3 calDirectLight(DirectionalLight light, vec3 normal, vec3 viewDir) {

    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    vec3 ambient = light.ambient * vec3(texture(texture_diffuse, texCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture_diffuse, texCoord));
    vec3 specular = light.specular * spec * vec3(texture(texture_specular, texCoord));

    return (ambient + diffuse + specular);
}

vec3 calPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {

    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    vec3 ambient = light.ambient * vec3(texture(texture_diffuse, texCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse, texCoord));
    vec3 specular = light.specular * spec * vec3(texture(texture_specular, texCoord));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}