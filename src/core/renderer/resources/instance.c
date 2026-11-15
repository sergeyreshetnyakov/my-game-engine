#include "instance.h"
#include "../renderer.h"
#include "../da_grow_macro.h"

renderer_instance_id renderer_make_instance(renderer *r, renderer_instance_desc *desc) {
    RENDERER_GROW_ARRAY(r, r->instances, r->instance_count, r->instance_capacity);
    
    renderer_instance instance = {
        .mesh_id = desc->mesh_id,
        .transformation = desc->transformation,
        .is_visible = desc->is_visible
    };
    
    renderer_instance_id id = r->instance_count;
    r->instances[r->instance_count++] = instance;

    return id;
}

void renderer_set_instance_material(renderer *r, renderer_instance_id instance_id, renderer_material_id material_id) {
    r->instances[instance_id].material_id = material_id;
}

void renderer_set_instance_transform(renderer *r, renderer_instance_id instance_id, HMM_Mat4 transformation) {
    r->instances[instance_id].transformation = transformation;
}

void renderer_set_instance_visibility(renderer *r, renderer_instance_id instance_id, bool is_visible) {
    r->instances[instance_id].is_visible = is_visible;
}