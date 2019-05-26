# GCC_OPTS=-static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic
SDL = C:/MinGW/devlibs/SDL-1.2.15
OUT = main.exe
SRC = main.cpp screen.cpp
HEAD = global.h canvas.hpp

$(OUT): $(SRC) $(HEAD)
	g++ -std=c++14 -Wall -m32 -o $(OUT) \
		-I$(SDL)/include \
		-L$(SDL)/lib \
		$(SRC) \
		-DNO_STDIO_REDIRECT sdlmain.cpp \
		-lmingw32 -lSDL -mwindows -mconsole

test2:
	g++ -std=c++11 -Wall -m32 -o $(OUT) \
		-I$(SDL)/include \
		-L$(SDL)/lib \
		$(SRC) \
		-lmingw32 -lSDLmain -lSDL -mwindows -mconsole

run: $(OUT)
	./$(OUT)
