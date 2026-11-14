#include "files.h"
#include <stb_image.h>
#include <stdio.h>

int files_load_image(files_load_image_desc *desc) {
    if(desc->flip) stbi_set_flip_vertically_on_load(true);
    
    unsigned char *data = stbi_load(desc->path, &desc->width, &desc->height, &desc->channels, desc->desired_channels);
    if (!data) {
        sprintf(desc->error, "Failed to load image %s. Error: %s\n", desc->path, stbi_failure_reason());
        return -1;
    }
    desc->data = data;
    stbi_image_free(data);
    
    return 0;
}
