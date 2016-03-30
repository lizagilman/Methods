#include "Label.h"



Label::Label(string text,COORD coord, CONSOLE_CURSOR_INFO cci, DWORD wAttr): _coord(coord), _cci(cci), _wAttr(wAttr)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, _coord);
	SetConsoleCursorInfo(h, & _cci);
	SetConsoleTextAttribute(h, _wAttr);
	cout << text << endl;
}


Label::~Label()
{
}

