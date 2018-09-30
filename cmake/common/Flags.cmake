#
#
#
if(CMAKE_COMPILER_IS_GNUCXX)
    set(optimization_flags)
else()
   message(WARNING "Compiler ${CMAKE_CXX_COMPILER_ID} is not supported yet")
endif()

#
#
#
if(CMAKE_COMPILER_IS_GNUCXX)
    set(warning_flags
        -Wall       #
        -Wextra     #
        -Wpedantic  #
        -Wno-psabi  # Disable ABI incompatible warnings between GCC 6.x and 8.1
    )
else()
   message(WARNING "Compiler ${CMAKE_CXX_COMPILER_ID} is not supported yet")
endif()

#
#
#
if(CMAKE_COMPILER_IS_GNUCXX)
   set(debug_flags
       ${warning_flags}
   )
else()
   message( WARNING "Compiler ${CMAKE_CXX_COMPILER_ID} is not supported yet" )
endif()

#
#
#
if(CMAKE_COMPILER_IS_GNUCXX)
   set(release_flags
       ${warning_flags}
       ${optimization_flags}
   )
else()
   message( WARNING "Compiler ${CMAKE_CXX_COMPILER_ID} is not supported yet" )
endif()
