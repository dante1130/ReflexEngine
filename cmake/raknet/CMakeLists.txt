project(raknet)

add_library(raknet STATIC
    RakString.cpp
    BitStream.cpp
    RakNetTypes.cpp
    RakSleep.cpp
    Gets.cpp
)
target_include_directories(raknet PUBLIC .)
target_link_libraries(raknet PRIVATE glfw glad ${APP_SERVICES_LIBRARY} ${COCOA_LIBRARY})
