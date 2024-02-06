#include "window.hpp"
#include "notifyicon.hpp"

WNDCLASS init_window_class(HINSTANCE instance, const wchar_t *class_name)
{
	WNDCLASS wc{ };

	wc.lpfnWndProc = window_proc;
	wc.hInstance = instance;
	wc.lpszClassName = class_name;

	return wc;
}

HWND create_window_handler(const wchar_t *class_name, const wchar_t *window_text, HINSTANCE instance)
{
	HWND hwnd = CreateWindowEx(
		0,			// Optional window styles.
		class_name,		// Window class
		window_text,		// Window text
		WS_OVERLAPPEDWINDOW,	// Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,		// Parent window
		NULL,		// Menu
		instance,	// Instance handle
		NULL		// Additional application data
	);

	return hwnd;
}

LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case TRAY_MSG:
		return handle_notifyicon_message(hwnd, LOWORD(lp));
	case WM_MENUCOMMAND:
		return handle_systray_mii_selected(hwnd, (HMENU)lp, (UINT)wp);
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wp, lp);
}

LRESULT CALLBACK low_level_keyboard_proc(int code, WPARAM wp, LPARAM lp)
{
	if (code != HC_ACTION)
	{
		return CallNextHookEx(NULL, code, wp, lp);
	}

	// KBDLLHOOKSTRUCT p = (KBDLLHOOKSTRUCT)lParam;
	// switch(wParam)
	// {
	// 	case WM_KEYDOWN:
	// 	case WM_SYSKEYDOWN:
	// }

	return 0;
}