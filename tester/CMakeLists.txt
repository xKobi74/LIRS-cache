cmake_minimum_required (VERSION 3.16)
project ("LIRS CACHE TESTER" VERSION 1.0.0) 

set (EXEC_FILE "lirs_tester")

set (INCLUDE 

    ../include
)

set (SOURCES 

    ../source/hash.c
    ../source/stack.c
    ../source/list.c
    ../source/cache_storage.c
    ../source/lirs.c
    ../tester/main_tester.c
    ../tester/tester.c
)

add_executable (${EXEC_FILE} ${SOURCES})
target_include_directories (${EXEC_FILE} PRIVATE ${INCLUDE})

set (COMPILE_SETTINGS

    -Wall
    -Wextra
    -Wpedantic
    -O2
)

target_compile_options (${EXEC_FILE} PRIVATE ${COMPILE_SETTINGS})