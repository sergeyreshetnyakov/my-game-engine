#pragma once
#include <sokol_gfx.h>
#include "renderer_types.h"
#include "resources/camera.h"
#include "resources/mesh.h"
#include "resources/texture.h"
#include "resources/material.h"
#include "resources/instance.h"

struct renderer {
    renderer_camera camera;
    
    sg_pipeline pipeline;
    sg_sampler sampler;
    renderer_mip_levels_t mip_levels;

    renderer_log_func_t log_func;
    
    renderer_mesh *meshes;
    renderer_mesh_id mesh_count;
    renderer_mesh_id mesh_capacity;

    renderer_instance *instances;
    renderer_instance_id instance_count;
    renderer_instance_id instance_capacity;

    renderer_texture *textures;
    renderer_texture_id texture_count;
    renderer_texture_id texture_capacity;
    renderer_texture_id white_texture;
    renderer_texture_id fallback_texture;

    renderer_material *materials;
    renderer_material_id material_count;
    renderer_material_id material_capacity;
};

typedef struct {
    renderer_camera camera;
    renderer_texture_filter texture_filter;
    renderer_texture_filter mipmap_filter;
    renderer_mip_levels_t mip_levels;
    renderer_log_func_t log_func;
} renderer_desc;

renderer* make_renderer(renderer_desc *desc);

void renderer_draw_frame(renderer *r);

void renderer_free_resources(renderer *r);

void renderer_destroy(renderer *r);