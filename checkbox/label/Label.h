#include <Windows.h>
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;
#pragma once
class Label
{
	COORD _coord;
	HANDLE _h;
	CONSOLE_CURSOR_INFO _cci;
	DWORD _wAttr;


public:
	
	Label(string text,COORD coord, CONSOLE_CURSOR_INFO cci, DWORD wAttr);
	~Label();

};