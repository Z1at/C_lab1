cmake_minimum_required(VERSION 3.23)
project(untitled C)

set(CMAKE_C_STANDARD 17)

add_executable(untitled Solution/src/main.c Solution/src/image/image.c Solution/src/inputOutput/fromToBmp.c Solution/src/openClose/openFile.c Solution/src/openClose/closeFile.c Solution/src/rotation/rotate.c)
