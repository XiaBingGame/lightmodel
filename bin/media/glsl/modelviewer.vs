#version 430 core
layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;

uniform mat4 mv_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;
uniform mat4 mvproj_matrix;
uniform vec3 light_position;

out VS_OUT
{
	vec3 view_dir;
	vec3 light_dir;
	vec3 normal;
} vs_out;

void main(void)
{
	gl_Position = mvproj_matrix*position;
	vec4 p = model_matrix * position;
	vec3 light_dir = light_position - p.xyz;
	vs_out.light_dir = (view_matrix * vec4(light_dir, 0.0)).xyz;
	vs_out.normal = normalize(mat3(mv_matrix)*normal);
	vs_out.view_dir = -normalize((mv_matrix*position).xyz);
}
