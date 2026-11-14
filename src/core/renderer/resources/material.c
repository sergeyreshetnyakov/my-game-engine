#include "material.h"
#include "../renderer.h"
#include "../da_grow_macro.h"

renderer_material_id renderer_make_material(renderer *r, renderer_material_desc* desc) {
    RENDERER_GROW_ARRAY(r, r->materials, r->material_count, r->material_capacity);

    renderer_material material = {
        .diffuse = sg_make_view(&(sg_view_desc){
            .texture = r->textures[desc->diffuse].image
        })
    };

    renderer_material_id id = r->material_count;
    r->materials[r->material_count++] = material;
    
    return id;
}