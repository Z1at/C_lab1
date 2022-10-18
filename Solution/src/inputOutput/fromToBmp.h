#ifndef UNTITLED_FROMTOBMP_H
#define UNTITLED_FROMTOBMP_H

#include <stdio.h>
#include <stdbool.h>
#include "../image/image.h"

bool fromBmp(FILE* out, struct image* image);
bool toBmp(FILE* out, const struct image* image);
#endif //UNTITLED_FROMTOBMP_H
