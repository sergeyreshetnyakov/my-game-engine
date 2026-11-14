#pragma once
#include "../renderer_types.h"

typedef struct {
    float width;
    float depth;
    uint16_t tiles;
} meshes_plane_desc;

typedef struct {
    float width;
    float height;
    float depth;
    uint16_t tiles;
} meshes_box_desc;

typedef struct {
    float radius;
    uint16_t slices;
    uint16_t stacks;
} meshes_sphere_desc;

typedef struct {
    float radius;
    float height;
    uint16_t slices; 
    uint16_t stacks;
} meshes_cylinder_desc;

typedef struct {
    float radius;
    float ring_radius;
    uint16_t sides;
    uint16_t rings;
} meshes_torus_desc;

renderer_mesh_id meshes_make_plane(renderer *r, meshes_plane_desc *desc);
renderer_mesh_id meshes_make_box(renderer *r, meshes_box_desc *desc);
renderer_mesh_id meshes_make_sphere(renderer *r, meshes_sphere_desc *desc);
renderer_mesh_id meshes_make_cylinder(renderer *r, meshes_cylinder_desc *desc);
renderer_mesh_id meshes_make_torus(renderer *r, meshes_torus_desc *desc);
