cmake_minimum_required(VERSION 3.31)

project(Mrz-Raylib-Pid)

include_directories(${CMAKE_SOURCE_DIR}/include)

link_directories(${CMAKE_SOURCE_DIR}/lib)

set(SOURCES 
    src/main.cpp 
    include/arms.cpp 
    include/motors.cpp
    include/gearboxs.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(Mrz-Raylib-Pid ${CMAKE_SOURCE_DIR}/lib/libraylib.a)
target_link_libraries(Mrz-Raylib-Pid raylib winmm)
