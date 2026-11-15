#pragma once
#include <sokol_gfx.h>
#include <HandmadeMath.h>
#include "../renderer_types.h"

typedef struct {
    sg_view diffuse;
    HMM_Vec4 tint;
} renderer_material;

typedef struct {
    renderer_texture_id diffuse;
    HMM_Vec4 tint;
} renderer_material_desc;

renderer_material_id renderer_make_material(renderer *r, renderer_material_desc *desc);

renderer_material_id renderer_make_color_material(renderer *r, HMM_Vec4 color);
