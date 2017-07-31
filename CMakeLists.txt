cmake_minimum_required(VERSION 3.7)
project(lem-in)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        get_next_line/get_next_line.c
        src/err_atoi.c
        src/errors.c
        src/graph.c
        src/list.c
        src/main.c
        src/parse.c
        src/room.c
        src/stack_operations.c
        )

add_executable(lem-in ${SOURCE_FILES})

file(GLOB SOURCES_LIB get_next_line/libft/*.c)
add_library(ft STATIC ${SOURCES_LIB})       # Создание статической библиотеки с именем libft

target_link_libraries(lem-in ft)	        # Линковка программы с библиотекой