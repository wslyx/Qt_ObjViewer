#version 450 core

in highp vec4 vColor;
in highp vec2 texCoord;
out highp vec4 fColor;

uniform sampler2D texture_diffuse;

void main()
{
//   fColor = vColor;
//    fColor = vec4(0.0f,0.8f,0.0f,0.8f);
    fColor = texture2D(texture_diffuse, texCoord);
}
