#include "Window.h" 

Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() noexcept
	:
	hInst(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);			//struct size
	wc.style = CS_OWNDC;			//class style (used device context, every window gets own device context)
	wc.lpfnWndProc = HandleMsgSetup;//pointer to procedure function for window (i.e. draw, quit) (important!)
	wc.cbClsExtra = 0;				//allocate extra bytes, 0 - not needed
	wc.hInstance = GetInstance();	//hinstance
	wc.hIcon = nullptr;				//default icon
	wc.hCursor = nullptr;			//default
	wc.hbrBackground = nullptr;		//default - window does not draw background
	wc.lpszMenuName = nullptr;		//default
	wc.lpszClassName = GetName();	//class name of window 
	wc.hIconSm = nullptr;			//icon - default
	RegisterClassEx(&wc);
}

//destructor to destroy window when not needed
Window::WindowClass::~WindowClass()
{
	UnregisterClass(wndClassName, GetInstance());
}

const wchar_t* Window::WindowClass::GetName() noexcept
{
	return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	return wndClass.hInst;
}

//window constructor using wi
Window::Window(int width, int height, const wchar_t* name) noexcept
{
	//calculate window size based on client region size
	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
	//create window and get hWnd
	hWnd = CreateWindow(
		WindowClass::GetName(), name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, WindowClass::GetInstance(), this //pointer to window instance, connects to procedure function
	);
	//show window
	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

//procedure function for window to set up window, passes message to message handling procedure
LRESULT WINAPI Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	//use create paramter pass in from CreateWindow() to store window class pointer
	if (msg == WM_NCCREATE)
	{
		//Extract ptr to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		//set WinAPI-managed user data to store ptr to window class
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		//set message proc to normal handler now that setup is finished
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
		//forward message to window class handler
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);

	}
	//handle w default handler if message recived before WM_NCCREATE message
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


//procdure function to pass pointer to message handler procedure function
//(adapter from winapi to c++ function)
LRESULT WINAPI Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	//retrieve ptr to window class from win32
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	//forward message to window class handler
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}


//message handler procedure function
LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{
		//window close
	case WM_CLOSE:
		PostQuitMessage(0);
		//returns 0 to activate windows destructor
		return 0;
	}

	//handle other messages using default windows procedure
	return DefWindowProc(hWnd, msg, wParam, lParam);
}