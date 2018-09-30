# - finds the bcm2835 library
# Find the native bcm2835 includes and libraries
#
# Bcm2835_FOUND         - True if library found.
# Bcm2835_FOUND_QUIETLY - True if library had been already found.
# Bcm2835_INCLUDE_DIRS  - The list of include directories.
# Bcm2835_LIBRARIES     - The list of library directories.

if(Bcm2835_FOUND)
    set(Bcm2835_FOUND_QUIETLY TRUE)
    return()
endif()

find_path(Bcm2835_INCLUDE_DIR bcm2835.h)
mark_as_advanced(Bcm2835_INCLUDE_DIR)

find_library(Bcm2835_LIBRARY NAMES bcm2835)
mark_as_advanced(Bcm2835_LIBRARY)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Bcm2835
    DEFAULT_MSG
    Bcm2835_LIBRARY Bcm2835_INCLUDE_DIR)

if(Bcm2835_FOUND)
    set(Bcm2835_INCLUDE_DIRS ${Bcm2835_INCLUDE_DIR})
    set(Bcm2835_LIBRARIES ${Bcm2835_LIBRARY})
endif()
