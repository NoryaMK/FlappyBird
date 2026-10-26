cmake_minimum_required(VERSION 3.16)

project(FlappyBird
        VERSION 1.0.0
        DESCRIPTION "A Flappy Bird clone written in modern C++ with SFML"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(FLAPPY_FETCH_SFML "If SFML is not installed, download and build it automatically" ON)

# ---------------------------------------------------------------- dependencies
find_package(SFML 2.6 COMPONENTS graphics window system QUIET)

if(NOT SFML_FOUND AND FLAPPY_FETCH_SFML)
    message(STATUS "SFML not found locally - fetching SFML 2.6.2 from GitHub")
    include(FetchContent)
    set(SFML_BUILD_AUDIO   OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_DOC     OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        2.6.2
        GIT_SHALLOW    TRUE)
    FetchContent_MakeAvailable(SFML)
elseif(NOT SFML_FOUND)
    message(FATAL_ERROR "SFML 2.6 not found. Install it or re-run with -DFLAPPY_FETCH_SFML=ON")
endif()

# --------------------------------------------------------------------- target
set(FLAPPY_SOURCES
    src/main.cpp
    src/Game.cpp
    src/StateMachine.cpp
    src/MenuState.cpp
    src/PlayState.cpp
    src/GameOverState.cpp
    src/Bird.cpp
    src/Pipe.cpp
    src/PipeManager.cpp
    src/Background.cpp
    src/ScoreBoard.cpp
    src/DigitRenderer.cpp
    src/TextRenderer.cpp
    src/ResourceManager.cpp
    src/Random.cpp
)

add_executable(flappybird ${FLAPPY_SOURCES})

target_include_directories(flappybird PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(flappybird PRIVATE sfml-graphics sfml-window sfml-system)

if(MSVC)
    # 源码为 UTF-8（含中文注释），中文 Windows 下 MSVC 默认按 GBK 读取会解析出错
    target_compile_options(flappybird PRIVATE /W4 /utf-8)
else()
    target_compile_options(flappybird PRIVATE -Wall -Wextra -Wpedantic)
endif()

# 把 assets 复制到可执行文件旁边，方便直接运行
add_custom_command(TARGET flappybird POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:flappybird>/assets)

install(TARGETS flappybird RUNTIME DESTINATION bin)
