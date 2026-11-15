#include "camera.h"
#include "../renderer.h"

HMM_Mat4 renderer_compute_mvp(renderer *r, HMM_Mat4 model) {
    HMM_Mat4 projection = HMM_Perspective_RH_NO(HMM_ToRad(r->camera.fov), *r->camera.aspect_ratio, r->camera.near_distance, r->camera.far_distance);
    HMM_Mat4 view = HMM_LookAt_RH(r->camera.position, (HMM_Vec3){ 0.0f, 0.0f, 0.0f }, (HMM_Vec3){0.0f, 1.0f, 0.0f});
    return HMM_MulM4(HMM_MulM4(projection, view), model);
}