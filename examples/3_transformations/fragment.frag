#version 330 core

in vec3 Color;
in vec2 TexCoord;
out vec4 color;

uniform sampler2D box;
uniform sampler2D awesome;
uniform sampler2D kappa;
void main(){
    color = mix(texture(box, TexCoord),texture(awesome,TexCoord),0.5f)*vec4(Color,1.0f);
}
