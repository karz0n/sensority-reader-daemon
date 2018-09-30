# - finds libmosquitto
# Find the native libmosquitto includes and libraries
#
# Mosquitto_FOUND        - True if library found.
# Mosquitto_FIND_QUIETLY - True if library had been already found.
# Mosquitto_INCLUDE_DIRS - The list of include directories.
# Mosquitto_LIBRARIES    - The list of library directories.

if(Mosquitto_FOUND)
    set(Mosquitto_FIND_QUIETLY TRUE)
    return()
endif()

find_path(Mosquitto_INCLUDE_DIR mosquitto.h)
mark_as_advanced(Mosquitto_INCLUDE_DIR)

find_library(Mosquitto_LIBRARY NAMES mosquitto)
mark_as_advanced(Mosquitto_LIBRARY)

find_library(Mosquitto_PP_LIBRARY NAMES mosquittopp)
mark_as_advanced(Mosquitto_PP_LIBRARY)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Mosquitto
    DEFAULT_MSG
    Mosquitto_INCLUDE_DIR Mosquitto_LIBRARY Mosquitto_PP_LIBRARY)

if(Mosquitto_FOUND)
    set(Mosquitto_INCLUDE_DIRS ${Mosquitto_INCLUDE_DIR})
    set(Mosquitto_LIBRARIES ${Mosquitto_LIBRARY} ${Mosquitto_PP_LIBRARY})
endif()
