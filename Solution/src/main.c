#include <stdio.h>

#include "image/image.h"
#include "inputOutput/fromToBmp.h"
#include "openClose/closeFile.h"
#include "openClose/openFile.h"
#include "rotation/rotate.h"

int main(int cntArg, char* args[]){
    if(cntArg != 3){
        perror("incorrectly passed arguments");
        return -1;
    }

    FILE *file;
    if (openFile(args[1], &file, "rb") != OPEN_OK) {
        perror("couldn't open the file");
        return -2;
    }

    struct image img = {0};

    if (fromBmp(file, &img) != READ_OK) {
        perror("couldn't convert from bmp");
        return -3;
    }

    struct image res = rotate(img);
    FILE *res_file;

    if (openFile(args[2], &res_file, "wb") != OPEN_OK) {
        perror("couldn't open the file");
        imageDestroyer(&res);
        return -2;
    }

    if (toBmp(res_file, &res) != WRITE_OK) {
        perror("couldn't convert to bmp");
        imageDestroyer(&res);
        closeFile(res_file);
        return -5;
    }


    if (closeFile(file) != CLOSE_OK) {
        perror("couldn't close the file");
        imageDestroyer(&img);
        return -4;
    }
    if (closeFile(res_file) != CLOSE_OK) {
        perror("couldn't close the file");
        imageDestroyer(&img);
        return -6;
    }
    imageDestroyer(&img);
    imageDestroyer(&res);

    return 0;
}