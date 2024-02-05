#include "notifyicon.hpp"
#include <strsafe.h>

NOTIFYICONDATA init_notifyicon_data(HWND hwnd)
{
	NOTIFYICONDATA nid = { };

	nid.cbSize = sizeof(nid);

	nid.hWnd = hwnd;
	nid.uID = 0;

	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;

	nid.uVersion = NOTIFYICON_VERSION_4;

	nid.uCallbackMessage = TRAY_MSG; // Message identifier

	StringCchCopy(nid.szTip, ARRAYSIZE(nid.szTip), L"Logging keystroke");

	return nid;
}