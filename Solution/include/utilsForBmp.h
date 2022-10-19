//
// Created by Zlat on 10/18/2022.
//

#ifndef UNTITLED_UTILSFORBMP_H
#define UNTITLED_UTILSFORBMP_H

#include "../inputOutput/fromToBmp.h"
size_t size_of_padding(const size_t width);
bool head_read(FILE* file, struct bmp_header* header);
size_t size_of_image(const struct image* image);
size_t size_of_file(const struct image* image);
struct bmp_header create_header(const struct image* image);

#endif //UNTITLED_UTILSFORBMP_H
