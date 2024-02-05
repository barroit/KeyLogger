#include "window.hpp"
#include "notifyicon.hpp"

WNDCLASS init_window_class(HINSTANCE hInstance, const wchar_t *CLASS_NAME)
{
	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	return wc;
}

HWND create_window_handler(const wchar_t *CLASS_NAME, const wchar_t *WINDOW_TEXT, HINSTANCE hInstance)
{
	HWND hwnd = CreateWindowEx(
		0,			// Optional window styles.
		CLASS_NAME,		// Window class
		WINDOW_TEXT,		// Window text
		WS_OVERLAPPEDWINDOW,	// Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,		// Parent window
		NULL,		// Menu
		hInstance,	// Instance handle
		NULL		// Additional application data
	);

	return hwnd;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case TRAY_MSG:
			return 0;
		case WM_CLOSE:
			DestroyWindow(hwnd);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}