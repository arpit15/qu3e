include_directories (${qu3e_SOURCE_DIR})

add_executable(tutorial main.cpp)

target_link_libraries(tutorial
	qu3e
)