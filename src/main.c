#include <HandmadeMath.h>

#include <sokol_app.h>
#include <sokol_gfx.h>
#include <sokol_glue.h>
#include <sokol_log.h>

#include "core/renderer/renderer.h"
#include "core/renderer/meshes/primitives.h"

renderer *r = NULL;
static float aspect_ratio = 0;

static void log_func(renderer_log_func_desc *desc) {
    slog_func(desc->tag, desc->level, 0, desc->message, desc->line_nr, desc->filename, NULL);
}

static void init() {
    sg_setup(&(sg_desc){ .environment = sglue_environment(), .logger.func = slog_func });
    aspect_ratio = (float)sapp_width() / (float)sapp_height();

    r = make_renderer(&(renderer_desc){
        .camera = (renderer_camera){
            .aspect_ratio = &aspect_ratio,
            .position = (HMM_Vec3){ 0.0, 0.0, 10.0 },
            .fov = 75.0f,
            .near_distance = 0.1f,
            .far_distance = 100.0f
        },
        .texture_filter = RENDERER_FILTER_LINEAR,
        .mipmap_filter = RENDERER_FILTER_LINEAR,
        .mip_levels = 1,
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

    renderer_texture_id crate_texture = renderer_make_texture(r, "textures/wooden_crate.jpg");
    renderer_material_id box_material = renderer_make_material(r, &(renderer_material_desc){
        .diffuse = crate_texture,
        .tint = HMM_V4(0.5f, 0.0f, 0.0f, 1.0f)
    });

    renderer_make_instance(r, &(renderer_instance_desc){
        .mesh_id = box,
        .material_id = box_material,
        .transformation = transform,
        .is_visible = true
    });
    renderer_make_instance(r, &(renderer_instance_desc){
        .mesh_id = box,
        .material_id = box_material,
        .transformation = transform2,
        .is_visible = true
    });
    renderer_make_instance(r, &(renderer_instance_desc){
        .mesh_id = box,
        .material_id = box_material,
        .transformation = transform3,
        .is_visible = true
    });
    renderer_make_instance(r, &(renderer_instance_desc){
        .mesh_id = box,
        .material_id = box_material,
        .transformation = transform4,
        .is_visible = true
    });
}

static void frame() {
    renderer_draw_frame(r);
}

static void cleanup() {
    renderer_free_resources(r);
    renderer_destroy(r);
    sg_shutdown();
}

static void event(const sapp_event* event) {
    switch (event->type) {
        case SAPP_EVENTTYPE_RESIZED:
            aspect_ratio = (float)sapp_width() / (float)sapp_height();
            break;
        default:
            break;
    }
}

sapp_desc sokol_main(int argc, char *argv[]) {
    (void)argc; (void)argv;
    return (sapp_desc){
        .init_cb = init,
        .frame_cb = frame,
        .cleanup_cb = cleanup,
        .event_cb = event,
        // .fullscreen = true,
        .width = 1280,
        .height = 960,
        .icon.sokol_default = true,
        .logger.func = slog_func
    };
}