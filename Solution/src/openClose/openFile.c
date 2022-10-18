#include "openFile.h"

bool openFile(const char* fileName, FILE** file, const char* type){
    *file = fopen(fileName, type);
    if(*file == NULL){
        return false;
    }
    return true;
}
