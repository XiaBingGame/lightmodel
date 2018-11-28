#version 430 core
uniform vec3 mat_diffuse;
uniform vec3 mat_spec;
uniform vec3 light_ambient;
uniform vec3 light_diffuse;
uniform vec3 light_spec;
uniform float light_shiness;

out vec4 color;

in VS_OUT
{
	vec3 view_dir;
	vec3 light_dir;
	vec3 normal;
} fs_in;

vec4 lambert_model()
{
    vec4 c = vec4(0.0);
    float NdotL = max(0.0, dot(normalize(fs_in.light_dir), normalize(fs_in.normal)));
    c.xyz = mat_diffuse * light_ambient + mat_diffuse * light_diffuse * NdotL;
    c.w = 1.0;

    return c;
}

vec4 phong_model()
{
    vec4 c = vec4(0.0);
    vec3 N = normalize(fs_in.normal);
    vec3 V = normalize(fs_in.view_dir);
    vec3 L = normalize(fs_in.light_dir);

    vec3 R = normalize((2.0*dot(N, L))*N - L);
    c.xyz = pow(max(0.0, dot(V, R)), light_shiness) * mat_spec * light_spec;
    c += lambert_model();
    c.w = 1.0;
    return c;
}

vec4 blinn_phong_model()
{
    vec4 c = vec4(0.0);
    vec3 N = normalize(fs_in.normal);
    vec3 V = normalize(fs_in.view_dir);
    vec3 L = normalize(fs_in.light_dir);
    vec3 H = normalize(V+L);

    c.xyz = pow(max(0.0, dot(N, H)), light_shiness) * mat_spec * light_spec;
    c += lambert_model();
    c.w = 1.0;
    return c;
}
                                                                  
void main(void)
{
    // color = lambert_model();
    // color = phong_model();
    color = blinn_phong_model();
}
