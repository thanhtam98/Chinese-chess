cmake_minimum_required(VERSION 3.14)
project(chinese-chess VERSION 0.1.0 LANGUAGES CXX)

# =============================================================================
# Build Configuration
# =============================================================================

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# =============================================================================
# Dependencies
# =============================================================================

# Find required packages
# Boost.Beast is header-only and part of Boost (since 1.66)
# Note: Boost 1.90+ has system as header-only, so we don't request it as a component
find_package(Boost REQUIRED COMPONENTS thread regex)

# Boost 1.90+: system is header-only; create alias so Boost::system still links
if(NOT TARGET Boost::system)
    add_library(Boost::system INTERFACE IMPORTED)
    if(TARGET Boost::headers)
        set_target_properties(Boost::system PROPERTIES INTERFACE_LINK_LIBRARIES Boost::headers)
    endif()
endif()

find_package(Threads REQUIRED)

# Set threads preference
set(THREADS_PREFER_PTHREAD_FLAG ON)

# =============================================================================
# Local Dependencies (Vendored in third_party/)
# =============================================================================

# GoogleTest - local copy
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(third_party/googletest)

# nlohmann/json - local copy
add_subdirectory(third_party/json)

# Note: WebSocket++ removed - using Boost.Beast instead (built into Boost)

# =============================================================================
# Finalcut Library Setup
# =============================================================================

# Add cmake modules to search path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Platform-specific library extension
if(APPLE)
    set(FINALCUT_LIB_EXT "dylib")
else()
    set(FINALCUT_LIB_EXT "so")
endif()

# Check if finalcut library exists, if not build it.
# On macOS autotools may only create a versioned dylib (libfinal.0.dylib),
# so also check for that variant.
set(FINALCUT_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/libfinal/lib/libfinal.${FINALCUT_LIB_EXT}")
set(FINALCUT_LIBRARY_PATH_V "${CMAKE_SOURCE_DIR}/libfinal/lib/libfinal.0.${FINALCUT_LIB_EXT}")
if(NOT EXISTS "${FINALCUT_LIBRARY_PATH}" AND NOT EXISTS "${FINALCUT_LIBRARY_PATH_V}")
    message(STATUS "Finalcut library not found at ${FINALCUT_LIBRARY_PATH}. Building...")
    add_custom_target(
        build_finalcut
        COMMAND ${CMAKE_SOURCE_DIR}/scripts/build_finalcut.sh
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Building finalcut library"
    )
else()
    message(STATUS "Finalcut library found at: ${FINALCUT_LIBRARY_PATH}")
    add_custom_target(build_finalcut COMMENT "Finalcut library already exists")
endif()

# Clear cached find results so re-configures pick up fresh paths
unset(FINALCUT_LIBRARY CACHE)
unset(FINALCUT_INCLUDE_DIR CACHE)

# Find finalcut using our custom module
find_package(Finalcut REQUIRED)

# =============================================================================
# Include Directories
# =============================================================================

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/utils/inc
    ${CMAKE_SOURCE_DIR}/logic/inc
    ${CMAKE_SOURCE_DIR}/rule/inc
    ${CMAKE_SOURCE_DIR}/rule/behaviorProvider/inc
    ${CMAKE_SOURCE_DIR}/ui/inc
    ${CMAKE_SOURCE_DIR}/ui/label/inc
    ${CMAKE_SOURCE_DIR}/ui/turn/inc
    ${CMAKE_SOURCE_DIR}/ui/selection/inc
    ${CMAKE_SOURCE_DIR}/websockpp/inc
    ${FINALCUT_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)

# =============================================================================
# Source Files
# =============================================================================

# Collect source files
file(GLOB UTILS_SOURCES "utils/src/*.cpp")
file(GLOB LOGIC_SOURCES "logic/src/*.cpp")
file(GLOB RULE_SOURCES "rule/src/*.cpp")
file(GLOB BEHAVIOR_SOURCES "rule/behaviorProvider/src/*.cpp")
file(GLOB UI_SOURCES "ui/src/*.cpp")
file(GLOB LABEL_SOURCES "ui/label/src/*.cpp")
file(GLOB SELECT_SOURCES "ui/selection/src/*.cpp")
file(GLOB TURN_SOURCES "ui/turn/src/*.cpp")
file(GLOB WEBSOCKPP_SOURCES "websockpp/src/*.cpp")

# Combine all source files
set(ALL_SOURCES
    main.cpp
    ${UTILS_SOURCES}
    ${LOGIC_SOURCES}
    ${RULE_SOURCES}
    ${BEHAVIOR_SOURCES}
    ${UI_SOURCES}
    ${LABEL_SOURCES}
    ${SELECT_SOURCES}
    ${TURN_SOURCES}
    ${WEBSOCKPP_SOURCES}
)

# =============================================================================
# Main Executable
# =============================================================================

add_executable(chinese-chess ${ALL_SOURCES})

# Link libraries
target_link_libraries(chinese-chess
    PRIVATE 
        finalcut
        nlohmann_json::nlohmann_json
        Boost::system 
        Boost::thread 
        Boost::regex
        Threads::Threads
)

# Set target properties
get_filename_component(FINALCUT_LIB_DIR "${FINALCUT_LIBRARIES}" DIRECTORY)
set_target_properties(chinese-chess PROPERTIES
    INSTALL_RPATH "${FINALCUT_LIB_DIR}"
    BUILD_WITH_INSTALL_RPATH TRUE
    INSTALL_RPATH_USE_LINK_PATH TRUE
)

# Add dependency on finalcut build
add_dependencies(chinese-chess build_finalcut)

# =============================================================================
# Test Executable
# =============================================================================

# Test sources
set(TEST_SOURCES
    test/pointTest.cc
    test/ruleTest.cc
    test/utilsTest.cc
    ${UTILS_SOURCES}
    ${RULE_SOURCES}
    ${BEHAVIOR_SOURCES}
)

add_executable(mainTest ${TEST_SOURCES})

target_link_libraries(mainTest
    GTest::gtest_main
    GTest::gmock_main
)

# Include test directories
target_include_directories(mainTest PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/test
)

# =============================================================================
# Standalone WebSocket Client (for testing)
# =============================================================================

# Build a simple WebSocket client using Boost.Beast for testing
add_executable(websocketClient test/websocketClient.cpp)

target_include_directories(websocketClient PRIVATE
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(websocketClient
    PRIVATE
        Boost::system
        Threads::Threads
)

# =============================================================================
# Testing
# =============================================================================

enable_testing()
include(GoogleTest)
gtest_discover_tests(mainTest)

# =============================================================================
# Installation
# =============================================================================

# Install executable
install(TARGETS chinese-chess
    RUNTIME DESTINATION bin
)

# Install run script
install(FILES run_game.sh
    DESTINATION bin
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)

# =============================================================================
# Custom Targets
# =============================================================================

# Clean target
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/libfinal
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/finalcut
    COMMENT "Cleaning all build artifacts and dependencies"
)

# Rebuild finalcut target
add_custom_target(rebuild-finalcut
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/libfinal
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/finalcut
    COMMAND ${CMAKE_SOURCE_DIR}/scripts/build_finalcut.sh
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Rebuilding finalcut library from scratch"
)

# =============================================================================
# Print Configuration
# =============================================================================

message(STATUS "=== Build Configuration ===")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Platform: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Finalcut library: ${FINALCUT_LIBRARIES}")
message(STATUS "Finalcut include: ${FINALCUT_INCLUDE_DIRS}")
message(STATUS "Boost version: ${Boost_VERSION}")
message(STATUS "==========================")
