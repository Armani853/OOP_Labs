project(lab_03 LANGUAGES CXX)

add_executable(lab_03_run src/main.cpp src/figure.cpp src/pentagon.cpp src/rhombus.cpp src/trapeze.cpp)

add_executable(lab_03_tests tests/test_figures.cpp src/figure.cpp src/pentagon.cpp src/rhombus.cpp src/trapeze.cpp)

target_link_libraries(lab_03_tests PRIVATE gtest gtest_main)