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
  test/pointTest.cc
  test/ruleTest.cc
  test/utilsTest.cc
  utils/point.cpp
  utils/utils.cpp
  rule/rule.cpp
  rule/ruleLimitBuilder.cpp
  rule/ruleShapeBuilder.cpp
  rule/ruleTargetBuilder.cpp
  rule/behaviorProvider/abstractBehaviorProvider.cpp
  rule/behaviorProvider/directionIterator.cpp
  rule/behaviorProvider/cannonBehaviorProvider.cpp
  rule/behaviorProvider/chariotBehaviorProvider.cpp
  rule/behaviorProvider/defaultBehaviorProvider.cpp
  rule/behaviorProvider/soldierBehaviorProvider.cpp
  rule/behaviorProvider/abstractBehaviorProvider.cpp
  rule/behaviorProvider/directionIterator.cpp
  
)

target_link_libraries(
  mainTest
  GTest::gtest_main
  GTest::gmock_main
)

include(GoogleTest)
include_directories(
  .
  ) 
gtest_discover_tests(mainTest)
