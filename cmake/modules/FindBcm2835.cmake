# - finds the bcm2835 library
# Find the native bcm2835 includes and libraries
#
#  Bcm2835_FOUND        - True if bcm2835 found.
#  Bcm2835_FIND_QUIETLY - True if bcm2835 had been already found.
#  Bcm2835_INCLUDE_DIRS - The bcm2835 include directories
#  Bcm2835_LIBRARIES    - The libraries needed to use bcm2835
#  Bcm2835_DEFINITIONS  - Compiler switches required for using bcm2835

if(Bcm2835_FOUND)
    set(Bcm2835_FIND_QUIETLY TRUE)
endif()

find_path(Bcm2835_INCLUDE_DIR bcm2835.h)
if(NOT Bcm2835_INCLUDE_DIR)
    message(FATAL_ERROR "Bcm2835_INCLUDE_DIR NOT FOUND")
else()
    mark_as_advanced(Bcm2835_INCLUDE_DIR)
endif()

find_library(Bcm2835_LIBRARY NAMES bcm2835)
if(NOT Bcm2835_LIBRARY)
    message(FATAL_ERROR "Bcm2835_LIBRARY NOT FOUND")
else()
    mark_as_advanced(Bcm2835_LIBRARY)
endif()

list(APPEND Bcm2835_LIBRARIES ${Bcm2835_LIBRARY})
list(APPEND Bcm2835_INCLUDE_DIRS ${Bcm2835_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    Bcm2835 DEFAULT_MSG
    Bcm2835_LIBRARY Bcm2835_INCLUDE_DIR)
