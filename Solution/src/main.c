#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "image/image.h"
#include "inputOutput/fromToBmp.h"
#include "openClose/closeFile.h"
#include "openClose/openFile.h"
#include "rotation/rotate.h"

int main(){
    FILE *file;
    if (!openFile("C:\\Users\\Zlat\\Desktop\\rotationOfPicture\\input\\input7.bmp", &file, "rb")) {
        return -2;
    }

    struct image img = {0};

    if (!fromBmp(file, &img)) {
        perror("error: bmp reader failed");
        return -3;
    }

    struct image res = rotate(img);
    FILE *res_file = NULL;

    if (!openFile("C:\\Users\\Zlat\\Desktop\\rotationOfPicture\\output\\output7.bmp", &res_file, "wb")) {
        imageDestroyer(&res);
        return -2;
    }

    if (!toBmp(res_file, &res)) {
        perror("error: bmp writer failed");
        imageDestroyer(&res);
        closeFile(res_file);
        return -5;
    }


    if (!closeFile(file)) {
        perror("error: close file failed");
        imageDestroyer(&img);
        return -4;
    }
    imageDestroyer(&img);
    imageDestroyer(&res);
    return closeFile(res_file);
}