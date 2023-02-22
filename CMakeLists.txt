cmake_minimum_required(VERSION 3.24)
project(toy_classloader_in_c
        VERSION 1.0
        DESCRIPTION "Playing around with loading bytecode classes"
        LANGUAGES C)

set(CMAKE_C_STANDARD 11)

add_executable(toy_classloader_in_c main.c)

include(EmbedJarContent.cmake)
SetupEmbed()
EmbedManifestFile("jar/META-INF/MANIFEST.MF")
EmbedClassFiles("jar/*.class")

add_library(bifit
        bifit/bifit.h
        bifit/bifit.c)
target_include_directories(bifit PUBLIC bifit)

target_link_libraries(bifit class_files)
target_link_libraries(toy_classloader_in_c bifit)
