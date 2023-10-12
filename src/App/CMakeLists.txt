set(SRCS
    main.cpp
    Mandelbrot.cpp
    Mandelbrot.h

    shaders.qrc
    Shaders/mandelbrot.fs
    Shaders/mandelbrot.vs
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(demo-app ${SRCS})

target_link_libraries(demo-app
    PRIVATE
        Qt5::Widgets
        FGL::Base
)
