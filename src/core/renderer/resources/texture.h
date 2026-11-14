#pragma once
#include <sokol_gfx.h>
#include "../renderer_types.h"

typedef struct {
    sg_image image;
} renderer_texture;

renderer_texture_id renderer_make_texture(renderer *r, const char* path);
renderer_texture_id renderer_make_chess_texture(renderer *r);