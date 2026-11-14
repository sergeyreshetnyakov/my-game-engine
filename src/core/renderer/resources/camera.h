#pragma once
#include <HandmadeMath.h>
#include "../renderer_types.h"

typedef struct {
    float aspect_ratio;
    float fov;
    float near_distance;
    float far_distance;
    HMM_Vec3 position;
} renderer_camera;

HMM_Mat4 renderer_compute_mvp(renderer *r, HMM_Mat4 model);