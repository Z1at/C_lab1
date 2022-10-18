#include "closeFile.h"

enum closeStatus closeFile(FILE* file){
    if(fclose(file) == EOF){
        return CLOSE_ERROR;
    }
    return CLOSE_OK;
}