
#include <windows.h>
#include <stdio.h>


HANDLE hStdin;
DWORD fdwSaveOldMode;

VOID ErrorExit(LPSTR);
VOID KeyEventProc(KEY_EVENT_RECORD);
VOID MouseEventProc(MOUSE_EVENT_RECORD);
VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);



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
	SetConsoleCursorPosition(h, c);
	printf("[ ] option A\n");
	
	c = { 1, 2 };
	SetConsoleCursorPosition(h, c);
	printf("[ ] option B\n");

	c = { 1, 3 };
	SetConsoleCursorPosition(h, c);
	printf("[ ] option C\n");
	
	c = { 1, 4 };
	SetConsoleCursorPosition(h, c);
	printf("[ ] option D\n");

	
	c = { 2,1 };
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
VOID KeyEventProc(KEY_EVENT_RECORD ker)
{	
	//printf("%d", ker.wVirtualKeyCode);
	static int counter = 0;
	counter++;
	if (counter % 2 == 0) {
		return;
	}
	
	int c = ker.uChar.AsciiChar;

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	
	static COORD coord1 = { 2,1 };
	//printf("Key event: ");
	
	//move down
	if (c == 's') {
		if (coord1.Y != 4) {
			coord1.Y = coord1.Y + 1;
			SetConsoleCursorPosition(h, coord1);
		}
		else {
			coord1.Y = 1;
			SetConsoleCursorPosition(h, coord1);
		}
		//printf("my Y : %d", coord1.Y);
	
	}
	//move up
	if (c == 'w') {
		if (coord1.Y != 1) {
			coord1.Y--;
			SetConsoleCursorPosition(h, coord1);
		}
		else {
			coord1.Y = 4;
			SetConsoleCursorPosition(h, coord1);
		
		}

		//printf("x\n");
		SetConsoleCursorPosition(h, coord1);
	}
	//printf("the key is: %d", c);
	//printf("\n)");
	if (c == 'x') {
		if (arr[coord1.Y - 1] == false) {
			printf("x");
			arr[coord1.Y - 1]=true;
		}
		else {
			arr[coord1.Y - 1] = false;
			printf(" ");
		
		}

		
		SetConsoleCursorPosition(h, coord1);
	}
	if(c=='a'){
		//printf("this is a");
		 coord1 = { 2, 1 };
		SetConsoleCursorPosition(h, coord1);
	}
	if (c == 'b') {
		coord1 = { 2, 2 };
		SetConsoleCursorPosition(h, coord1);
		//printf("this is z");
	}
	if (c == 'c') {
		coord1 = { 2, 3 };
		SetConsoleCursorPosition(h, coord1);
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
