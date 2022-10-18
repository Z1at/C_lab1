#include <stdio.h>
#include <stdint.h>

#include "image/image.h"
#include "inputOutput/fromToBmp.h"
#include "openClose/closeFile.h"
#include "openClose/openFile.h"
#include "rotation/rotate.h"

int main(){
    FILE *file;
    if (openFile("C:\\Users\\Zlat\\Desktop\\rotationOfPicture\\input\\input.bmp", &file, "rb") != OPEN_OK) {
        return -2;
    }

    struct image img = {0};

    if (fromBmp(file, &img) != READ_OK) {
        perror("error: bmp reader failed");
        return -3;
    }

    struct image res = rotate(img);
    FILE *res_file = NULL;

    if (openFile("C:\\Users\\Zlat\\Desktop\\rotationOfPicture\\output\\output.bmp", &res_file, "wb") != OPEN_OK) {
        imageDestroyer(&res);
        return -2;
    }

    if (toBmp(res_file, &res) != WRITE_OK) {
        perror("error: bmp writer failed");
        imageDestroyer(&res);
        closeFile(res_file);
        return -5;
    }


    if (closeFile(file) != CLOSE_OK) {
        perror("error: close file failed");
        imageDestroyer(&img);
        return -4;
    }
    if (closeFile(res_file) != CLOSE_OK) {
        perror("error: close file failed");
        imageDestroyer(&img);
        return -6;
    }
    imageDestroyer(&img);
    imageDestroyer(&res);

    return 0;
}