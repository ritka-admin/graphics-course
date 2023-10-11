set(SRCS
    main.cpp
    mondelbrot.cpp
    mondelbrot.h

    shaders.qrc
    Shaders/mondelbrot.fs
    Shaders/mondelbrot.vs
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(demo-app ${SRCS})

target_link_libraries(demo-app
    PRIVATE
        Qt5::Widgets
        FGL::Base
)
