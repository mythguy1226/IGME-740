#version 430
in vec4 normal;
in vec4 ppos;
in vec4 eyePos;

in vec3 ambientColor1;
in vec3 diffuseColor1;
in vec3 specularColor1;
in vec4 lightDir1; 

in vec3 ambientColor2;
in vec3 diffuseColor2;
in vec3 specularColor2;
in vec4 lightDir2;

out vec4 frag_color;

void main() {
  // Ambient component for light 1
  float ambientCoef = 0.6f;
  vec3 ambient = ambientCoef * ambientColor1;
  
  // Diffuse component for light 1
  float diffuseCoef = 0.5f;
  float diffuseIntensity = max(dot(normal, lightDir1), 0.0);
  vec3 diffuse = diffuseCoef * diffuseIntensity * diffuseColor1;
  
  // Specular component for light 1
  float specularCoef = 0.8f;
  vec4 reflection = (2 * normal * dot(normal, lightDir1)) - lightDir1;
  vec4 vDir = normalize(eyePos - ppos);
  float specularIntensity = pow(max(dot(reflection, vDir), 0.0), 10.0f);
  vec3 specular = specularCoef * specularIntensity * specularColor1;
  
  // Combine all components to get final color 1
  vec3 color1 = ambient + diffuse + specular;
  
  // Ambient component for light 2
  ambientCoef = 0.6f;
  ambient = ambientCoef * ambientColor2;
  
  // Diffuse component for light 2
  diffuseCoef = 0.5f;
  diffuseIntensity = max(dot(normal, lightDir2), 0.0);
  diffuse = diffuseCoef * diffuseIntensity * diffuseColor2;
  
  // Specular component for light 2
  specularCoef = 0.8f;
  reflection = (2 * normal * dot(normal, lightDir2)) - lightDir2;
  vDir = normalize(eyePos - ppos);
  specularIntensity = pow(max(dot(reflection, vDir), 0.0), 10.0f);
  specular = specularCoef * specularIntensity * specularColor2;
  
  // Combine all components to get final color 2
  vec3 color2 = ambient + diffuse + specular;

  frag_color = vec4(color1 + color2, 0.0f);
}