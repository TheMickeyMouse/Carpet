gcc -c imgui.cpp imgui_demo.cpp imgui_draw.cpp imgui_impl_glfw.cpp imgui_impl_opengl3.cpp imgui_stdlib.cpp imgui_tables.cpp imgui_widgets.cpp ^
-I..\..\..\..\Dependencies\GLFW\include -L..\..\..\..\Dependencies\GLFW\lib-mingw-w64 -l:libglfw.a -O3
move *.o obj\
cd obj
ar -rcs libimgui.a imgui.o imgui_demo.o imgui_draw.o imgui_impl_glfw.o imgui_impl_opengl3.o imgui_stdlib.o imgui_tables.o imgui_widgets.o
move libimgui.a ..\lib\
pause