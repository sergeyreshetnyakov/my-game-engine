#include <HandmadeMath.h>

#include <sokol_app.h>
#include <sokol_gfx.h>
#include <sokol_glue.h>
#include <sokol_log.h>

#include "core/renderer/renderer.h"
#include "core/renderer/meshes/primitives.h"

renderer *r = NULL;

void log_func(renderer_log_func_desc *desc) {
    slog_func(desc->tag, desc->level, 0, desc->message, desc->line_nr, desc->filename, NULL);
}

void init() {
    sg_setup(&(sg_desc){ .environment = sglue_environment(), .logger.func = slog_func });
    r = make_renderer(&(renderer_desc){
        .camera = (renderer_camera){
            .aspect_ratio = (float)sapp_width() / (float)sapp_height(),
            .position = (HMM_Vec3){ 0.0, 0.0, 10.0 },
            .fov = 75.0f,
            .near_distance = 0.1f,
            .far_distance = 100.0f
        },
        .texture_filter = RENDERER_FILTER_LINEAR,
        .mipmap_filter = RENDERER_FILTER_LINEAR,
        .mip_levels = 4,
        .log_func = log_func,
    });
    
    renderer_mesh_id box = meshes_make_box(r, &(meshes_box_desc){
        .depth = 1.0f,
        .height = 1.0f,
        .width = 1.0f,
        .tiles = 1
    });

    HMM_Mat4 transform = HMM_Translate((HMM_Vec3){0.0f, 0.0f, 3.0f});
    HMM_Mat4 transform2 = HMM_Translate((HMM_Vec3){0.0f, 0.0f, -3.0f});
    HMM_Mat4 transform3 = HMM_Translate((HMM_Vec3){3.0f, 0.0f, 0.0f});
    HMM_Mat4 transform4 = HMM_Translate((HMM_Vec3){-3.0f, 0.0f, 0.0f});

    renderer_make_instance(r, box, transform);
    renderer_make_instance(r, box, transform2);
    renderer_make_instance(r, box, transform3);
    renderer_make_instance(r, box, transform4);
}

void frame() {
    renderer_draw_frame(r);
}

void cleanup() {
    renderer_free_resources(r);
    renderer_destroy(r);
    sg_shutdown();
}

sapp_desc sokol_main(int argc, char *argv[]) {
    (void)argc; (void)argv;
    return (sapp_desc){
        .init_cb = init,
        .frame_cb = frame,
        .cleanup_cb = cleanup,
        // .fullscreen = true,
        .width = 1280,
        .height = 960,
        .icon.sokol_default = true,
        .logger.func = slog_func
    };
}