cmake_minimum_required(VERSION 3.24)
project(clion_playground C)

set(CMAKE_C_STANDARD 11)

add_executable(clion_playground main.c)

include(./cmake/EmbedJarContent.cmake)
SetupClassFileStore()
file(GLOB_RECURSE files "jar/*.class")

foreach(file ${files})
    EmbedClassFile(${file})
endforeach()

target_link_libraries(clion_playground classes)

