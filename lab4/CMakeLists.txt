project(lab_04 LANGUAGES CXX)

add_executable(lab_04_run main.cpp include/figure.h include/point.h include/factory.h include/shapes.h)

add_executable(lab_04_tests tests/test_figures.cpp include/figure.h include/point.h include/factory.h include/shapes.h)

target_link_libraries(lab_04_tests PRIVATE gtest gtest_main)