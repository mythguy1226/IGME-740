#version 430

uniform mat4 modelMat; 
uniform mat4 viewMat;
uniform mat4 projMat; 
uniform vec3 lightPos;

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;

out vec3 color;

void main() {
  
  vec4 lpos = viewMat * vec4(lightPos, 1.0f);
  vec4 ppos = viewMat * modelMat * vec4 (vertex_position, 1.0f);
  vec4 lightDir = normalize(lpos - ppos);
  
  vec4 normal = normalize (viewMat * modelMat * vec4(vertex_normal, 0.0f));
  
  float intensity = max(dot(normal, lightDir), 0.0);
  
  vec4 reflection = (2 * normal * dot(normal, lightDir)) - lightDir;
  vec4 eyePos = vec4(viewMat[0][3], viewMat[1][3], viewMat[2][3], 0.0f);
  vec4 vDir = normalize(eyePos - ppos);
  float specularIntensity = pow(max(dot(reflection, vDir), 0.0), 10.0f);
  
  color = vec3(0.0f, 0.15f, 0.0f) + (0.5f * intensity * vec3(1.0f, 1.0f, 0.0f)) + (specularIntensity * vec3(1.0, 0.0, 0.0));
	
  gl_Position = projMat * viewMat * modelMat * vec4(vertex_position, 1.0f);
}




