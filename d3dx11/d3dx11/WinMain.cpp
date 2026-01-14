#include <Windows.h>


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
	wc.lpfnWndProc = DefWindowProc;	//default pointer to message function for window (draw message) (important!)
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
	

	while (true);
	return 0;
}