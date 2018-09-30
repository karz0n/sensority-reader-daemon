# - finds the c-ares library
# Find the native c-ares includes and libraries
#
# Cares_FOUND         - True if library found.
# Cares_FOUND_QUIETLY - True if library had been already found.
# Cares_INCLUDE_DIRS  - The list of include directories.
# Cares_LIBRARIES     - The list of library directories.

if(Cares_FOUND)
    set(Cares_FOUND_QUIETLY TRUE)
    return()
endif()

find_path(Cares_INCLUDE_DIR ares.h)
mark_as_advanced(Cares_INCLUDE_DIR)

find_library(Cares_LIBRARY NAMES cares)
mark_as_advanced(Cares_LIBRARY)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Cares
    DEFAULT_MSG
    Cares_INCLUDE_DIR Cares_LIBRARY)

if(Cares_FOUND)
    set(Cares_INCLUDE_DIRS ${Cares_INCLUDE_DIR})
    set(Cares_LIBRARIES ${Cares_LIBRARY})
endif()
