#shader vertex
#version 430 core

layout(location = 0) in vec4 position;

void main(){
    gl_Position = position;
}

#shader fragment
#version 430 core

layout(location = 0) out vec4 color;
layout (std430, binding=3) buffer shader_data
{
    double field[];
};

uniform int u_xScale;
uniform int u_yScale;
uniform double u_maxMag;
//uniform float u_Field[10*10];

float random (vec2 st) {
    return fract(sin(dot(st.xy,
    vec2(12.9898,78.233)))*
    43758.5453123);
}
//
vec4 magnitudeToColor(in double m){
    double red, blue, green;
    double t = u_maxMag/3.0;
    double r = m/u_maxMag;
    vec4 nuevoColores = vec4(0,0,0,1);
    if(m < t){
        nuevoColores.r = float(r);
    } else {
        nuevoColores.r = 1.0;
        nuevoColores.g = float(r/2);
        nuevoColores.b = float(r);
    }
    return nuevoColores;
}

vec4 testing(in double m){
    float r = float(m/u_maxMag);
    vec4 nuevoColores = {r,0,0,0};
    return nuevoColores;

}


void main(){

    color = testing(field[(int(floor(gl_FragCoord.y)) * u_xScale) +  int(floor(gl_FragCoord.x))]);
//    color = magnitudeToColor(field[(int(floor(gl_FragCoord.y)) * u_xScale) +  int(floor(gl_FragCoord.x))]);

}
