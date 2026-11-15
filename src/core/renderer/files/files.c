#include "files.h"
#include <stb_image.h>
#include <stdio.h>

int renderer_load_image(renderer_load_image_desc *desc) {
    if(desc->flip) stbi_set_flip_vertically_on_load(true);

    int w, h, ch;
    unsigned char *data = stbi_load(desc->path, &w, &h, &ch, desc->desired_channels);
    if (!data) {
        snprintf(desc->error, 256,
                 "Failed to load image %s. Error: %s",
                 desc->path, stbi_failure_reason());
        return -1;
    }

    desc->width = w;
    desc->height = h;
    desc->channels = ch;
    desc->data = data;
    
    return 0;
}

    
void renderer_free_image_data(unsigned char *data) {
    stbi_image_free(data);
}