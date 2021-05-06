#version 330 core

in vec4 relativePosition;
in vec4 absolutePosition;
in vec3 Color;
in vec2 TexCoord;
out vec4 color;
uniform vec3 colorChange;
uniform float time;
uniform sampler2D texture1;
uniform sampler2D texture2; 
uniform sampler2D texture3; 

float factor = 10;
float crazyOffset = 1;
float t = time*factor;
vec2 tc = TexCoord*(sin(time*20)+2)*3-crazyOffset;
void main(){
    vec2 awesomeCoords = vec2(cos(t)*tc.x-sin(t)*tc.y,
                              sin(t)*tc.x+cos(t)*tc.y)+crazyOffset;
    vec4 coloredAwesome = mix(absolutePosition,texture(texture2, awesomeCoords),0.5);
    vec4 coloredBox = texture(texture1, TexCoord)*vec4(Color,1.0f);
    vec4 boxAwesome = mix(texture(texture1,TexCoord),texture(texture2,-1*awesomeCoords),(sin(absolutePosition*10)+1)/2);
    vec2 specialCoords = vec2(TexCoord.x*cos(time*10),TexCoord.y+sin(time*1000)/10);
    vec4 kappaCray = texture(texture3,-1*specialCoords*3).xxxx; 
    color = mix(boxAwesome,kappaCray,(cos(absolutePosition*10)+1)/2);
}
