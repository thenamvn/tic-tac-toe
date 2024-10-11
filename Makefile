all:
	g++ -I SDL2/include -I SDL2_ttf/include -L SDL2/lib -L SDL2_ttf/lib -o main main.cpp caro.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
clean:
	del main.exe