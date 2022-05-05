cmake_minimum_required(VERSION 3.14.0)
project(Game VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lX11")
endif()

# add_subdirectory()
# target_link_libraries(devemul microapro)
# target_include_directories(devemul PRIVATE "${PROJECT_SOURCE_DIR}/microapro/lib/include")


## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_subdirectory(src)

target_include_directories(game_lib PRIVATE ${SFML_INCLUDE_DIR} ${X11_INCLUDE_DIR})
target_include_directories(game_lib PRIVATE "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(game_lib sfml-graphics sfml-audio)

add_executable(${PROJECT_NAME} 
    main.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE ${SFML_INCLUDE_DIR} ${X11_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(${PROJECT_NAME} game_lib)
