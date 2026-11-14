#pragma once 
#include <HandmadeMath.h>
#include "../renderer_types.h"

typedef struct {
    renderer_mesh_id mesh_id;
    renderer_material_id material_id;
    HMM_Mat4 transformation;
    bool is_visible;
} renderer_instance;

renderer_instance_id renderer_make_instance(renderer *r, renderer_mesh_id mesh_id, HMM_Mat4 transformation);

void renderer_set_instance_visibility(renderer *r, renderer_instance_id instance_id, bool is_visible);