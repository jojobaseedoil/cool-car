#version 430
layout(location = 0) in vec3 Position;
layout(location = 1) uniform vec3 Color;
layout(location = 2) uniform mat4 Projection;
layout(location = 3) uniform mat4 Model; 
layout(location = 4) uniform mat4 View;
out vec4 vs_Color;
void main()
{
    gl_Position = Projection*View*Model*vec4(Position, 1.0);
    vs_Color = vec4(Color.x,Color.y, Color.z, 1.0);
}