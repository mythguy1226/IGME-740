#version 430

uniform mat4 modelMat;
uniform mat4 viewMat; 
uniform mat4 projMat; 
uniform vec3 lightPos1;
uniform vec3 lightPos2;

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;

out vec4 normal;
out vec4 ppos;
out vec4 eyePos;

out vec3 ambientColor1;
out vec3 diffuseColor1;
out vec3 specularColor1;
out vec4 lightDir1;

out vec3 ambientColor2;
out vec3 diffuseColor2;
out vec3 specularColor2;
out vec4 lightDir2;

void main() {
  vec4 lpos = viewMat * vec4(lightPos1, 1.0f);
  ppos = viewMat * modelMat * vec4 (vertex_position, 1.0f);
  eyePos = vec4(viewMat[0][3], viewMat[1][3], viewMat[2][3], 0.0f);
  
  // Get light 1 values to pass to frag
  lightDir1 = normalize(lpos - ppos);
  normal = normalize (viewMat * modelMat * vec4(vertex_normal, 0.0f));
  ambientColor1 = vec3(0.0f, 0.15f, 0.0f);
  diffuseColor1 = vec3(1.0, 1.0, 0.0);
  specularColor1 = vec3(1.0f, 0.0f, 0.0f);
  
  // Get light 2 values to pass to frag
  lpos = viewMat * vec4(lightPos2, 1.0f);
  lightDir2 = normalize(lpos - ppos);
  ambientColor2 = vec3(0.0f, 0.0f, 0.15f);
  diffuseColor2 = vec3(1.0, 0.0, 1.0);
  specularColor2 = vec3(1.0f, 0.0f, 0.0f);
	
  gl_Position = projMat * viewMat * modelMat * vec4(vertex_position, 1.0f);
}




