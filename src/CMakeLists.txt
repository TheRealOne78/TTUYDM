# Set the output directory for libraries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
	${CMAKE_BINARY_DIR}/libs)

# Set main executable source files
set("${PROJECT_NAME}_SRC"
	main.cpp)

add_executable(${PROJECT_NAME}
	"${${PROJECT_NAME}_SRC}")

target_include_directories("${PROJECT_NAME}" PRIVATE
  "${PROJECT_SOURCE_DIR}/include"
  "${PROJECT_BINARY_DIR}/include")

target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

# Set the output directory for executables
set(EXECUTABLE_OUTPUT_PATH
	"${CMAKE_BINARY_DIR}/build")
