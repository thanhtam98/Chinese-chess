cmake_minimum_required(VERSION 3.14)
project(chinese-chess VERSION 0.1)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
# set(CMAKE_BUILD_PARALLEL_LEVEL 12)
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# === websocket++ ===
FetchContent_Declare(websocketpp
GIT_REPOSITORY https://github.com/zaphoyd/websocketpp.git
  GIT_TAG 0.8.2)
FetchContent_GetProperties(websocketpp)
if(NOT websocketpp_POPULATED)
  FetchContent_Populate(websocketpp)
  add_subdirectory(${websocketpp_SOURCE_DIR} ${websocketpp_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(CMakePrintHelpers)

set(CMAKE_BUILD_TYPE Debug)
# Dependencies
find_package(Boost COMPONENTS system REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Assign the include directories
include_directories(${Boost_INCLUDE_DIRS})

# add_subdirectory(finalcut)

include_directories(utils/inc)
include_directories(logic/inc)
include_directories(rule/inc)
include_directories(rule/behaviorProvider/inc)
include_directories(ui/inc)
include_directories(ui/label/inc)
include_directories(ui/turn/inc)
include_directories(websockpp/inc)
include_directories(final)
include_directories(.)

FILE(GLOB UTILS utils/src/*.cpp)
FILE(GLOB LOGIC logic/src/*.cpp)
FILE(GLOB RULE rule/src/*.cpp)
FILE(GLOB BEHAVIOR rule/behaviorProvider/src/*.cpp)
FILE(GLOB UI ui/src/*.cpp)
FILE(GLOB LABEL ui/label/src/*.cpp)
FILE(GLOB TURN ui/turn/src/*.cpp)
FILE(GLOB WEBSOCKPP websockpp/src/*cpp)

# Set source files
set(DEP 
    ${UTILS}
    ${LOGIC}
    ${RULE}
    ${BEHAVIOR}
    ${UI}
    ${LABEL}
    ${TURN}
    ${WEBSOCKPP}
    )
set(SOURCES
    main.cpp
    ${DEP}
)
set(FINALCUT
    ${CMAKE_SOURCE_DIR}/libfinal/lib/libfinal.so)

cmake_print_variables(FINALCUT)

# Create executable
add_executable(chinese-chess ${SOURCES})
# add_executable(client ${SOURCES})

# Link libraries
# include(finalcut)
target_include_directories(chinese-chess PUBLIC ${websocketpp_SOURCE_DIR})
target_link_libraries(chinese-chess
    PRIVATE finalcut
    INTERFACE Boost::system Boost::thread Boost::regex
)
add_library(finalcut SHARED IMPORTED)
set_property(TARGET finalcut PROPERTY IMPORTED_LOCATION ${FINALCUT})

add_custom_target(
    build_finalcut
    COMMAND [ ! -f ${FINALCUT} ] && cd ${CMAKE_SOURCE_DIR} && ./scripts/build_finalcut.sh && cd - || true
)

add_dependencies(chinese-chess build_finalcut)

enable_testing()


add_executable(
  mainTest
  test/pointTest.cc
  test/ruleTest.cc
  test/utilsTest.cc
  ${UTILS}
  ${RULE}
  ${BEHAVIOR}

)

target_link_libraries(
  mainTest
  GTest::gtest_main
  GTest::gmock_main
)

include(GoogleTest)
include_directories(
  .
  test
  ) 
gtest_discover_tests(mainTest)
