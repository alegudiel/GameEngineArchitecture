cmake_minimum_required(VERSION 3.23)

project(GAME VERSION 1.0)

# Enable C++20 features
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(src/Game)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${PROJECT_SOURCE_DIR}/src/Game
)

target_link_directories(${PROJECT_NAME}
  PRIVATE src/Game
)

target_link_libraries(${PROJECT_NAME}
  SDL2main
  SDL2
  Game
)