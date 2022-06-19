#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 textureCoord;

out vec4 vColor;
out vec2 texCoord;

uniform mat4 modelToWorld;
uniform mat4 worldToCamera;
uniform mat4 cameraToView;

void main()
{
  gl_Position = cameraToView * worldToCamera * modelToWorld * vec4(position, 1.0);
//  vColor = vec4(normal, 1.0);
//  vColor = vec4(textureCoord,1.0,1.0);
//  vColor = vec4(position,1.0);
  texCoord = textureCoord;
}
