if(DEFINED ENV{ARM_DEPLOY_PATH})
    set(ARM_DEPLOY_PATH $ENV{ARM_DEPLOY_PATH})
    message(STATUS "ARM deploy path is ${ARM_DEPLOY_PATH}")
else()
    message(FATAL_ERROR "ARM deploy path not sets")
    return()
endif()

file(WRITE "${PROJECT_SOURCE_DIR}/QtCreatorDeployment.txt" "${ARM_DEPLOY_PATH}\n")

macro(add_deployment_file SRC DEST)
    file(RELATIVE_PATH path "${PROJECT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
    file(APPEND "${PROJECT_SOURCE_DIR}/QtCreatorDeployment.txt" "${path}/${SRC}:${DEST}\n")
endmacro()

macro(add_deployment_directory SRC DEST)
    file(GLOB_RECURSE files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${SRC}/*")
    foreach(filename ${files})
        get_filename_component(path ${filename} PATH)
        add_deployment_file("${filename}" "${DEST}/${path}")
    endforeach(filename)
endmacro()