add_executable(ggwave-quiet main.cpp)

target_include_directories(ggwave-quiet PRIVATE
    ..
    ${SDL2_INCLUDE_DIRS}
    )

target_link_libraries(ggwave-quiet PRIVATE
    ggwave
    ggwave-common
    ggwave-common-sdl2
    ${CMAKE_THREAD_LIBS_INIT}
    )
