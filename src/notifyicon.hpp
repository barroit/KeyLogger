#pragma once

#define TRAY_MSG	(WM_APP + 1)

#define BTNID_CLOSE	1001
#define BTNIDX_CLOSE	0

NOTIFYICONDATA init_notifyicon_data(HWND hwnd);

LRESULT handle_notifyicon_message(HWND hwnd, UINT msg);

LRESULT handle_systray_mii_selected(HWND hwnd, HMENU hmenu, UINT iidx);