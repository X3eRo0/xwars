#include wxWidgets in your application
find_package(wxWidgets REQUIRED base core gl OPTIONAL_COMPONENTS net)
include(${wxWidgets_USE_FILE})

add_library(arena_deps  ../xasm/xasm_functions.c
                        ../xasm/parse.c
                        ../xvm/cpu.c
                        ../xvm/execute.c
                        ../xvm/syscall.c 
                        ../common/loader.c
                        ../common/sections.c
                        ../common/segfault.c
                        ../common/signals.c
                        ../common/symbols.c)

# create executable
add_executable(arena MainApp.cpp MainWindow.cpp MiddlePanel.cpp MemoryGrid.cpp ArenaTerminal.cpp
                     XBot.cpp XWar.cpp)
target_link_libraries(arena arena_deps ${wxWidgets_LIBRARIES})
target_include_directories(arena PUBLIC ${wxWidgets_INCLUDE_DIRS})