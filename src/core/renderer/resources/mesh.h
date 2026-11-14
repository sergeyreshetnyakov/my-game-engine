#pragma once
#include <sokol_gfx.h>
#include "../renderer_types.h"

typedef struct {
    sg_buffer vertex_buffer;
    sg_buffer index_buffer;
    renderer_index_count_t  index_count;
} renderer_mesh;

typedef struct {
    const renderer_vertex *vertices;
    const renderer_index_t *indices;
    renderer_vertices_size_t vertices_size;
    renderer_index_count_t index_count;
} renderer_mesh_desc;

renderer_mesh_id renderer_make_mesh(renderer *r, renderer_mesh_desc *desc);