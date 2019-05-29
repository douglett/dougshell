# GCC_OPTS=-static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic
SDL = C:/MinGW64/devlibs/SDL-1.2.15
OUT = main.exe
SRC = src/main.cpp
HEAD = src/global.h src/display.hpp src/canvas.hpp

$(OUT): $(SRC) $(HEAD)
	g++ -std=c++11 -Wall -m32 -o $(OUT) \
		-I$(SDL)/include \
		-L$(SDL)/lib \
		$(SRC) \
		-lmingw32 -lSDLmain -lSDL -mwindows -mconsole

# compile1: $(SRC) $(HEAD)
# 	g++ -std=c++14 -Wall -m32 -o $(OUT) \
# 		-I$(SDL)/include \
# 		-L$(SDL)/lib \
# 		$(SRC) \
# 		-DNO_STDIO_REDIRECT sdlmain.cpp \
# 		-lmingw32 -lSDL -mwindows -mconsole

# compile2: $(SRC) $(HEAD)
# 	g++ -std=c++11 -Wall -m32 -o $(OUT) \
# 		-I$(SDL)/include \
# 		-L$(SDL)/lib \
# 		$(SRC) \
# 		-lmingw32 -lSDLmain -lSDL -mwindows -mconsole

run: $(OUT)
	./$(OUT)

clean:
	rm -f *.o *.exe