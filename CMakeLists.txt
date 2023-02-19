cmake_minimum_required(VERSION 3.24)
project(clion_playground C)

set(CMAKE_C_STANDARD 11)

add_executable(clion_playground main.c)

include(./cmake/FileEmbed.cmake)
FileEmbedSetup()
FileEmbedAdd(${CMAKE_SOURCE_DIR}/HelloWorld.class)
FileEmbedAdd(${CMAKE_SOURCE_DIR}/Greeter.class)

target_link_libraries(clion_playground file_embed)

