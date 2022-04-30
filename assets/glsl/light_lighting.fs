# version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

# 片段法向量
in vec3 Normal;
# 光源位置
uniform vec3 lightPos;
# 观察位置
uniform vec3 viewPos;
# 片段位置
in vec3 FragPos;

void main() {
    # 环境光照
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    # 漫反射
    # 法线向量标准化
    vec3 norm = normalize(Normal);
    # 片段上光线照射的方向向量
    vec3 lightDir = normalize(lightPos - FragPos);
    # 法向量和光照方向向量点乘，得到漫反射影响，角度越小，值越大，影响越大
    float diff = max(dot(norm, lightDir), 0.0);
    # 计算漫反射分量
    vec3 diffuse = diff * lightColor;

    # 镜面反射
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    # 计算所有光照
    vec3 result = (ambient + diffuse + specular) * objectColor;

    FragColor = vec4(diffuse * objectColor, 1.0);
}