#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

struct __attribute__ ((packed)) pixel{
    uint8_t b;
    uint8_t g;
    uint8_t r;
};

struct image{
    uint64_t width;
    uint64_t height;
    struct pixel* data;
};

size_t get_index(const size_t x, const size_t y, const size_t width){
    return y * width + x;
}

struct image some_image(uint64_t width, uint64_t height, struct pixel* pixels){
    return (struct image) {.data = pixels, .width = width, .height = height};
}

struct image image_create(const size_t image_width, const size_t image_height){
    struct pixel* pixels = malloc(sizeof(struct pixel) * image_height * image_width);
    return some_image(image_width, image_height, pixels);
}

struct image copy_image(struct image image){
    size_t size_of_image = sizeof(struct pixel) * image.height * image.width;
    struct pixel* pixels = malloc(size_of_image);
    for(size_t i = 0; i < image.height * image.width; i++){
        pixels[i] = image.data[i];
    }
    return some_image(image.width, image.height, pixels);
}

void image_destroy(const struct image* image){
    free(image->data);
}



struct image rotate(const struct image source){
    if(source.data == NULL){
        return some_image(source.width, source.height, NULL);
    }

    struct pixel* pixels = malloc(sizeof(struct pixel) * source.width * source.height);

    for(size_t y = 0; y < source.height; y++){
        for(size_t x = 0; x < source.width; x++){
            pixels[get_index(source.height - y - 1, x, source.height)] = source.data[get_index(x, y, source.width)];
        }
    }

    return some_image(source.height, source.width, pixels);
}



struct __attribute__((packed)) bmp_header {
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t  biHeight;
    uint16_t  biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t  biClrImportant;
};

size_t size_of_padding(const size_t width){
    if(width % 4 == 0) return 0;
    return 4 - ((width * sizeof(struct pixel)) % 4);
}

bool head_read(FILE* file, struct bmp_header* header){
    return fread(header, sizeof(struct bmp_header), 1, file);
}

size_t size_of_image(const struct image* image){
    return (image->width * sizeof(struct pixel) + size_of_padding(image->width)) * image->height;
}

size_t size_of_file(const struct image* image){
    return size_of_image(image) + sizeof(struct bmp_header);
}

struct bmp_header create_header(const struct image* image){
    return (struct bmp_header){
        .bfType = 19778,
        .bfileSize = size_of_file(image),
        .bfReserved = 0,
        .bOffBits = 54,
        .biSize = 40,
        .biWidth = image->width,
        .biHeight = image->height,
        .biPlanes = 1,
        .biBitCount = 24,
        .biCompression = 0,
        .biSizeImage = size_of_image(image),
        .biXPelsPerMeter = 0,
        .biYPelsPerMeter = 0,
        .biClrImportant = 0,
        .biClrUsed = 0
    };
}

bool from_bmp(FILE* in, struct image* image){
    struct bmp_header header = {0};

    if(!head_read(in, &header)){
        image_destroy(image);
        return false;
    }

    *image = image_create(header.biWidth, header.biHeight);
    const size_t padding = size_of_padding(image->width);

    for(size_t i = 0; i < image->height; i++){
        for(size_t j = 0; j < image->width; j++){
            if(!fread(&(image->data[image->width * i + j]), sizeof(struct pixel), 1, in)){
                image_destroy(image);
                return false;
            }
        }
        if(fseek(in, padding, SEEK_CUR)){
            image_destroy(image);
            return false;
        }
    }

    return true;
}

bool to_bmp(FILE* out, const struct image* image){
    struct bmp_header header = create_header(image);
    if(!fwrite(&header, sizeof(struct bmp_header), 1, out)){
        return false;
    }

    if(fseek(out, header.bOffBits, SEEK_SET)){
        return false;
    }

    const uint8_t paddings[3] = {0};
    const size_t padding = size_of_padding(image->width);

    if(image->data == NULL){
        return false;
    }

    for(size_t i = 0; i < image->height; i++){

        if(!fwrite(image->data + i * image->width, image->width * sizeof(struct pixel), 1, out)){
            return false;
        }
        if(padding != 0) {
            if (!fwrite(paddings, padding, 1, out)) {
                return false;
            }
        }
    }

    return true;
}



bool file_open(const char* fileName, FILE** file, const char* mode){
    *file = fopen(fileName, mode);
    if(file == NULL){
        perror("Error: open file failed");
        return false;
    }

    return true;
}

bool file_close(FILE* file){
    if(fclose(file)){
        return false;
    }

    return true;
}



int main(int argc, char *argv[]) {
    if (argc != 3) {
        perror("Incorrect arguments");
        return -1;
    }

    FILE* file;
    if (!file_open("C:\\Users\\Zlat\\CLionProjects\\untitled\\input\\input2.bmp", &file, "rb")) {
        return -2;
    }

    struct image img = {0};

    if (!from_bmp(file, &img)) {
        perror("error: bmp reader failed");
        return -3;
    }
    if (!file_close(file)) {
        perror("error: close file failed");
        image_destroy(&img);
        return -4;
    }

    struct image res = rotate(img);
    image_destroy(&img);
    FILE* res_file;

//    rewind(file);
//    struct bmp_header head;
//    head_read(file, &head);


    if (!file_open("C:\\Users\\Zlat\\CLionProjects\\untitled\\output\\output2.bmp", &res_file, "wb")) {
        image_destroy(&res);
        return -2;
    }

    if (!to_bmp(res_file, &res)) {
        perror("error: bmp writer failed");
        image_destroy(&res);
        file_close(res_file);
        return -5;
    }

    image_destroy(&res);
    return file_close(res_file);
//
}
