@ctype mat4 HMM_Mat4

@vs vs
layout (binding = 0) uniform vs_params {
    mat4 mvp;
};

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 texcoord;

out vec3 v_normal;
out vec2 v_texcoord;

void main() {
    gl_Position = mvp * vec4(position, 1.0);
    v_normal = normalize(normal.xyz);
    v_texcoord = texcoord;
}
@end

@fs fs
layout (binding = 0) uniform texture2D diffuse_tex;
layout (binding = 0) uniform sampler diffuse_smp;
layout (binding = 1) uniform fs_params {
    vec4 color;
};
in vec3 v_normal;
in vec2 v_texcoord;

out vec4 frag_color;

void main() {
    vec3 light_dir = normalize(vec3(0.5, 1.0, 0.5));
    float diff = max(dot(normalize(v_normal), light_dir), 0.0);

    vec4 diffuse_color = texture(sampler2D(diffuse_tex, diffuse_smp), v_texcoord) * color;
    
    frag_color = vec4(diffuse_color.rgb * (0.2 + 0.8 * diff + (v_texcoord.x * 0)), 1.0);
}
@end

@program default_shader vs fs