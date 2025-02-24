cmake_minimum_required(VERSION 3.10)
project(Game)

# Find SFML library
set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/sfml/lib/cmake/SFML")  # Adjust to your actual SFML installation path
find_package(SFML 2.6 COMPONENTS system window graphics REQUIRED)

# Add sources
file(GLOB RootDirSources src/*.cpp)
file(GLOB SingletonSources src/singleton/*.cpp)

# Create the executable
add_executable(Game ${RootDirSources} ${SingletonSources})

# Link SFML libraries
target_link_libraries(Game sfml-system sfml-window sfml-graphics)