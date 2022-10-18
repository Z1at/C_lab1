#include "openFile.h"

enum openStatus openFile(const char* fileName, FILE** file, const char* type){
    *file = fopen(fileName, type);
    if(*file == NULL){
        return OPEN_ERROR;
    }
    return OPEN_OK;
}
