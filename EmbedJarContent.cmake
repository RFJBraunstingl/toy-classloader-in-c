function(SetupEmbed)
    if (NOT EXISTS ${CMAKE_BINARY_DIR}/classes)
        file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/classes)
    endif ()

    add_library(class_files
            ${CMAKE_BINARY_DIR}/classes/classes_combined.h
            ${CMAKE_BINARY_DIR}/classes/classes_combined.c)
    target_include_directories(class_files PUBLIC ${CMAKE_BINARY_DIR}/classes)

    set(output_h "
#ifndef CLASSES_COMBINED_H
#define CLASSES_COMBINED_H
#include \"stdint.h\"
")
    file(WRITE ${CMAKE_BINARY_DIR}/classes/classes_combined.h
            ${output_h})

    set(output_c "
#include \"classes_combined.h\"
")
    file(WRITE ${CMAKE_BINARY_DIR}/classes/classes_combined.c
            ${output_c})
endfunction()

function(EmbedManifestFile path)

    message("load manifest file ${path}")

    # load manifest file into ${manifest_content}
    file(READ ${path} manifest_content)

    # find the main class entry
    string(REGEX MATCH "Main-Class: .*" main_class_line ${manifest_content})

    # get the identifier
    string(REPLACE "Main-Class: " "" main_class_identifier ${main_class_line})
    string(REGEX REPLACE "\n" "" main_class_identifier "${main_class_identifier}")
    message("found main class identifier: ${main_class_identifier}")

    # make the identifier accessible in C
    set(output_h "
extern char * bifit_main_class_identifier\;
")
    file(APPEND ${CMAKE_BINARY_DIR}/classes/classes_combined.h
            ${output_h})

    set(output_c "
char * bifit_main_class_identifier = \"${main_class_identifier}\"\;
")
    file(APPEND ${CMAKE_BINARY_DIR}/classes/classes_combined.c
            ${output_c})

endfunction()

function(EmbedClassFiles path)


    file(GLOB_RECURSE files ${path})

    set(output_h "
typedef uint8_t * classfile_pointer\;
extern classfile_pointer bifit_embedded_class_files[]\;
unsigned int bifit_embedded_class_files_size\;
#endif // CLASSES_COMBINED_H
")

    file(APPEND ${CMAKE_BINARY_DIR}/classes/classes_combined.h
            ${output_h})

    set(output_c "
classfile_pointer bifit_embedded_class_files[] = {")

    file(APPEND ${CMAKE_BINARY_DIR}/classes/classes_combined.c
            ${output_c})

    set(counter 0)
    foreach (file ${files})
        EmbedClassFile(${file})
        MATH(EXPR counter "${counter}+1")
    endforeach ()

    file(APPEND ${CMAKE_BINARY_DIR}/classes/classes_combined.c
            "\n};\n")
    file(APPEND ${CMAKE_BINARY_DIR}/classes/classes_combined.c
            "unsigned int bifit_embedded_class_files_size = ${counter};")

endfunction()

function(EmbedClassFile file)
    message("embed class file ${file}")
    ClassFileGenerate(${file} var)
    target_sources(class_files PUBLIC ${var})
endfunction()

function(ClassFileGenerate file generated_c)

    get_filename_component(base_filename ${file} NAME)
    set(output_filename "${base_filename}.c")
    string(MAKE_C_IDENTIFIER ${base_filename} c_name)
    file(READ ${file} content HEX)

    string(REGEX MATCHALL "([A-Fa-f0-9][A-Fa-f0-9])" SEPARATED_HEX ${content})

    set(output_c "")

    set(counter 0)
    foreach (hex IN LISTS SEPARATED_HEX)
        string(APPEND output_c "0x${hex},")
        MATH(EXPR counter "${counter}+1")
        if (counter GREATER 16)
            string(APPEND output_c "\n    ")
            set(counter 0)
        endif ()
    endforeach ()

    set(output_c "
#include \"${c_name}.h\"
uint8_t ${c_name}_data[] = {
    ${output_c}
}\;
unsigned ${c_name}_size = sizeof(${c_name}_data)\;
")

    set(output_h "
#ifndef ${c_name}_H
#define ${c_name}_H
#include \"stdint.h\"
extern uint8_t ${c_name}_data[]\;
extern unsigned ${c_name}_size\;
#endif // ${c_name}_H
")

    file(WRITE ${CMAKE_BINARY_DIR}/classes/${c_name}.c
            ${output_c})

    file(WRITE ${CMAKE_BINARY_DIR}/classes/${c_name}.h
            ${output_h})

    file(APPEND ${CMAKE_BINARY_DIR}/classes/classes_combined.h
            "\n#include \"${c_name}.h\"")

    file(APPEND ${CMAKE_BINARY_DIR}/classes/classes_combined.c
            "\n${c_name}_data,")

    set(${generated_c} ${CMAKE_BINARY_DIR}/classes/${c_name}.c PARENT_SCOPE)

endfunction()

if (RUN_CLASS_FILE_GENERATE)
    ClassFileGenerate(${CLASS_FILE_GENERATE_PATH} var)
endif ()
