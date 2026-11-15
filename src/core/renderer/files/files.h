typedef struct {
    const char *path;
    unsigned char *data;
    int width;
    int height;
    int channels;
    int desired_channels;
    bool flip;
    char *error;
} renderer_load_image_desc;

int renderer_load_image(renderer_load_image_desc *desc);