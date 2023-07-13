cmake_minimum_required(VERSION 3.26.4)

project(GEA VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(
  ${PROJECT_NAME} 
  src/main.cpp
  src/Game.cpp
  )


target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
