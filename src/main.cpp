#include "window.hpp"
#include "notifyicon.hpp"
#include <commctrl.h>
#include "resource.hpp"

const wchar_t *CLASS_NAME = L"Key Logger", *WINDOW_TEXT = L"Log Keys";

int WINAPI wWinMain(HINSTANCE hInstance, [[maybe_unused]] HINSTANCE hPrevInstance, [[maybe_unused]] PWSTR pCmdLine, [[maybe_unused]] int nCmdShow)
{
	WNDCLASS wc;
	HWND hwnd;

	wc = init_window_class(hInstance, CLASS_NAME);
	RegisterClass(&wc);

	if ((hwnd = create_window_handler(CLASS_NAME, WINDOW_TEXT, hInstance)) == NULL)
	{
		return 1;
	}

	ShowWindow(hwnd, SW_HIDE);

	NOTIFYICONDATA nid;

	nid = init_notifyicon_data(hwnd);
	if (FAILED(LoadIconMetric(hInstance, MAKEINTRESOURCE(OIC_TRAY_ICON), LIM_SMALL, &nid.hIcon)))
	{
		return 1;
	}

	BOOL br;
	if ((br = Shell_NotifyIcon(NIM_ADD, &nid)) != TRUE)
	{
		return 1;
	}
	// Must be called every time a notification area icon is added
	if ((br = Shell_NotifyIcon(NIM_SETVERSION, &nid)) != TRUE)
	{
		return 1;
	}

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	DestroyIcon(nid.hIcon);

	return 0;
}