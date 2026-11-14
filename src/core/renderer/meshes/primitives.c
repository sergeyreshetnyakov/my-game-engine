#include "primitives.h"
#include "../renderer.h"
#include <assert.h>
#include <util/sokol_shape.h>

#pragma pack(push, 1)
typedef struct {
    float position[3];
    int8_t normal[4];
    uint16_t uv[2];
} packed_sshape_vertex_t;
#pragma pack(pop)

static renderer_vertex* convert_sshape_vertices(const packed_sshape_vertex_t *raw_data, size_t raw_size) {
    assert(raw_size % sizeof(packed_sshape_vertex_t) == 0);
    uint32_t vertex_count = raw_size / sizeof(packed_sshape_vertex_t);
    const packed_sshape_vertex_t *packed = (const packed_sshape_vertex_t *)raw_data;

    renderer_vertex *vertices = malloc(vertex_count * sizeof(renderer_vertex));
    assert(vertices);

    for (uint32_t i = 0; i < vertex_count; i++) {
        vertices[i] = (renderer_vertex){
            .position = { packed[i].position[0], packed[i].position[1], packed[i].position[2] },
            .normal   = { packed[i].normal[0] / 127.0f, packed[i].normal[1] / 127.0f, packed[i].normal[2] / 127.0f },
            .texcoord = { packed[i].uv[0] / 65535.0f, packed[i].uv[1] / 65535.0f }
        };
    }

    return vertices;
}


renderer_mesh_id meshes_make_plane(renderer *r, meshes_plane_desc *desc) {
    size_t vertex_size = sshape_vertex_size(&RENDERER_PRIMITIVE_VERTEX_COMPONENTS);
    sshape_sizes_t buffers_sizes = sshape_plane_sizes(desc->tiles, vertex_size);
    packed_sshape_vertex_t *sshape_vertices = malloc(buffers_sizes.vertices.size);
    renderer_index_t *indices = malloc(buffers_sizes.indices.size);
    assert(sshape_vertices);
    assert(indices);

    sshape_state_t state = {
        .vertices.buffer = { .ptr = sshape_vertices, .size = buffers_sizes.vertices.size },
        .indices.buffer =  { .ptr = indices,  .size = buffers_sizes.indices.size },
        .disable = {
            .texcoords = !RENDERER_PRIMITIVE_VERTEX_COMPONENTS.texcoords,
            .normals = !RENDERER_PRIMITIVE_VERTEX_COMPONENTS.normals,
            .colors = !RENDERER_PRIMITIVE_VERTEX_COMPONENTS.colors
        }
    };
    sshape_build_plane(&state, &(sshape_plane_t){
        .width = desc->width,
        .depth = desc->depth,
        .tiles = desc->tiles
    });

    assert(state.valid);

    renderer_vertex *vertices = convert_sshape_vertices(sshape_vertices, buffers_sizes.vertices.size);
    assert(vertices);
    free(sshape_vertices);

    renderer_mesh_id id = renderer_make_mesh(r, &(renderer_mesh_desc){
        .vertices = vertices,
        .indices = indices,
        .vertices_size = sizeof(renderer_vertex) * buffers_sizes.vertices.num,
        .index_count = buffers_sizes.indices.num
    });

    free(vertices);
    free(indices);

    return id;
}

renderer_mesh_id meshes_make_box(renderer *r, meshes_box_desc *desc) {
    size_t vertex_size = sshape_vertex_size(&RENDERER_PRIMITIVE_VERTEX_COMPONENTS);
    sshape_sizes_t buffers_sizes = sshape_box_sizes(desc->tiles, vertex_size);
    packed_sshape_vertex_t *sshape_vertices = malloc(buffers_sizes.vertices.size);
    renderer_index_t *indices = malloc(buffers_sizes.indices.size);
    assert(sshape_vertices);
    assert(indices);

    sshape_state_t state = {
        .vertices.buffer = { .ptr = sshape_vertices, .size = buffers_sizes.vertices.size },
        .indices.buffer = { .ptr = indices, .size = buffers_sizes.indices.size },
        .disable = {
            .texcoords = !RENDERER_PRIMITIVE_VERTEX_COMPONENTS.texcoords,
            .normals = !RENDERER_PRIMITIVE_VERTEX_COMPONENTS.normals,
            .colors = !RENDERER_PRIMITIVE_VERTEX_COMPONENTS.colors
        }
    };
    sshape_build_box(&state, &(sshape_box_t){
        .width = desc->width,
        .height = desc->height,
        .depth = desc->depth,
        .tiles = desc->tiles
    });

    assert(state.valid);

    renderer_vertex *vertices = convert_sshape_vertices(sshape_vertices, buffers_sizes.vertices.size);
    assert(vertices);
    free(sshape_vertices);
    
    renderer_mesh_id id = renderer_make_mesh(r, &(renderer_mesh_desc){
        .vertices = vertices,
        .indices = indices,
        .vertices_size = sizeof(renderer_vertex) * buffers_sizes.vertices.num,
        .index_count = buffers_sizes.indices.num
    });

    free(vertices);
    free(indices);

    return id;
}

renderer_mesh_id meshes_make_sphere(renderer *r, meshes_sphere_desc *desc) {
    size_t vertex_size = sshape_vertex_size(&RENDERER_PRIMITIVE_VERTEX_COMPONENTS);
    sshape_sizes_t buffers_sizes = sshape_sphere_sizes(desc->slices, desc->stacks, vertex_size);
    packed_sshape_vertex_t *sshape_vertices = malloc(buffers_sizes.vertices.size);
    renderer_index_t *indices = malloc(buffers_sizes.indices.size);
    assert(sshape_vertices);
    assert(indices);

    sshape_state_t state = {
        .vertices.buffer = { .ptr = sshape_vertices, .size = buffers_sizes.vertices.size },
        .indices.buffer = { .ptr = indices, .size = buffers_sizes.indices.size },
        .disable = {
            .texcoords = !RENDERER_PRIMITIVE_VERTEX_COMPONENTS.texcoords,
            .normals = !RENDERER_PRIMITIVE_VERTEX_COMPONENTS.normals,
            .colors = !RENDERER_PRIMITIVE_VERTEX_COMPONENTS.colors
        }
    };
    sshape_build_sphere(&state, &(sshape_sphere_t){
        .radius = desc->radius,
        .slices = desc->slices,
        .stacks = desc->stacks
    });

    assert(state.valid);

    renderer_vertex *vertices = convert_sshape_vertices(sshape_vertices, buffers_sizes.vertices.size);
    assert(vertices);
    free(sshape_vertices);
    
    renderer_mesh_id id = renderer_make_mesh(r, &(renderer_mesh_desc){
        .vertices = vertices,
        .indices = indices,
        .vertices_size = sizeof(renderer_vertex) * buffers_sizes.vertices.num,
        .index_count = buffers_sizes.indices.num
    });

    free(vertices);
    free(indices);

    return id;
}

renderer_mesh_id meshes_make_cylinder(renderer *r, meshes_cylinder_desc *desc) {
    size_t vertex_size = sshape_vertex_size(&RENDERER_PRIMITIVE_VERTEX_COMPONENTS);
    sshape_sizes_t buffers_sizes = sshape_cylinder_sizes(desc->slices, desc->stacks, vertex_size);
    packed_sshape_vertex_t *sshape_vertices = malloc(buffers_sizes.vertices.size);
    renderer_index_t *indices = malloc(buffers_sizes.indices.size);
    assert(sshape_vertices);
    assert(indices);

    sshape_state_t state = {
        .vertices.buffer = { .ptr = sshape_vertices, .size = buffers_sizes.vertices.size },
        .indices.buffer = { .ptr = indices, .size = buffers_sizes.indices.size },
        .disable = {
            .texcoords = !RENDERER_PRIMITIVE_VERTEX_COMPONENTS.texcoords,
            .normals = !RENDERER_PRIMITIVE_VERTEX_COMPONENTS.normals,
            .colors = !RENDERER_PRIMITIVE_VERTEX_COMPONENTS.colors
        }
    };
    sshape_build_cylinder(&state, &(sshape_cylinder_t){
        .radius = desc->radius,
        .height = desc->height,
        .slices = desc->slices,
        .stacks = desc->stacks
    });

    assert(state.valid);

    renderer_vertex *vertices = convert_sshape_vertices(sshape_vertices, buffers_sizes.vertices.size);
    assert(vertices);
    free(sshape_vertices);

    renderer_mesh_id id = renderer_make_mesh(r, &(renderer_mesh_desc){
        .vertices = vertices,
        .indices = indices,
        .vertices_size = sizeof(renderer_vertex) * buffers_sizes.vertices.num,
        .index_count = buffers_sizes.indices.num
    });

    free(vertices);
    free(indices);

    return id;
}

renderer_mesh_id meshes_make_torus(renderer *r, meshes_torus_desc *desc) {
    size_t vertex_size = sshape_vertex_size(&RENDERER_PRIMITIVE_VERTEX_COMPONENTS);
    sshape_sizes_t buffers_sizes = sshape_torus_sizes(desc->sides, desc->rings, vertex_size);
    packed_sshape_vertex_t *sshape_vertices = malloc(buffers_sizes.vertices.size);
    renderer_index_t *indices = malloc(buffers_sizes.indices.size);
    assert(sshape_vertices);
    assert(indices);

    sshape_state_t state = {
        .vertices.buffer = { .ptr = sshape_vertices, .size = buffers_sizes.vertices.size },
        .indices.buffer = { .ptr = indices, .size = buffers_sizes.indices.size },
        .disable = {
            .texcoords = !RENDERER_PRIMITIVE_VERTEX_COMPONENTS.texcoords,
            .normals = !RENDERER_PRIMITIVE_VERTEX_COMPONENTS.normals,
            .colors = !RENDERER_PRIMITIVE_VERTEX_COMPONENTS.colors
        }
    };
    sshape_build_torus(&state, &(sshape_torus_t){
        .radius = desc->radius,
        .ring_radius = desc->ring_radius,
        .sides = desc->sides,
        .rings = desc->rings,
    });

    assert(state.valid);

    renderer_vertex *vertices = convert_sshape_vertices(sshape_vertices, buffers_sizes.vertices.size);
    assert(vertices);
    free(sshape_vertices);

    renderer_mesh_id id = renderer_make_mesh(r, &(renderer_mesh_desc){
        .vertices = vertices,
        .indices = indices,
        .vertices_size = sizeof(renderer_vertex) * buffers_sizes.vertices.num,
        .index_count = buffers_sizes.indices.num
    });

    free(vertices);
    free(indices);

    return id;
}
