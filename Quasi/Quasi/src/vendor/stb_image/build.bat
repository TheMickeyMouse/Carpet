gcc -c stb_image.cpp -O3

move *.o obj\
cd obj
ar -rcs libstbimage.a stb_image.o
move libstbimage.a ..\lib\
pause