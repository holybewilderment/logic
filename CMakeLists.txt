cmake_minimum_required(VERSION 3.15)

project(logic-game)

add_executable(logic-game)

include_directories(${CMAKE_SOURCE_DIR}/include)

# мы любим древние хламовые маки (да и современные тоже)
if(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.7")
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
    target_link_libraries(logic-game ${CMAKE_SOURCE_DIR}/lib/macos/libraylib.a "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
endif()

target_sources(logic-game PRIVATE src/main.c src/player.c)
