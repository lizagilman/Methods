
#include <windows.h>
#include <stdio.h>
#include <string>
#include <iostream>

HANDLE hStdin;
DWORD fdwSaveOldMode;

VOID ErrorExit(LPSTR);
VOID KeyEventProc(KEY_EVENT_RECORD);
VOID MouseEventProc(MOUSE_EVENT_RECORD);
VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);

using namespace std;

static string myOptions[4] = { "[ ] option A\n","[ ] option B\n","[ ] option C\n","[ ] option D\n" };


int main(VOID)
{	
	//create frame
	int width, high;
	width = 15;
	high = 6;
	for (int rows = 0; rows < high; rows++) {
		for (int col = 0; col < width; col++) {
			if (col == 0||col== (width-1)||rows==0||(rows==high-1)) {
				printf("*");
			}
			else { 
				printf(" "); 
			}
		}
		printf("\n");
	}
	COORD c = { 1, 1 };
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	//creating the options
	
	//COLOR THE FIRST LINE IN YELLOW
	DWORD wAttr = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
	SetConsoleTextAttribute(h, wAttr);
	SetConsoleCursorPosition(h, c);
	cout<< myOptions[0];
	
	//COLOR THE OTHER LINES IN GREEN
	wAttr = FOREGROUND_GREEN ;
	SetConsoleTextAttribute(h, wAttr);
	c = { 1, 2 };
	SetConsoleCursorPosition(h, c);
	cout << myOptions[1];

	c = { 1, 3 };
	SetConsoleCursorPosition(h, c);
	cout<<myOptions[2];
	
	c = { 1, 4 };
	SetConsoleCursorPosition(h, c);
	cout << myOptions[3];

	//the position of the cursor after printing
	c = { 1,1 };
	SetConsoleCursorPosition(h, c);



	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];
	int counter = 0;

	// Get the standard input handle. 

	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit("GetStdHandle");

	// Save the current input mode, to be restored on exit. 

	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		ErrorExit("GetConsoleMode");

	// Enable the window and mouse input events. 

	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit("SetConsoleMode");

	// Loop to read and handle the next 100 input events. 

	while (counter++ <= 900)
	{
		// Wait for the events. 

		if (!ReadConsoleInput(
			hStdin,      // input buffer handle 
			irInBuf,     // buffer to read into 
			256,         // size of read buffer 
			&cNumRead)) // number of records read 
			ErrorExit("ReadConsoleInput");

		// Dispatch the events to the appropriate handler. 

		for (i = 0; i < cNumRead; i++)
		{
			
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input 
				KeyEventProc(irInBuf[i].Event.KeyEvent);

				break;

			case MOUSE_EVENT: // mouse input 
				MouseEventProc(irInBuf[i].Event.MouseEvent);
				break;

			case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
				ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
				break;

			case FOCUS_EVENT:  // disregard focus events 

			case MENU_EVENT:   // disregard menu events 
				break;

			default:
				ErrorExit("Unknown event type");
				break;
			}
		}
	}

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	return 0;
}

VOID ErrorExit(LPSTR lpszMessage)
{
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	ExitProcess(0);
}
static bool arr[4] = { false,false,false,false };

static COORD coord2 = { 1,1 };
VOID KeyEventProc(KEY_EVENT_RECORD ker) /////////////////////////////////KEYBORAD//////////////////
{	
	//printf("%d", ker.wVirtualKeyCode);
	static int counter = 0;

	counter++;
	if (counter % 2 == 0) {
		return;
	}
	
	char c = ker.uChar.AsciiChar;

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	
	
	//printf("Key event: ");
	
	//move down
	if (c == 's') {
		if (coord2.Y < 4) {
			//color the previous line from yellow to green
			DWORD wAttr = FOREGROUND_GREEN;
			SetConsoleTextAttribute(h, wAttr);
			cout << myOptions[coord2.Y-1];
			

			//COLOR THE CURRENT LINE TO YELLOW
			coord2.Y = coord2.Y + 1;
			SetConsoleCursorPosition(h, coord2);
			wAttr = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
			SetConsoleTextAttribute(h, wAttr);
			
			cout << myOptions[coord2.Y-1];
			SetConsoleCursorPosition(h, coord2);
			//color//
			
			
			//printf("test");
		}
		else { //coord2.Y == 4 ==last line
			//color the last line from yellow to green
			return;
			//DWORD wAttr = FOREGROUND_GREEN;
			//SetConsoleTextAttribute(h, wAttr);
			//cout << myOptions[coord2.Y - 1];

			//COLOR THE first LINE TO YELLOW
			//coord2.Y = 0;
			//SetConsoleCursorPosition(h, coord2);
			//wAttr = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
			//cout << myOptions[coord2.Y-1];
			//SetConsoleCursorPosition(h, coord1);
		}
		//printf("my Y : %d", coord1.Y);
	
	}
	//move up
	if (c == 'w') {
		if (coord2.Y != 1) {
			DWORD wAttr = FOREGROUND_GREEN;
			SetConsoleTextAttribute(h, wAttr);
			cout << myOptions[coord2.Y - 1];
			
			//going up
			coord2.Y--;
			SetConsoleCursorPosition(h, coord2);
			wAttr = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
			SetConsoleTextAttribute(h, wAttr);
			cout << myOptions[coord2.Y - 1];
			SetConsoleCursorPosition(h, coord2);


		}
		else {
			return;
		
		}

		//printf("x\n");
		SetConsoleCursorPosition(h, coord2);
	}
	//printf("the key is: %d", c);
	//printf("\n)");
	if (c == 'x') {
		coord2.X = coord2.X++;
		SetConsoleCursorPosition(h, coord2);

		if (arr[coord2.Y - 1] == false) {
			printf("x");

			arr[coord2.Y - 1]=true;
		}
		else {
			arr[coord2.Y - 1] = false;
			printf(" ");
		
		}

		coord2.X--;
		SetConsoleCursorPosition(h, coord2);
	}
	if(c=='a'){
		//printf("this is a");
		coord2 = { 2, 1 };
		SetConsoleCursorPosition(h, coord2);
	}
	if (c == 'b') {
		coord2 = { 2, 2 };
		SetConsoleCursorPosition(h, coord2);
		//printf("this is z");
	}
	if (c == 'c') {
		coord2 = { 2, 3 };
		SetConsoleCursorPosition(h, coord2);
		//printf("this is z");
	}


	

	//if (ker.bKeyDown)
	//	printf("key pressed\n");
//	else printf("key released\n");
}

VOID MouseEventProc(MOUSE_EVENT_RECORD mer)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
	//printf("Mouse event: ");
	
	
	
	switch (mer.dwEventFlags)
	{
	case 0:
						/////////////////////////////////////////////////////////////////////////////////////
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			
			//printf("right button press \n");
			COORD mouseCoord = mer.dwMousePosition;
			//onlt move in Y axis
			if (mouseCoord.X == 2) {
				HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleCursorPosition(h, mouseCoord);
				///////////////////////////////////////////////////////////////////////////////////
				if (arr[mouseCoord.Y - 1] == false) {
					printf("x");
					arr[mouseCoord.Y - 1] = true;
				}
				else {
					arr[mouseCoord.Y - 1] = false;
					printf(" ");
				}
				SetConsoleCursorPosition(h, mouseCoord);
			}
			

		}
		else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			
			COORD mouseCoord = mer.dwMousePosition;


		}
		else
		{
			//printf("button press\n");
		}
		break;
	case DOUBLE_CLICK:
		//printf("double click\n");
		break;
	case MOUSE_HWHEELED:
		//printf("horizontal mouse wheel\n");
		break;
	case MOUSE_MOVED:
	//	printf("mouse moved\n");
		break;
	case MOUSE_WHEELED:
		//printf("vertical mouse wheel\n");
		break;
	default:
	//	printf("unknown\n");
		break;
	}
}

VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
	printf("Resize event\n");
	printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);
}
