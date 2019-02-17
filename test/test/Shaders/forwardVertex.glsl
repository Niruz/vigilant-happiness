#version 330 core
  
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in float tid;
layout (location = 3) in vec4 color;
layout (location = 4) in float invertColor;
out DATA
{
	vec4 pos;
	vec4 col;
	float tid;
	vec2 texCoords;
	float invert;
} vs_out;


uniform mat4 projectionMatrix;
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 modelMatrix = mat4(1.0);



void main()
{

   gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position,1);
   vs_out.pos = modelMatrix * vec4(position,1);
   vs_out.col = color;
   vs_out.texCoords = texCoords;
   vs_out.tid = tid;
   vs_out.invert = invertColor;
}