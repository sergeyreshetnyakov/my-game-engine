#pragma once
#include <sokol_gfx.h>
#include "../renderer_types.h"

typedef struct {
    sg_view diffuse;
} renderer_material;

typedef struct {
    renderer_texture_id diffuse;
} renderer_material_desc;

renderer_material_id renderer_make_material(renderer *r, renderer_material_desc *desc);
