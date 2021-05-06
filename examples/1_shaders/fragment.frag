#version 330 core

in vec4 position;
out vec4 color;

uniform vec3 colorChange;
void main(){
    color = vec4(position);
}
