cmake_minimum_required(VERSION 3.14)
project(chinese-chess)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  mainTest
  mainTest.cc
  utils/point.cpp
)

target_link_libraries(
  mainTest
  GTest::gtest_main
)

include(GoogleTest)
include_directories(
  .
  ) 
gtest_discover_tests(mainTest)
