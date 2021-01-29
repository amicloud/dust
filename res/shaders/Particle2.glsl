#shader vertex
#version 430 core

layout(location = 0) in vec4 position;

uniform mat4 ortho;

void main(){
    gl_Position = position * ortho;
    gl_PointSize = 2;
}

#shader fragment
#version 430 core

layout(location = 0) out vec4 color;


void main(){

    color = vec4(1, 0, 0, 1);

}
