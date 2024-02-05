#pragma once

WNDCLASS init_window_class(HINSTANCE hInstance, const wchar_t *CLASS_NAME);

HWND create_window_handler(const wchar_t *CLASS_NAME, const wchar_t *WINDOW_TEXT, HINSTANCE hInstance);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);