#ifndef UNTITLED_CLOSEFILE_H
#define UNTITLED_CLOSEFILE_H

#include <stdio.h>
#include <stdbool.h>
enum closeStatus{
    CLOSE_OK,
    CLOSE_ERROR
};

enum closeStatus closeFile(FILE* file);
#endif //UNTITLED_CLOSEFILE_H
