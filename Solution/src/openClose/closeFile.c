#include "closeFile.h"

bool closeFile(FILE* file){
    if(fclose(file) == EOF){
        return false;
    }
    return true;
}