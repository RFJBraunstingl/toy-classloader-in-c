function(EmbedClassFiles path)
    SetupClassFileStore()
    file(GLOB_RECURSE files ${path})

    set(output_h "
#ifndef CLASSES_COMBINED_H
#define CLASSES_COMBINED_H
#include \"stdint.h\"
typedef uint8_t * classfile_pointer\;
extern classfile_pointer all_class_files[]\;
// extern unsigned ${c_name}_size\;
#endif // CLASSES_COMBINED_H
")

    file(WRITE ${CMAKE_BINARY_DIR}/classes/classes_combined.h
            ${output_h})

    set(output_c "
#include \"classes_combined.h\"
classfile_pointer all_class_files[] = {")

    file(WRITE ${CMAKE_BINARY_DIR}/classes/classes_combined.c
            ${output_c})

    foreach(file ${files})
        EmbedClassFile(${file})
    endforeach()

    file(APPEND ${CMAKE_BINARY_DIR}/classes/classes_combined.c
            "\n};")
endfunction()

function(SetupClassFileStore)

    message("setting up class file store")
    if (NOT EXISTS ${CMAKE_BINARY_DIR}/classes)
        file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/classes)
    endif ()

    add_library(classes ${CMAKE_BINARY_DIR}/classes/classes_combined.h)
    target_include_directories(classes PUBLIC ${CMAKE_BINARY_DIR}/classes)

endfunction()

function(EmbedClassFile file)
    message("embed class file ${file}")
    ClassFileGenerate(${file} var)
    target_sources(classes PUBLIC ${var})
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
