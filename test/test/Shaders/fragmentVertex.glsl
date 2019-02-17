#version 330 core

layout (location = 0) out vec4 color;


in DATA
{
	vec4 pos;
	vec4 col;
	float tid;
	vec2 texCoords;
	float invert;
} fs_in;

uniform vec2 lightPos;
//uniform sampler2D texture2d;
uniform sampler2D textureArray[16];
void main()
{
	float intensity = 50.0f / length(fs_in.pos.xy - lightPos);
	vec4 texColor = fs_in.col;
	if (fs_in.tid > 0.0)
	{
		int tid = int(fs_in.tid - 0.5);
		texColor = fs_in.col *texture(textureArray[tid],fs_in.texCoords);
		if(fs_in.invert == 1.0f)
			texColor = vec4(1.0f - texColor.x, 1.0f - texColor.y, 1.0f - texColor.z, texColor.w); 
		else if(fs_in.invert == 2.0f)
			texColor = vec4(texColor.x,texColor.y,texColor.z, texColor.w == 0 ? 0 : fs_in.col.w);
		texColor = texColor.zyxw;
	}
	//texColor.xyz *= intensity;
	color = texColor;// * intensity;
} 