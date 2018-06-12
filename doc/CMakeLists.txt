#
# Doxygen (dot)
#
# Install:
#   $ sudo apt-get install doxygen graphviz
#
# To generate UML diagram, download PlantUml and specify 'PLANTUML_JAR_PATH' environment variable
# (e.g. `export PLANTUML_JAR_PATH=/usr/share/java/plantuml.jar`)
#

if(BUILD_DOC)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()

    if(DEFINED ENV{PLANTUML_JAR_PATH})
        set(DOXYGEN_PLANTUML_JAR_PATH $ENV{PLANTUML_JAR_PATH})
        message(STATUS "PlantUml JAR path is ${DOXYGEN_PLANTUML_JAR_PATH}")
    endif()
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "README.md")

    doxygen_add_docs(doc
            LICENSE.md
            README.md
            doc
            src
        WORKING_DIRECTORY
            ${PROJECT_SOURCE_DIR}
        COMMENT
            "Generate project documentation")
endif()
