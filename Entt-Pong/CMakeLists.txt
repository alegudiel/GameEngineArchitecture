cmake_minimum_required(VERSION 3.23)

project(GAME VERSION 1.0)

# Enable C++20 features
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(SDL2, /Library/Frameworks/SDL2.framework)
set(glm_header_search_path /Library/Frameworks/glm/)
set(ENTT_INCLUDE_DIR /usr/local/Cellar/entt/3.12.2/include)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${glm_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
    ${ENTT_INCLUDE_DIR}  
)

add_executable(${PROJECT_NAME} 
  src/main.cpp
  src/Game/Game.cpp
  src/Pong/Pong.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${glm_header_search_path}
    ${PROJECT_SOURCE_DIR}/src/
    ${PROJECT_SOURCE_DIR}/src/Game
    ${PROJECT_SOURCE_DIR}/src/Scene
    ${PROJECT_SOURCE_DIR}/include
)
# Find GLM
find_package(glm REQUIRED)

# Find SDL2 libraries
find_package(SDL2 REQUIRED)

# Find entt 

# Link SDL2 libraries
target_link_libraries(${PROJECT_NAME}
  SDL2::SDL2main
  SDL2::SDL2
)
