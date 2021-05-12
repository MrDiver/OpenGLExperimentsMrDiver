#version 330 core

in vec4 relativePosition;
in vec4 absolutePosition;
in vec3 Color;
in vec2 TexCoord;
out vec4 color;
uniform vec3 colorChange;
uniform sampler2D ourTexture;
void main(){
    color = texture(ourTexture, TexCoord)*vec4(Color,1.0f)+absolutePosition;
}
