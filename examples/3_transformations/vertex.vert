#version 330 core

layout(location=0)in vec3 aPos;
layout(location=1)in vec3 aColor;
layout(location=2)in vec2 texCoord;

out vec4 relativePosition;
out vec4 absolutePosition;
out vec3 Color;
out vec2 TexCoord;

uniform float timeVert;
uniform vec2 positionOffset;
void main()
{
    float timeVert=timeVert/50+1;
    gl_Position=vec4(aPos.x*timeVert+positionOffset.x,aPos.y*timeVert+positionOffset.y,0.f,1.f);
    relativePosition = vec4(aPos.xy,0.0f,0.0f);
    absolutePosition = gl_Position;
    Color = aColor; 
    TexCoord = texCoord;
}
