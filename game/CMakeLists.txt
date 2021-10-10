#include wxWidgets in your application
find_package(wxWidgets REQUIRED base core gl OPTIONAL_COMPONENTS net)
include(${wxWidgets_USE_FILE})

add_library(libxvm 
    ../xasm/disasm.c
    ../xasm/xasm_functions.c
    ../xasm/parse.c
    ../xvm/cpu.c
    ../xvm/execute.c
    ../xvm/syscall.c 
    ../common/loader.c
    ../common/sections.c
    ../common/segfault.c
    ../common/signals.c
    ../common/symbols.c
)

# create executable
add_executable(xwars 
    Common.cpp
    MainApp.cpp
    MainWindow.cpp
    MiddlePanel.cpp
    MemoryGrid.cpp
    Arena.cpp
    InstructionDisplay.cpp
    RegisterDisplay.cpp
    XBot.cpp
    XWars.cpp
    Register.cpp
    BotNameDisplay.cpp
    BotInfo.cpp
)

target_link_libraries(xwars libxvm ${wxWidgets_LIBRARIES})
target_include_directories(xwars PUBLIC ${wxWidgets_INCLUDE_DIRS})
