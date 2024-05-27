# Set the output directory for libraries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
  "${CMAKE_BINARY_DIR}/libs")

# Set main executable source files
set("${PROJECT_NAME}_SRC"
  main.cpp
  arghandleopts.c
  signal-handlers.c
  ttuydm.cpp
  version-help.c
)

set("${PROJECT_NAME}_SESSIONS_SRC"
  session.cpp
  sessions.cpp
)

set("${PROJECT_NAME}_USERS_SRC"
  user.cpp
  users.cpp
)

set("${PROJECT_NAME}_UI_SRC"
  ui-passwordentry.cpp
  ui-sessionentry.cpp
  ui-userentry.cpp
  ui.cpp
)

add_library("${PROJECT_NAME}_sessions"
  "${${PROJECT_NAME}_SESSIONS_SRC}"
)
add_library("${PROJECT_NAME}_users"
  "${${PROJECT_NAME}_USERS_SRC}"
)
add_library("${PROJECT_NAME}_ui"
  "${${PROJECT_NAME}_UI_SRC}"
)

add_executable(${PROJECT_NAME}
  "${${PROJECT_NAME}_SRC}")

set(include_dirs
  "${PROJECT_SOURCE_DIR}/include"
  "${PROJECT_BINARY_DIR}/include"
)

foreach(target
  "${PROJECT_NAME}"
  "${PROJECT_NAME}_sessions"
  "${PROJECT_NAME}_users"
  "${PROJECT_NAME}_ui"
)
  target_include_directories(${target} PRIVATE ${include_dirs})
endforeach()


target_link_libraries("${PROJECT_NAME}"
  "${PROJECT_NAME}_sessions"
  "${PROJECT_NAME}_users"
  "${PROJECT_NAME}_ui"


  "${CURSES_LIBRARIES}"
  "${PAM_LIBRARIES}"
  spdlog::spdlog)

# Set the output directory for executables
set(EXECUTABLE_OUTPUT_PATH
  "${CMAKE_BINARY_DIR}/build")
