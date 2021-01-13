#include <iostream>
#include <fstream>
#include <Windows.h>
#include "classes.h"
using namespace std;

int main()
{
	setlocale(0, "");
	SetConsoleTitle("Black Box");
	
	Game game;
	game.Start_Game();

	return 0;
}
