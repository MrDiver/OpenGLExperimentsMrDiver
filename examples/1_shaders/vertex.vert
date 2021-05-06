#version 330 core

layout(location=0)in vec2 aPos;
uniform vec2 positionOffset;
out vec4 position;
void main()
{
    gl_Position=vec4(aPos.x+positionOffset.x,aPos.y+positionOffset.y,0.f,1.f);
    position = vec4(aPos,0.0f,0.0f);
}
