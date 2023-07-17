cmake_minimum_required(VERSION 3.23)

project(GAME VERSION 1.0)

# Enable C++20 features
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} 
  src/main.cpp
  src/Game.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# Find SDL2 libraries
find_package(SDL2 REQUIRED)

# Link SDL2 libraries
target_link_libraries(${PROJECT_NAME}
  SDL2::SDL2main
  SDL2::SDL2
)
