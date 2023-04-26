#--------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.21.3)

set(CMAKE_TOOLCHAIN_FILE "/home/onefore/coding-src/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(course-paper)

#--------------------------------------------------------------------------------

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

# Sources include
add_executable(${PROJECT_NAME} main.cpp sources/Bot.cpp sources/Eat.cpp sources/Empty.cpp sources/Object.cpp sources/Poison.cpp sources/Wall.cpp sources/World.cpp sources/Graphics.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

# Output file name settings
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/$<0:>)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX .exe)

#--------------------------------------------------------------------------------