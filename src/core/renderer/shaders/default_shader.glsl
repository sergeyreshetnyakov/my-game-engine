@ctype mat4 HMM_Mat4

@vs vs
layout (binding = 0) uniform vs_params {
    mat4 mvp;
    vec4 color;
};

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 texcoord;

out vec3 v_normal;
out vec2 v_texcoord;
out vec4 v_color;

void main() {
    gl_Position = mvp * vec4(position, 1.0);
    v_normal = normalize(normal.xyz);
    v_texcoord = texcoord;
    v_color = color;
}
@end

@fs fs
in vec3 v_normal;
in vec2 v_texcoord;
in vec4 v_color;

out vec4 frag_color;

void main() {
    vec3 light_dir = normalize(vec3(0.5, 1.0, 0.5));
    float diff = max(dot(normalize(v_normal), light_dir), 0.0);
    frag_color = vec4(v_color.rgb * (0.2 + 0.8 * diff + (v_texcoord.x * 0)), 1.0);
}
@end

@program default_shader vs fs