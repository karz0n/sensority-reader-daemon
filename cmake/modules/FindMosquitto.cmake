# - Find libmosquitto
# Find the native libmosquitto includes and libraries
#
#  Mosquitto_INCLUDE_DIRS - where to find mosquitto.h, etc.
#  Mosquitto_LIBRARIES    - List of libraries when using libmosquitto.
#  Mosquitto_FOUND        - True if libmosquitto found.

if(Mosquitto_INCLUDE_DIRS)
    set(Mosquitto_FIND_QUIETLY TRUE)
endif(Mosquitto_INCLUDE_DIRS)

find_path(Mosquitto_INCLUDE_DIRS mosquitto.h)

find_library(Mosquitto_LIBRARY NAMES libmosquitto mosquitto)
find_library(Mosquitto_PP_LIBRARY NAMES libmosquittopp mosquittopp)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    Mosquitto
    DEFAULT_MSG
    Mosquitto_LIBRARY Mosquitto_PP_LIBRARY Mosquitto_INCLUDE_DIRS)

if(Mosquitto_FOUND)
  set(Mosquitto_LIBRARIES ${Mosquitto_LIBRARY} ${Mosquitto_PP_LIBRARY})
else(Mosquitto_FOUND)
  set(Mosquitto_LIBRARIES)
endif(Mosquitto_FOUND)

mark_as_advanced(Mosquitto_INCLUDE_DIRS Mosquitto_LIBRARY Mosquitto_PP_LIBRARY)
