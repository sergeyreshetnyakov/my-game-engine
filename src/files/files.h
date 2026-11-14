typedef struct {
    const char *path;
    unsigned char *data;
    int width;
    int height;
    int channels;
    int desired_channels;
    bool flip;
    char *error;
} files_load_image_desc;

int files_load_image(files_load_image_desc *desc);