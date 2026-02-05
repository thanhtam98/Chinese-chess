# =============================================================================
# FindFinalcut.cmake
# Cross-platform support for Linux and macOS
# =============================================================================

# Find the finalcut library and headers
# This module sets the following variables:
#   FINALCUT_FOUND - True if finalcut is found
#   FINALCUT_LIBRARIES - The finalcut libraries
#   FINALCUT_INCLUDE_DIRS - The finalcut include directories

# Set search paths
set(FINALCUT_SEARCH_PATHS
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/libfinal
    ${CMAKE_SOURCE_DIR}/finalcut
    /usr/local
    /usr
)

# Platform-specific library names
if(APPLE)
    set(FINALCUT_LIB_NAMES 
        final
        libfinal.dylib
        libfinal.1.dylib
    )
else()
    set(FINALCUT_LIB_NAMES 
        final
        libfinal.so
        libfinal.so.1
    )
endif()

# Find the library
find_library(FINALCUT_LIBRARY
    NAMES ${FINALCUT_LIB_NAMES}
    PATHS ${FINALCUT_SEARCH_PATHS}
    PATH_SUFFIXES lib lib64
    NO_DEFAULT_PATH
)

# Find the include directory
find_path(FINALCUT_INCLUDE_DIR
    NAMES final.h
    PATHS ${FINALCUT_SEARCH_PATHS}
    PATH_SUFFIXES final include/final include
    NO_DEFAULT_PATH
)

# Debug output (uncomment for debugging)
# message(STATUS "FINALCUT_SEARCH_PATHS: ${FINALCUT_SEARCH_PATHS}")
# message(STATUS "FINALCUT_LIB_NAMES: ${FINALCUT_LIB_NAMES}")
# message(STATUS "FINALCUT_LIBRARY: ${FINALCUT_LIBRARY}")
# message(STATUS "FINALCUT_INCLUDE_DIR: ${FINALCUT_INCLUDE_DIR}")

# Check if we found everything
if(FINALCUT_LIBRARY AND FINALCUT_INCLUDE_DIR)
    set(FINALCUT_FOUND TRUE)
    set(FINALCUT_LIBRARIES ${FINALCUT_LIBRARY})
    set(FINALCUT_INCLUDE_DIRS ${FINALCUT_INCLUDE_DIR})
    
    # Create imported target
    if(NOT TARGET finalcut)
        add_library(finalcut SHARED IMPORTED)
        set_target_properties(finalcut PROPERTIES
            IMPORTED_LOCATION "${FINALCUT_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${FINALCUT_INCLUDE_DIR}"
        )
    endif()
    
    message(STATUS "Found finalcut: ${FINALCUT_LIBRARY}")
    message(STATUS "  Include dir: ${FINALCUT_INCLUDE_DIR}")
else()
    set(FINALCUT_FOUND FALSE)
    message(STATUS "Finalcut not found")
    if(APPLE)
        message(STATUS "  Expected library: libfinal.dylib in ${FINALCUT_SEARCH_PATHS}")
    else()
        message(STATUS "  Expected library: libfinal.so in ${FINALCUT_SEARCH_PATHS}")
    endif()
endif()

# Handle the QUIETLY and REQUIRED arguments
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Finalcut
    REQUIRED_VARS FINALCUT_LIBRARY FINALCUT_INCLUDE_DIR
    FOUND_VAR FINALCUT_FOUND
)
