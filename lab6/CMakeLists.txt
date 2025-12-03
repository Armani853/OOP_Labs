project(lab_06 LANGUAGES CXX)

add_executable(lab_06_run main.cpp src/npc.cpp src/battle_visitor.cpp src/observer.cpp src/npc_factory.cpp src/dungeon_editor.cpp)

add_executable(lab_06_tests tests/dungeon_tests.cpp src/npc.cpp src/battle_visitor.cpp src/observer.cpp src/npc_factory.cpp src/dungeon_editor.cpp)

target_link_libraries(lab_06_tests PRIVATE gtest gtest_main)