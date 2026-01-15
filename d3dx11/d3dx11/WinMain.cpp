#include <Windows.h>


//Custom Windows procedure for terminating when closing window
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:			 //on window close
		PostQuitMessage(69); //post exit code
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,		//string holding command line inputs
	int       nCmdShow)			//shows window

{
	const auto pClassName = L"saffcon";
	//Register window class

	//configure structure for window class 
	WNDCLASSEX wc = { 0 };			//init 0
	wc.cbSize = sizeof(wc);			//struct size
	wc.style = CS_OWNDC;			//class style (used device context, every window gets own device context)
	wc.lpfnWndProc = WndProc;		//pointer to procedure function for window (i.e. draw, quit) (important!)
	wc.cbClsExtra = 0;				//allocate extra bytes, 0 - not needed
	wc.hInstance = hInstance;		//hinstance
	wc.hIcon = nullptr;				//default icon
	wc.hCursor = nullptr;			//default
	wc.hbrBackground = nullptr;		//default - window does not draw background
	wc.lpszMenuName = nullptr;		//default
	wc.lpszClassName = pClassName;	//class name of window 
	wc.hIconSm = nullptr;			//icon - default

	RegisterClassEx(&wc);			//register pointer to window

	//Create Window instance (createwindowexA) 
	//returns handle 
	HWND hWnd = CreateWindowEx(
		0, pClassName,
		L"Happy Window",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, //window styles
		200, 200, 640, 480,						  //window position and size
		nullptr, nullptr, hInstance, nullptr
	);

	
	//show window command
	ShowWindow(hWnd, SW_SHOW);

	//message pump
	MSG msg;
	BOOL gResult;
	while (gResult = GetMessage(&msg, nullptr, 0, 0) > 0) //>0 if msg!= quit, ==0 if quit, ==-1 if error, (0, 0) = get all messages
	{
		TranslateMessage(&msg);	//process message
		DispatchMessage(&msg);  //pass message to windowproc

	}

	//process gResult
	//-1 if error, 0 if quit, stays in loop above if >0
	if (gResult == -1) 
	{
		return -1;
	}
	else {
		return msg.wParam; //return quit code (69)
	}
}