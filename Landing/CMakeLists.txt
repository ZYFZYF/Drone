file(GLOB_RECURSE SRC *.cpp *.c *.hpp *.h)

set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Landing ${SRC})
target_link_libraries(Landing winmm ws2_32)