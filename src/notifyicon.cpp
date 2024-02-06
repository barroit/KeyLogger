#include "notifyicon.hpp"
#include <strsafe.h>
#include "config.hpp"

NOTIFYICONDATA init_notifyicon_data(HWND hwnd)
{
	NOTIFYICONDATA nid = { };

	nid.cbSize = sizeof(NOTIFYICONDATA);

	nid.hWnd = hwnd;
	nid.uID = 0;

	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_SHOWTIP;

	nid.uVersion = NOTIFYICON_VERSION_4;
	nid.uCallbackMessage = TRAY_MSG; // Message identifier
	StringCchCopy(nid.szTip, ARRAYSIZE(nid.szTip), TEXT("KeyLogger - " VERSION_MAJOR "." VERSION_MINOR "." VERSION_PATCH));

	return nid;
}

LRESULT handle_notifyicon_message(HWND hwnd, UINT msg)
{
	if (!(msg == WM_CONTEXTMENU || msg == NIN_KEYSELECT || msg == NIN_SELECT))
	{
		return 1;
	}

	POINT pt;
	GetCursorPos(&pt);

	MENUITEMINFO mii{ };

	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_TYPE | MIIM_ID;
	mii.fType = MFT_STRING;
	mii.wID = BTNID_CLOSE;
	mii.dwTypeData = TEXT("Close");
	mii.cch = lstrlen(mii.dwTypeData);

	HMENU hmenu = CreatePopupMenu();
	if (hmenu == NULL)
	{
		return 1;
	}

	MENUINFO mi{ };
	mi.cbSize = sizeof(MENUINFO);
	mi.fMask = MIM_STYLE;
	mi.dwStyle = MNS_NOTIFYBYPOS;

	if (SetMenuInfo(hmenu, &mi) == FALSE)
	{
		return 1;
	}

	if (InsertMenuItem(hmenu, BTNIDX_CLOSE, TRUE, &mii) == FALSE)
	{
		return 1;
	}

	SetForegroundWindow(hwnd);
	TrackPopupMenu(hmenu, TPM_LEFTBUTTON, pt.x, pt.y, 0, hwnd, NULL);

	DestroyMenu(hmenu);

	return 0;
}

LRESULT handle_systray_mii_selected(HWND hwnd, [[maybe_unused]] HMENU hmenu, UINT iidx)
{
	switch (iidx)
	{
	case BTNIDX_CLOSE:
		DestroyWindow(hwnd);
	}

	return 0;
}