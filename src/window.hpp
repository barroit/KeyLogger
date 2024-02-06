#pragma once

WNDCLASS init_window_class(HINSTANCE instance, const wchar_t *class_name);

HWND create_window_handler(const wchar_t *class_name, const wchar_t *window_text, HINSTANCE instance);

LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

LRESULT CALLBACK low_level_keyboard_proc(int code, WPARAM wp, LPARAM lp);