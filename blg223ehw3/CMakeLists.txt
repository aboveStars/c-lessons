cmake_minimum_required(VERSION 3.29)
project(blg223ehw3 C)

set(CMAKE_C_STANDARD 11)

add_executable(blg223ehw3
        include/connect4.h
        include/game_bot.h
        include/interface.h
        include/tree.h
        src/connect4.c
        src/game_bot.c
        src/interface.c
        src/tree.c
        include/game_bot_tests.h
        include/interface_tests.h
        include/tree_tests.h
        src/munit.c
        include/munit.h
        src/tests.c
)
