cmake_minimum_required(VERSION 3.16)
project(xvm C CXX)

# for pure xvm
set(CMAKE_C_STANDARD 11)

# for arena
# arena is written in cpp
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_BUILD_TYPE Debug)

# c binaries exec flag setup
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -g -O0")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g -O0")

add_executable(xvm
    xvm/xvm.c
    xvm/cpu.c
    xvm/cpu.h
    xvm/execute.c
    common/symbols.c
    common/symbols.h
    common/const.h
    common/loader.c
    common/loader.h
    common/sections.c
    common/sections.h
    common/bitmap.c
    common/bitmap.h
    xvm/syscall.c
    common/signals.c
    common/signals.h)

add_executable(xasm
    xasm/xasm.c
    xasm/xasm.h
    xasm/xasm_functions.c
    xasm/parse.c
    common/symbols.c
    common/symbols.h
    common/sections.c
    common/sections.h
    common/loader.c
    common/loader.h
    common/signals.c
    common/signals.h
    common/bitmap.c
)

add_executable(xinfo
    xasm/xinfo.c
    common/loader.c
    common/loader.h
    common/symbols.c
    common/symbols.h
    common/sections.c
    common/sections.h
    common/signals.c
    common/signals.h
    common/bitmap.c
)

add_executable(xdis
    xasm/xdis.c
    xasm/disasm.c
    xasm/xasm_functions.c
    common/loader.c
    common/loader.h
    common/symbols.c
    common/symbols.h
    common/sections.c
    common/sections.h
    common/signals.c
    common/signals.h
    common/bitmap.c
)

# build xwars
add_subdirectory(game)
