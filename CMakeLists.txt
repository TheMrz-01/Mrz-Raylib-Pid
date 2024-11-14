cmake_minimum_required(VERSION 3.31)

project(Mrz-Raylib-Pid)

include_directories(${CMAKE_SOURCE_DIR}/include)

link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(${PROJECT_NAME} src/main.c)

target_link_libraries(Mrz-Raylib-Pid ${CMAKE_SOURCE_DIR}/lib/libraylib.a)
target_link_libraries(Mrz-Raylib-Pid raylib winmm)
