cmake_minimum_required(VERSION 3.7)
project(lem-in)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        get_next_line/get_next_line.c
        src/depth_algorithm/choose_path_group.c
        src/display.c
        src/err_atoi.c
        src/errors.c
        src/depth_algorithm/find_path_groups.c
        src/generate_steps.c
        src/depth_algorithm/get_all_paths.c
        src/graph.c
        src/list/list.c
        src/list/create.c
        src/list/add.c
        src/main.c
        src/parse/parse.c
        src/parse/parse_rooms.c
        src/room.c
        src/create_steps.c
        src/debug_display.c
        src/free/free_1.c
        src/free/free_2.c
        src/list/add_room.c
        src/get_next_write.c
        )

add_executable(lem-in ${SOURCE_FILES})

file(GLOB SOURCES_LIB get_next_line/libft/*.c)
add_library(ft STATIC ${SOURCES_LIB})       # Создание статической библиотеки с именем libft

target_link_libraries(lem-in ft)	        # Линковка программы с библиотекой