#include wxWidgets in your application
find_package(wxWidgets REQUIRED base core gl OPTIONAL_COMPONENTS net)
include(${wxWidgets_USE_FILE})

# create executable
add_executable(arena MainApp.cpp MainWindow.cpp MiddlePanel.cpp MemoryGrid.cpp ArenaTerminal.cpp)
target_link_libraries(arena ${wxWidgets_LIBRARIES})
target_include_directories(arena PUBLIC ${wxWidgets_INCLUDE_DIRS})