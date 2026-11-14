#pragma once
#include <stdint.h>
#include <sokol_gfx.h>
#include <util/sokol_shape.h>

typedef struct renderer renderer;

typedef uint32_t renderer_instance_id;
typedef uint32_t renderer_mesh_id;
typedef uint32_t renderer_texture_id;
typedef uint32_t renderer_material_id;

typedef enum { 
    RENDERER_FILTER_LINEAR = SG_FILTER_LINEAR,
    RENDERER_FILTER_NEAREST = SG_FILTER_NEAREST
} renderer_texture_filter;
typedef uint8_t renderer_mip_levels_t;

#define RENDERER_VERTEX_POSITION_FORMAT SG_VERTEXFORMAT_FLOAT3
#define RENDERER_VERTEX_NORMAL_FORMAT SG_VERTEXFORMAT_FLOAT3
#define RENDERER_VERTEX_TEXCOORD_FORMAT SG_VERTEXFORMAT_FLOAT2
#define RENDERER_INDEX_TYPE SG_INDEXTYPE_UINT16

typedef struct {
    float position[3];
    float normal[3];
    float texcoord[2];
} renderer_vertex;

typedef uint32_t renderer_vertices_size_t;

#define RENDERER_PRIMITIVE_VERTEX_COMPONENTS (sshape_optional_components_t){ \
    .texcoords = true, \
    .normals = true, \
    .colors = false, \
}

typedef uint16_t renderer_index_t;
typedef uint16_t renderer_index_count_t;


typedef struct {
    const char *path;
    unsigned char* data;
    int width;
    int height;
    int channels;
    int desired_channels;
    bool flip;
    char *error;
} renderer_load_image_func_desc;

typedef int(*renderer_load_image_func_t)(renderer_load_image_func_desc*);

typedef enum { LOG_PANIC, LOG_ERROR, LOG_WARN, LOG_INFO } renderer_log_level;

typedef struct {
    const char *tag;
    renderer_log_level level;
    const char *message;
    uint32_t line_nr;
    const char *filename;
} renderer_log_func_desc;

typedef void(*renderer_log_func_t)(renderer_log_func_desc *desc);