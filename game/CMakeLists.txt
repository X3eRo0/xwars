#include wxWidgets in your application
find_package(wxWidgets REQUIRED base core xml gl OPTIONAL_COMPONENTS net)
include(${wxWidgets_USE_FILE})
add_library(vm
    ../xasm/disasm.c
    ../xasm/xasm_functions.c
    ../xasm/parse.c
    ../xvm/cpu.c
    ../xvm/execute.c
    ../xvm/syscall.c
    ../common/loader.c
    ../common/sections.c
    ../common/signals.c
    ../common/symbols.c
    ../common/bitmap.c
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
    Factory.cpp
    Property.cpp
    PropertyDataWidgets.cpp
    PropertyDisplay.cpp
    SettingsDialog.cpp
    PropertyData.cpp
    StatsDisplay.cpp
)

target_link_libraries(xwars vm ${wxWidgets_LIBRARIES})
target_include_directories(xwars PUBLIC ${wxWidgets_INCLUDE_DIRS})
