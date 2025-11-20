project(lab_05 LANGUAGES CXX)

add_executable(lab_05_run main.cpp include/list_resource.h include/pmr_vector.h)

add_executable(lab_05_tests tests/pmr_tests.cpp include/list_resource.h include/pmr_vector.h)

target_link_libraries(lab_05_tests PRIVATE gtest gtest_main)