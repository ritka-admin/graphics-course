set(SRCS
    main.cpp
    mondelbrot.cpp
    mondelbrot.cpp

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

#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)