project(lab_02 LANGUAGES CXX)

add_executable(lab_02_run src/main.cpp src/twelve.cpp)

add_executable(lab_02_tests tests/test_twelve.cpp src/twelve.cpp)

target_link_libraries(lab_02_tests PRIVATE gtest gtest_main)