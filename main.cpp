#include "global.h"
#include <iostream>
using namespace std;


int main(int argc, char** argv) {
	printf("hello world\n");
	Screen::begin();

	
	Screen::mainloop();
	return Screen::quit();
}