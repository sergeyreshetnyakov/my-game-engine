cmake_minimum_required(VERSION 3.20)
project(MyGame C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fms-extensions")

find_package(OpenGL REQUIRED)

include(FetchContent)

FetchContent_Declare(
    sokol
    GIT_REPOSITORY https://github.com/floooh/sokol.git
    GIT_TAG master
)
FetchContent_MakeAvailable(sokol)

FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb
    GIT_TAG master
)
FetchContent_MakeAvailable(stb)

FetchContent_Declare(
    flecs
    GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
    GIT_TAG master
)
set(FLECS_SHARED OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(flecs)

FetchContent_Declare(
    HandmadeMath
    GIT_REPOSITORY https://github.com/HandmadeMath/HandmadeMath.git
    GIT_TAG master
)
FetchContent_MakeAvailable(HandmadeMath)

add_executable(game
    src/main.c
    src/core/sokol_impl.c
    src/core/renderer/renderer.c
    src/core/renderer/meshes/primitives.c
    src/core/renderer/resources/mesh.c
    src/core/renderer/resources/instance.c
    src/core/renderer/resources/material.c
    src/core/renderer/resources/texture.c
    src/core/renderer/resources/camera.c
    src/core/renderer/file_loaders/stbi_impl.c
    src/core/renderer/file_loaders/file_loaders.c
)

target_include_directories(game PRIVATE
    ${sokol_SOURCE_DIR}
    ${stb_SOURCE_DIR}
    "${CMAKE_BINARY_DIR}/_deps/handmademath-src/"
)

if(WIN32)
    target_link_libraries(game PRIVATE 
        kernel32
        user32
        shell32
        gdi32
        opengl32)
elseif(UNIX AND NOT APPLE)
    target_link_libraries(game PRIVATE
        m
        X11
        Xi
        Xcursor
    )
endif()

target_link_libraries(game PRIVATE
    flecs::flecs_static
    OpenGL::GL
)