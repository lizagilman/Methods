#include <Windows.h>
#include <stdio.h>
#include "Label.h"


int main() {

	COORD c = { 15, 15 };
	CONSOLE_CURSOR_INFO cci = { 100, TRUE };
	DWORD wAttr = FOREGROUND_GREEN |FOREGROUND_INTENSITY;
	Label label("My Label",c, cci, wAttr);
	getchar();


}