#ifndef UNTITLED_OPENFILE_H
#define UNTITLED_OPENFILE_H

#include <stdbool.h>
#include <stdio.h>
enum openStatus{
    OPEN_ERROR,
    OPEN_OK
};

enum openStatus openFile(const char* fileName, FILE** file, const char* type);
#endif //UNTITLED_OPENFILE_H
