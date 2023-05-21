cmake_minimum_required(VERSION 3.14)
project(chinese-chess VERSION 0.1)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_BUILD_PARALLEL_LEVEL 12)
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


# add_subdirectory(finalcut)

include_directories(utils/inc)
include_directories(logic/inc)
include_directories(rule/inc)
include_directories(rule/behaviorProvider/inc)
include_directories(ui/inc)
include_directories(ui/label/inc)
include_directories(ui/turn/inc)
include_directories(final)
include_directories(.)

FILE(GLOB UTILS utils/src/*.cpp)
FILE(GLOB LOGIC logic/src/*.cpp)
FILE(GLOB RULE rule/src/*.cpp)
FILE(GLOB BEHAVIOR rule/behaviorProvider/src/*.cpp)
FILE(GLOB UI ui/src/*.cpp)
FILE(GLOB LABEL ui/label/src/*.cpp)
FILE(GLOB TURN ui/turn/src/*.cpp)


# Set source files
set(SOURCES
    main.cpp
    ${UTILS}
    ${LOGIC}
    ${RULE}
    ${BEHAVIOR}
    ${UI}
    ${LABEL}
    ${TURN}

)
set(FINALCUT
    /workspaces/chinese-chess/libfinal/lib/libfinal.so)

# Create executable
add_executable(chinese-chess ${SOURCES})

# Link libraries
# include(finalcut)
target_link_libraries(chinese-chess
    finalcut
)
add_library(finalcut SHARED IMPORTED)
set_property(TARGET finalcut PROPERTY IMPORTED_LOCATION "/workspaces/chinese-chess/libfinal/lib/libfinal.so")

add_custom_target(
    build_finalcut
    COMMAND [ ! -f ${FINALCUT} ] && cd /workspaces/chinese-chess/ && ./scripts/build_finalcut.sh && cd - || true
)
add_dependencies(chinese-chess build_finalcut)

# enable_testing()


# add_executable(
#   mainTest
#   test/pointTest.cc
#   test/ruleTest.cc
#   test/utilsTest.cc
#   ${UTILS}
#   ${RULE}
#   ${BEHAVIOR}

# )

# target_link_libraries(
#   mainTest
#   GTest::gtest_main
#   GTest::gmock_main
# )

# include(GoogleTest)
# include_directories(
#   .
#   test
#   ) 
# gtest_discover_tests(mainTest)
