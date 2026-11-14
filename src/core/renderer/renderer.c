#include "renderer.h"
#include "shaders/default_shader.h"
#include <stdlib.h>
#include <sokol_glue.h>

renderer* make_renderer(renderer_desc *desc) {
    renderer *r = malloc(sizeof(renderer));
    
    sg_pipeline pip = sg_make_pipeline(&(sg_pipeline_desc){
        .index_type = RENDERER_INDEX_TYPE,
        .shader = sg_make_shader(default_shader_shader_desc(sg_query_backend())),
        .depth = { .compare = SG_COMPAREFUNC_LESS_EQUAL, .write_enabled = true },
        .cull_mode = SG_CULLMODE_BACK,
        .layout.attrs = {
            [ATTR_default_shader_position].format = RENDERER_VERTEX_POSITION_FORMAT,
            [ATTR_default_shader_normal].format = RENDERER_VERTEX_NORMAL_FORMAT,
            [ATTR_default_shader_texcoord]. format = RENDERER_VERTEX_TEXCOORD_FORMAT
        }
    });

    sg_sampler smp = sg_make_sampler(&(sg_sampler_desc){
        .mag_filter = desc->texture_filter,
        .min_filter = desc->texture_filter,
        .mipmap_filter = desc->mipmap_filter,
    });

    *r = (renderer){
        .camera = desc->camera,
        .pipeline = pip,
        .sampler = smp,
        .mip_levels = desc->mip_levels,
        .log_func = desc->log_func
    };

    r->fallback_texture = renderer_make_chess_texture(r);

    return r;
}

void renderer_draw_frame(renderer *r) {
    sg_begin_pass(&(sg_pass){
        .swapchain = sglue_swapchain(),
        .action = {
            .colors[0] = { .load_action = SG_LOADACTION_CLEAR, .clear_value = { 0.1f, 0.1f, 0.1f, 1.0f }}
        }
    });
    sg_apply_pipeline(r->pipeline);
    
    renderer_mesh_id current_mesh_id = UINT16_MAX;
    renderer_mesh current_mesh = {0};
    sg_bindings bind = {0};
    
    for (renderer_instance_id i = 0; i < r->instance_count; i++) {
        renderer_instance instance = r->instances[i];

        if(!instance.is_visible) continue;
        
        if(current_mesh_id != instance.mesh_id) {
            current_mesh_id = instance.mesh_id;
            current_mesh = r->meshes[current_mesh_id];
            
            bind.vertex_buffers[0] = current_mesh.vertex_buffer;
            bind.index_buffer = current_mesh.index_buffer;

            sg_apply_bindings(&bind);
        }

        vs_params_t vs_params ={
            .mvp = renderer_compute_mvp(r, instance.transformation),
            .color = { 1.0f, 0.0f, 0.0f, 1.0f }
        };
        sg_apply_uniforms(0, &SG_RANGE(vs_params));

        sg_draw(0, current_mesh.index_count, 1);
    }

    sg_end_pass();
    sg_commit();
}

void renderer_free_resources(renderer *r) {
    for(renderer_mesh_id i = 0; i < r->mesh_count; i++) {
        sg_destroy_buffer(r->meshes[i].vertex_buffer);
        sg_destroy_buffer(r->meshes[i].index_buffer);
    }

    for(renderer_texture_id i = 0; i < r->texture_count; i++) {
        sg_destroy_image(r->textures[i].image);
    }
    
    for(renderer_material_id i = 0; i < r->material_count; i++) {
        sg_destroy_view(r->materials[i].diffuse);
    }
    
    free(r->meshes);
    r->mesh_capacity = 0;
    r->mesh_count = 0;
    
    free(r->instances);
    r->instance_capacity = 0;
    r->instance_count = 0;
    
    free(r->textures);
    r->texture_capacity = 0;
    r->texture_count = 0;

    free(r->materials);
    r->material_capacity = 0;
    r->material_count = 0;
}

void renderer_destroy(renderer *r) {
    sg_destroy_sampler(r->sampler);
    sg_destroy_pipeline(r->pipeline);
    free(r);
}