project(lab_07 LANGUAGES CXX)

add_executable(lab_07_run main.cpp src/simulation.cpp src/battle_logic.cpp)

add_executable(lab_07_tests tests/battle_tests.cpp src/simulation.cpp src/battle_logic.cpp)

target_link_libraries(lab_07_tests PRIVATE gtest gtest_main)

find_package(Threads REQUIRED)
target_link_libraries(lab_07_run PRIVATE Threads::Threads)