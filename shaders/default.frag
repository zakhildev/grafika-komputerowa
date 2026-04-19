#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture_diffuse1;
uniform int hasTextures;

uniform vec3 viewPos;

struct Material {
  vec3 diffuse;
  vec3 specular;
  float shininess;
  float metallic;
  float alpha;
};

uniform Material material;

void main()
{    
  // Get base color and alpha
  vec3 color;
  float alpha = material.alpha;
  
  if (hasTextures == 1) {
    vec4 texColor = texture(texture_diffuse1, TexCoords);
    color = texColor.rgb;
    alpha = texColor.a;
  } else {
    color = material.diffuse;
  }
  
  // Normalize normal
  vec3 norm = normalize(Normal);
  
  // Light direction and position (fixed light above)
  vec3 lightPos = vec3(2.0, 3.0, 2.0);
  vec3 lightDir = normalize(lightPos - FragPos);
  
  // Ambient
  float ambientStrength = 0.3;
  vec3 ambient = ambientStrength * color;
  
  // Diffuse
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * color;
  
  // Specular - much stronger for metallic materials
  float shininess = material.shininess;
  float specStrength = 0.3;
  
  // For metallic materials, dramatically increase specular
  if (material.metallic > 0.0) {
    specStrength = mix(0.3, 2.0, material.metallic);
    shininess = mix(material.shininess, 256.0, material.metallic);
    diffuse *= (1.0 - material.metallic * 0.7); // Make diffuse much darker
  }
  
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
  
  // For metallic, use a brighter specular color (more white)
  vec3 specColor = material.specular;
  if (material.metallic > 0.0) {
    specColor = mix(material.specular, vec3(1.0), material.metallic * 0.5);
  }
  
  vec3 specular = specStrength * spec * specColor;
  
  vec3 result = ambient + diffuse + specular;
  FragColor = vec4(result, alpha);
}