file(GLOB_RECURSE SRC *.cpp *.c *.hpp *.h)
set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(Landing ${SRC})
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
if(UNIX)
    target_link_libraries(Landing ${OpenCV_LIBS})
else()  
    target_link_libraries(Landing winmm ws2_32 ${OpenCV_LIBS})
endif()