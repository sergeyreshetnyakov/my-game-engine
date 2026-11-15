#include "../renderer.h"
#include "../da_grow_macro.h"
#include "../files/files.h"

renderer_texture_id renderer_make_texture(renderer *r, const char* path) {
    RENDERER_GROW_ARRAY(r, r->textures, r->texture_count, r->texture_capacity);

    renderer_load_image_desc raw_image = { 0 };

    raw_image.path = path;
    raw_image.desired_channels = 4;
    raw_image.error = malloc(256); 

    if (renderer_load_image(&raw_image)) {
        r->log_func(&(renderer_log_func_desc){
            .tag = "load texture",
            .level = LOG_WARN,
            .message = raw_image.error,
            .line_nr = __LINE__,
            .filename = __FILE__
        });
        free(raw_image.error);

        return r->fallback_texture;
    }
    free(raw_image.error);

    sg_image img = sg_make_image(&(sg_image_desc){
        .width = raw_image.width,
        .height = raw_image.height,
        .pixel_format = SG_PIXELFORMAT_RGBA8,
        .num_mipmaps = r->mip_levels,
        .data = {
            .ptr = raw_image.data,
            .size = raw_image.width * raw_image.height * 4,
        }
    });

    renderer_free_image_data(raw_image.data);

    renderer_texture texture = {
        .image = img,
    };
    
    renderer_texture_id id = r->texture_count;
    r->textures[r->texture_count++] = texture;

    return id;
}

renderer_texture_id renderer_make_white_texture(renderer *r) {
    static const uint8_t white[4] = { 255, 255, 255, 255 };
    
    sg_image white_image = sg_make_image(&(sg_image_desc){
        .width = 1,
        .height = 1,
        .pixel_format = SG_PIXELFORMAT_RGBA8,
        .data = {
            .ptr = &white,
            .size = sizeof(white),
        }
    });

    renderer_texture texture = {
        .image = white_image,
    };

    RENDERER_GROW_ARRAY(r, r->textures, r->texture_count, r->texture_capacity);
    renderer_texture_id id = r->texture_count;
    r->textures[r->texture_count++] = texture;
}

renderer_texture_id renderer_make_chess_texture(renderer *r) {
    const int size = 64;
    const int tile_size = 8;
    unsigned char *data = malloc(size * size * 4);

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            int idx = (y * size + x) * 4;
            int c = ((x / tile_size) + (y / tile_size)) % 2;
            if (c) {
                data[idx] = 255;
                data[idx + 1] = 0;
                data[idx + 2] = 255;
            } else {
                data[idx] = 0;
                data[idx + 1] = 0;
                data[idx + 2] = 0;
            }
            data[idx + 3] = 255;
        }
    }

    sg_image img = sg_make_image(&(sg_image_desc){
        .width = size,
        .height = size,
        .pixel_format = SG_PIXELFORMAT_RGBA8,
        .data = {
            .ptr = data,
            .size = size * size * 4
        }
    });

    renderer_texture texture = {
        .image = img,
    };

    RENDERER_GROW_ARRAY(r, r->textures, r->texture_count, r->texture_capacity);
    renderer_texture_id id = r->texture_count;
    r->textures[r->texture_count++] = texture;
    return id;
}