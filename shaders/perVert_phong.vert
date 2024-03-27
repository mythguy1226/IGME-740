#version 430

uniform mat4 modelMat; 
uniform mat4 viewMat;
uniform mat4 projMat; 
uniform vec3 lightPos1;
uniform vec3 lightPos2;

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;

out vec3 color;

void main() {
  
  // First light
  vec4 lpos = viewMat * vec4(lightPos1, 1.0f);
  vec4 ppos = viewMat * modelMat * vec4 (vertex_position, 1.0f);
  vec4 lightDir = normalize(lpos - ppos);
  
  vec4 normal = normalize (viewMat * modelMat * vec4(vertex_normal, 0.0f));
  
  // Ambient component for light 1
  float ambientCoef = 0.6f;
  vec3 ambient = ambientCoef * vec3(0.0f, 0.15f, 0.0f);
  
  // Diffuse component for light 1
  float diffuseCoef = 0.5f;
  float diffuseIntensity = max(dot(normal, lightDir), 0.0);
  vec3 diffuse = diffuseCoef * diffuseIntensity * vec3(1.0f, 1.0f, 0.0f);
  
  // Specular component for light 1
  float specularCoef = 0.8f;
  vec4 reflection = (2 * normal * dot(normal, lightDir)) - lightDir;
  vec4 eyePos = vec4(viewMat[0][3], viewMat[1][3], viewMat[2][3], 0.0f);
  vec4 vDir = normalize(eyePos - ppos);
  float specularIntensity = pow(max(dot(reflection, vDir), 0.0), 10.0f);
  vec3 specular = specularCoef * specularIntensity * vec3(1.0, 0.0, 0.0);
  
  // Combine all components to get final color 1
  vec3 color1 = ambient + diffuse + specular;
  
  // Second light
  lpos = viewMat * vec4(lightPos2, 1.0f);
  lightDir = normalize(lpos - ppos);
  
  // Ambient component for light 2
  ambientCoef = 0.6f;
  ambient = ambientCoef * vec3(0.0f, 0.0f, 0.15f);
  
  // Diffuse component for light 2
  diffuseCoef = 0.5f;
  diffuseIntensity = max(dot(normal, lightDir), 0.0);
  diffuse = diffuseCoef * diffuseIntensity * vec3(1.0f, 0.0f, 1.0f);
  
  // Specular component for light 2
  specularCoef = 0.8f;
  reflection = (2 * normal * dot(normal, lightDir)) - lightDir;
  eyePos = vec4(viewMat[0][3], viewMat[1][3], viewMat[2][3], 0.0f);
  vDir = normalize(eyePos - ppos);
  specularIntensity = pow(max(dot(reflection, vDir), 0.0), 10.0f);
  specular = specularCoef * specularIntensity * vec3(1.0, 0.0, 0.0);
  
  // Combine all components to get final color 2
  vec3 color2 = ambient + diffuse + specular;
  
  color = color1 + color2;
	
  gl_Position = projMat * viewMat * modelMat * vec4(vertex_position, 1.0f);
}




