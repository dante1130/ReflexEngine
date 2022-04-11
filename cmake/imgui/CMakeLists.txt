project(imgui)

add_library(imgui STATIC
    imgui.cpp
    imgui_draw.cpp
    imgui_widgets.cpp
    imgui_demo.cpp
    examples/imgui_impl_glfw.cpp
    examples/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC .)
target_link_libraries(imgui PRIVATE glfw glad ${APP_SERVICES_LIBRARY} ${COCOA_LIBRARY})
