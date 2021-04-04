#shader-type vertex
#version 430 core

layout (location = 0) in vec3 position;

out vec3 SampleDirection;

uniform mat4 view;
uniform mat4 projection;

void main() 
{
	SampleDirection = position; 	
	vec4 pos = projection * mat4(mat3(view)) * vec4(position, 1.0f);
	gl_Position = pos.xyww; // Put w in depth position so when perspective division occurs w/w = 1 (which is the greatest depth value) so it is rendered behind everything
}




#shader-type fragment
#version 430 core

out vec4 FragColour;

in vec3 SampleDirection;

uniform samplerCube skyboxCubemap;

void main() {
	FragColour = texture(skyboxCubemap, SampleDirection);
}
