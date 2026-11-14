#include "mesh.h"
#include "../renderer.h"
#include "../da_grow_macro.h"

renderer_mesh_id renderer_make_mesh(renderer *r, renderer_mesh_desc *desc) {
    RENDERER_GROW_ARRAY(r, r->meshes, r->mesh_count, r->mesh_capacity);

    renderer_mesh mesh = {
        .vertex_buffer = sg_make_buffer(&(sg_buffer_desc){
            .data = {
                .ptr = desc->vertices,
                .size = desc->vertices_size
            }
        }),
        .index_buffer = sg_make_buffer(&(sg_buffer_desc){
            .data = {
                .ptr = desc->indices,
                .size = desc->index_count * sizeof(renderer_index_t)
            },
            .usage.index_buffer = true,
        }),
        .index_count = desc->index_count
    };

    renderer_mesh_id id = r->mesh_count;
    r->meshes[r->mesh_count++] = mesh;

    return id;
}