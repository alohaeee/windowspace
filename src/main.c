#include <stdio.h>
#include <Windows.h>
#include <Shellapi.h>
#include <Psapi.h>
#include <dwmapi.h>
#define CORE__IMPLEMENTATION
#include "Core.h"
#include "main.h"
#include "tomlc17.h"

#define MAX_WND_NAME_LENGTH 512

#pragma comment(lib, "Dwmapi.lib")
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Advapi32.lib")

// TODO:
// * Loggin into file
// * Query command list
// * fuzzy find command

B32 key_string_to_virtual_key(const char* key, U32 key_len, U8* keycode) {
	typedef struct {
		const char* name;
		BYTE        vk;
	} KeyMapping;

	static const KeyMapping key_map[] = {
		{"ctrl", VK_CONTROL},
		{"lctrl", VK_LCONTROL},
		{"rctrl", VK_RCONTROL},
		{"lshift", VK_LSHIFT},
		{"rshift", VK_RSHIFT},
		{"shift", VK_SHIFT},
		{"alt", VK_MENU},
		{"lalt", VK_LMENU},
		{"ralt", VK_RMENU},
		{"win", VK_LWIN},
		{"lwin", VK_LWIN},
		{"rwin", VK_RWIN},

		{"f1", VK_F1},
		{"f2", VK_F2},
		{"f3", VK_F3},
		{"f4", VK_F4},
		{"f5", VK_F5},
		{"f6", VK_F6},
		{"f7", VK_F7},
		{"f8", VK_F8},
		{"f9", VK_F9},
		{"f10", VK_F10},
		{"f11", VK_F11},
		{"f12", VK_F12},
		{"f13", VK_F13},
		{"f14", VK_F14},
		{"f15", VK_F15},
		{"f16", VK_F16},
		{"f17", VK_F17},
		{"f18", VK_F18},
		{"f19", VK_F19},
		{"f20", VK_F20},
		{"f21", VK_F21},
		{"f22", VK_F22},
		{"f23", VK_F23},
		{"f24", VK_F24},

		{"escape", VK_ESCAPE},
		{"esc", VK_ESCAPE},
		{"enter", VK_RETURN},
		{"return", VK_RETURN},
		{"space", VK_SPACE},
		{"tab", VK_TAB},
		{"backspace", VK_BACK},
		{"back", VK_BACK},
		{"delete", VK_DELETE},
		{"del", VK_DELETE},
		{"insert", VK_INSERT},
		{"ins", VK_INSERT},
		{"home", VK_HOME},
		{"end", VK_END},
		{"pageup", VK_PRIOR},
		{"pgup", VK_PRIOR},
		{"pagedown", VK_NEXT},
		{"pgdn", VK_NEXT},
		{"pause", VK_PAUSE},
		{"break", VK_PAUSE},
		{"capslock", VK_CAPITAL},
		{"caps", VK_CAPITAL},
		{"numlock", VK_NUMLOCK},
		{"scrolllock", VK_SCROLL},
		{"scroll", VK_SCROLL},
		{"printscreen", VK_SNAPSHOT},
		{"print", VK_SNAPSHOT},

		{"up", VK_UP},
		{"down", VK_DOWN},
		{"left", VK_LEFT},
		{"right", VK_RIGHT},

		{"0", 0x30},
		{"1", 0x31},
		{"2", 0x32},
		{"3", 0x33},
		{"4", 0x34},
		{"5", 0x35},
		{"6", 0x36},
		{"7", 0x37},
		{"8", 0x38},
		{"9", 0x39},

		{"a", 0x41},
		{"b", 0x42},
		{"c", 0x43},
		{"d", 0x44},
		{"e", 0x45},
		{"f", 0x46},
		{"g", 0x47},
		{"h", 0x48},
		{"i", 0x49},
		{"j", 0x4A},
		{"k", 0x4B},
		{"l", 0x4C},
		{"m", 0x4D},
		{"n", 0x4E},
		{"o", 0x4F},
		{"p", 0x50},
		{"q", 0x51},
		{"r", 0x52},
		{"s", 0x53},
		{"t", 0x54},
		{"u", 0x55},
		{"v", 0x56},
		{"w", 0x57},
		{"x", 0x58},
		{"y", 0x59},
		{"z", 0x5A},

		{"numpad0", VK_NUMPAD0},
		{"numpad1", VK_NUMPAD1},
		{"numpad2", VK_NUMPAD2},
		{"numpad3", VK_NUMPAD3},
		{"numpad4", VK_NUMPAD4},
		{"numpad5", VK_NUMPAD5},
		{"numpad6", VK_NUMPAD6},
		{"numpad7", VK_NUMPAD7},
		{"numpad8", VK_NUMPAD8},
		{"numpad9", VK_NUMPAD9},
		{"multiply", VK_MULTIPLY},
		{"add", VK_ADD},
		{"subtract", VK_SUBTRACT},
		{"decimal", VK_DECIMAL},
		{"divide", VK_DIVIDE},
		{"num*", VK_MULTIPLY},
		{"num+", VK_ADD},
		{"num-", VK_SUBTRACT},
		{"num.", VK_DECIMAL},
		{"num/", VK_DIVIDE},

		{";", VK_OEM_1},
		{"semicolon", VK_OEM_1},
		{"=", VK_OEM_PLUS},
		{"plus", VK_OEM_PLUS},
		{"equal", VK_OEM_PLUS},
		{",", VK_OEM_COMMA},
		{"comma", VK_OEM_COMMA},
		{"-", VK_OEM_MINUS},
		{"minus", VK_OEM_MINUS},
		{".", VK_OEM_PERIOD},
		{"period", VK_OEM_PERIOD},
		{"/", VK_OEM_2},
		{"slash", VK_OEM_2},
		{"`", VK_OEM_3},
		{"grave", VK_OEM_3},
		{"tilde", VK_OEM_3},
		{"[", VK_OEM_4},
		{"lbracket", VK_OEM_4},
		{"\\", VK_OEM_5},
		{"backslash", VK_OEM_5},
		{"]", VK_OEM_6},
		{"rbracket", VK_OEM_6},
		{"'", VK_OEM_7},
		{"quote", VK_OEM_7},
		{"apostrophe", VK_OEM_7},

		{"lbutton", VK_LBUTTON},
		{"rbutton", VK_RBUTTON},
		{"mbutton", VK_MBUTTON},
		{"xbutton1", VK_XBUTTON1},
		{"xbutton2", VK_XBUTTON2},

		{"volumeup", VK_VOLUME_UP},
		{"volumedown", VK_VOLUME_DOWN},
		{"volumemute", VK_VOLUME_MUTE},
		{"mute", VK_VOLUME_MUTE},
		{"medianext", VK_MEDIA_NEXT_TRACK},
		{"mediaprev", VK_MEDIA_PREV_TRACK},
		{"mediastop", VK_MEDIA_STOP},
		{"mediaplay", VK_MEDIA_PLAY_PAUSE},
		{"playpause", VK_MEDIA_PLAY_PAUSE},

		{"browserback", VK_BROWSER_BACK},
		{"browserforward", VK_BROWSER_FORWARD},
		{"browserrefresh", VK_BROWSER_REFRESH},
		{"browserstop", VK_BROWSER_STOP},
		{"browsersearch", VK_BROWSER_SEARCH},
		{"browserfavorites", VK_BROWSER_FAVORITES},
		{"browserhome", VK_BROWSER_HOME},

		{NULL, 0}};
	for (int i = 0; key_map[i].name != NULL; i++) {
		size_t name_len = strlen(key_map[i].name);
		if (key_len == name_len && strncmp(key, key_map[i].name, key_len) == 0) {
			*keycode = key_map[i].vk;
			return 1;
		}
	}
	return 0;
}

static B32 is_extended_virtual_key(U8 vk) {
	switch (vk) {
		case VK_RCONTROL:
		case VK_RMENU:
		case VK_LWIN:
		case VK_RWIN:
		case VK_APPS:
		case VK_INSERT:
		case VK_DELETE:
		case VK_HOME:
		case VK_END:
		case VK_PRIOR:
		case VK_NEXT:
		case VK_LEFT:
		case VK_RIGHT:
		case VK_UP:
		case VK_DOWN:
		case VK_NUMLOCK:
		case VK_DIVIDE:
		case VK_SNAPSHOT:
			return 1;
	}
	return 0;
}

static B32 virtual_key_to_string(U8 vk, char* buffer, U32 buffer_size) {
	if (buffer_size == 0) {
		return 0;
	}
	if (vk >= '0' && vk <= '9') {
		buffer[0] = (char)vk;
		buffer[1] = 0;
		return 1;
	}
	if (vk >= 'A' && vk <= 'Z') {
		buffer[0] = (char)(vk + ('a' - 'A'));
		buffer[1] = 0;
		return 1;
	}

	switch (vk) {
		case VK_CONTROL:
			snprintf(buffer, buffer_size, "ctrl");
			return 1;
		case VK_LCONTROL:
			snprintf(buffer, buffer_size, "lctrl");
			return 1;
		case VK_RCONTROL:
			snprintf(buffer, buffer_size, "rctrl");
			return 1;
		case VK_SHIFT:
			snprintf(buffer, buffer_size, "shift");
			return 1;
		case VK_LSHIFT:
			snprintf(buffer, buffer_size, "lshift");
			return 1;
		case VK_RSHIFT:
			snprintf(buffer, buffer_size, "rshift");
			return 1;
		case VK_MENU:
			snprintf(buffer, buffer_size, "alt");
			return 1;
		case VK_LMENU:
			snprintf(buffer, buffer_size, "lalt");
			return 1;
		case VK_RMENU:
			snprintf(buffer, buffer_size, "ralt");
			return 1;
		case VK_LWIN:
			snprintf(buffer, buffer_size, "lwin");
			return 1;
		case VK_RWIN:
			snprintf(buffer, buffer_size, "rwin");
			return 1;
		case VK_ESCAPE:
			snprintf(buffer, buffer_size, "esc");
			return 1;
		case VK_RETURN:
			snprintf(buffer, buffer_size, "enter");
			return 1;
		case VK_SPACE:
			snprintf(buffer, buffer_size, "space");
			return 1;
		case VK_TAB:
			snprintf(buffer, buffer_size, "tab");
			return 1;
		case VK_BACK:
			snprintf(buffer, buffer_size, "backspace");
			return 1;
		case VK_DELETE:
			snprintf(buffer, buffer_size, "delete");
			return 1;
		case VK_INSERT:
			snprintf(buffer, buffer_size, "insert");
			return 1;
		case VK_HOME:
			snprintf(buffer, buffer_size, "home");
			return 1;
		case VK_END:
			snprintf(buffer, buffer_size, "end");
			return 1;
		case VK_PRIOR:
			snprintf(buffer, buffer_size, "pageup");
			return 1;
		case VK_NEXT:
			snprintf(buffer, buffer_size, "pagedown");
			return 1;
		case VK_PAUSE:
			snprintf(buffer, buffer_size, "pause");
			return 1;
		case VK_CAPITAL:
			snprintf(buffer, buffer_size, "capslock");
			return 1;
		case VK_NUMLOCK:
			snprintf(buffer, buffer_size, "numlock");
			return 1;
		case VK_SCROLL:
			snprintf(buffer, buffer_size, "scrolllock");
			return 1;
		case VK_SNAPSHOT:
			snprintf(buffer, buffer_size, "printscreen");
			return 1;
		case VK_UP:
			snprintf(buffer, buffer_size, "up");
			return 1;
		case VK_DOWN:
			snprintf(buffer, buffer_size, "down");
			return 1;
		case VK_LEFT:
			snprintf(buffer, buffer_size, "left");
			return 1;
		case VK_RIGHT:
			snprintf(buffer, buffer_size, "right");
			return 1;
		case VK_F1:
			snprintf(buffer, buffer_size, "f1");
			return 1;
		case VK_F2:
			snprintf(buffer, buffer_size, "f2");
			return 1;
		case VK_F3:
			snprintf(buffer, buffer_size, "f3");
			return 1;
		case VK_F4:
			snprintf(buffer, buffer_size, "f4");
			return 1;
		case VK_F5:
			snprintf(buffer, buffer_size, "f5");
			return 1;
		case VK_F6:
			snprintf(buffer, buffer_size, "f6");
			return 1;
		case VK_F7:
			snprintf(buffer, buffer_size, "f7");
			return 1;
		case VK_F8:
			snprintf(buffer, buffer_size, "f8");
			return 1;
		case VK_F9:
			snprintf(buffer, buffer_size, "f9");
			return 1;
		case VK_F10:
			snprintf(buffer, buffer_size, "f10");
			return 1;
		case VK_F11:
			snprintf(buffer, buffer_size, "f11");
			return 1;
		case VK_F12:
			snprintf(buffer, buffer_size, "f12");
			return 1;
		case VK_F13:
			snprintf(buffer, buffer_size, "f13");
			return 1;
		case VK_F14:
			snprintf(buffer, buffer_size, "f14");
			return 1;
		case VK_F15:
			snprintf(buffer, buffer_size, "f15");
			return 1;
		case VK_F16:
			snprintf(buffer, buffer_size, "f16");
			return 1;
		case VK_F17:
			snprintf(buffer, buffer_size, "f17");
			return 1;
		case VK_F18:
			snprintf(buffer, buffer_size, "f18");
			return 1;
		case VK_F19:
			snprintf(buffer, buffer_size, "f19");
			return 1;
		case VK_F20:
			snprintf(buffer, buffer_size, "f20");
			return 1;
		case VK_F21:
			snprintf(buffer, buffer_size, "f21");
			return 1;
		case VK_F22:
			snprintf(buffer, buffer_size, "f22");
			return 1;
		case VK_F23:
			snprintf(buffer, buffer_size, "f23");
			return 1;
		case VK_F24:
			snprintf(buffer, buffer_size, "f24");
			return 1;
		case VK_NUMPAD0:
			snprintf(buffer, buffer_size, "numpad0");
			return 1;
		case VK_NUMPAD1:
			snprintf(buffer, buffer_size, "numpad1");
			return 1;
		case VK_NUMPAD2:
			snprintf(buffer, buffer_size, "numpad2");
			return 1;
		case VK_NUMPAD3:
			snprintf(buffer, buffer_size, "numpad3");
			return 1;
		case VK_NUMPAD4:
			snprintf(buffer, buffer_size, "numpad4");
			return 1;
		case VK_NUMPAD5:
			snprintf(buffer, buffer_size, "numpad5");
			return 1;
		case VK_NUMPAD6:
			snprintf(buffer, buffer_size, "numpad6");
			return 1;
		case VK_NUMPAD7:
			snprintf(buffer, buffer_size, "numpad7");
			return 1;
		case VK_NUMPAD8:
			snprintf(buffer, buffer_size, "numpad8");
			return 1;
		case VK_NUMPAD9:
			snprintf(buffer, buffer_size, "numpad9");
			return 1;
		case VK_MULTIPLY:
			snprintf(buffer, buffer_size, "num*");
			return 1;
		case VK_ADD:
			snprintf(buffer, buffer_size, "num+");
			return 1;
		case VK_SUBTRACT:
			snprintf(buffer, buffer_size, "num-");
			return 1;
		case VK_DECIMAL:
			snprintf(buffer, buffer_size, "num.");
			return 1;
		case VK_DIVIDE:
			snprintf(buffer, buffer_size, "num/");
			return 1;
		case VK_OEM_1:
			snprintf(buffer, buffer_size, ";");
			return 1;
		case VK_OEM_PLUS:
			snprintf(buffer, buffer_size, "=");
			return 1;
		case VK_OEM_COMMA:
			snprintf(buffer, buffer_size, ",");
			return 1;
		case VK_OEM_MINUS:
			snprintf(buffer, buffer_size, "-");
			return 1;
		case VK_OEM_PERIOD:
			snprintf(buffer, buffer_size, ".");
			return 1;
		case VK_OEM_2:
			snprintf(buffer, buffer_size, "/");
			return 1;
		case VK_OEM_3:
			snprintf(buffer, buffer_size, "`");
			return 1;
		case VK_OEM_4:
			snprintf(buffer, buffer_size, "[");
			return 1;
		case VK_OEM_5:
			snprintf(buffer, buffer_size, "\\");
			return 1;
		case VK_OEM_6:
			snprintf(buffer, buffer_size, "]");
			return 1;
		case VK_OEM_7:
			snprintf(buffer, buffer_size, "'");
			return 1;
	}

	UINT scan_code = MapVirtualKeyA(vk, MAPVK_VK_TO_VSC);
	if (scan_code != 0) {
		if (is_extended_virtual_key(vk)) {
			scan_code |= 0x0100;
		}
		LONG lparam = (LONG)(scan_code << 16);
		int  len = GetKeyNameTextA(lparam, buffer, buffer_size);
		if (len > 0) {
			return 1;
		}
	}

	snprintf(buffer, buffer_size, "vk_%02x", vk);
	return 1;
}

B32 parse_binding_inner(char* binding, U32 binding_len, KeycodesUnsorted keycodes) {
	B32 parsing = binding_len > 0;
	U32 index = 0;
	U32 keycode_index = 0;
	MemoryZeroArray(keycodes);
	while (parsing) {
		U32 start_index = index;
		for (;;) {
			if (index >= binding_len) {
				parsing = 0;
				break;
			}
			if (binding[index] == '_') {
				break;
			}
			index++;
		}
		char* base = &binding[start_index];
		U32   key_len = index - start_index;
		U8    keycode;
		B32   success = key_string_to_virtual_key(base, key_len, &keycode);
		if (!success) {
			return 0;
		}
		keycodes[keycode_index++] = keycode;
		if (keycode_index >= ArrayCount(keycodes)) {
			return 0;
		}

		if (index < binding_len && binding[index] == '_') {
			index++;
		}
	}
	return 1;
}

void keycodes_unsorted_to_sparse_map(KeycodesUnsorted unsorted_keycodes, KeycodesSparseMap out_keycodes_sparse_map) {
	for (int i = 0; i < KEYCODES_COUNT; i++) {
		if (unsorted_keycodes[i] == 0) {
			break;
		}
		out_keycodes_sparse_map[unsorted_keycodes[i]] = 1;
	}
}

void keycodes_sparse_map_to_sorted(KeycodesSparseMap sparse_keycodes_map, KeycodesSorted out_keycodes_sorted) {
	int index = 0;
	for (int i = 0; i < KEYCODES_COUNT; i++) {
		if (sparse_keycodes_map[i] != 0) {
			out_keycodes_sorted[index++] = i;
		}
	}
}

B32 parse_binding(char* binding, KeycodesUnsorted keycodes) {
	return parse_binding_inner(binding, strlen(binding), keycodes);
}

void print_keycodes_sparce(KeycodesSparseMap keycodes_sorted) {
	for (int i = 0; i < KEYCODES_COUNT; i++) {
		if (keycodes_sorted[i]) {
			char key_name[64];
			virtual_key_to_string((U8)keycodes_sorted[i], key_name, ArrayCount(key_name));
			printf("%d(%s) ", keycodes_sorted[i], key_name);
		}
	}
}

void print_keycodes_sorted(KeycodesSorted keycodes_sorted) {
	for (int i = 0; i < KEYCODES_COUNT; i++) {
		if (keycodes_sorted[i] == 0) {
			break;
		}
		char key_name[64];
		virtual_key_to_string((U8)keycodes_sorted[i], key_name, ArrayCount(key_name));
		printf("%d(%s) ", keycodes_sorted[i], key_name);
	}
}

U32 workspace_to_index(WorkspacesData* workspaces_data, Workspace* workspace) {
	return (U32)(workspace - &workspaces_data->workspaces[0]);
}

static void tray_set_workspace(U32 workspace_index);

static void workspace_set_active(WorkspacesData* workspaces_data, U32 workspace_index) {
	if (workspaces_data->active_workspace_index == workspace_index) {
		return 0;
	}
	workspaces_data->prev_active_workspace = workspaces_data->active_workspace_index;
	workspaces_data->active_workspace_index = workspace_index;
	tray_set_workspace(workspace_index);
}

Arena*          g_temp_arena = NULL;
Config          g_config = {0};
HHOOK           g_keyboard_hook = NULL;
U64             g_main_thread_id = 0;
U64             g_keyboard_thread_id = 0;
State           g_state = {0};
HWND            g_main_hwnd = NULL;
NOTIFYICONDATAW g_tray_icon_data = {0};
HICON           g_tray_icon_cache[256] = {0};
U32             g_tray_workspace_index = 0;

THREAD_LOCAL KeyboardHookThreadState* g_keyboard_thread_state = {0};
global Semaphore                      g_keyboard_bindings_update_semaphore = {0};
global Semaphore                      g_keyboard_thread_ready_semaphore = {0};

////////////////////////////////
//~ IPC Types and Globals

typedef enum ExecMode ExecMode;
enum ExecMode {
	ExecMode_Normal,
	ExecMode_IPCSender,
};

typedef struct IPCInfo IPCInfo;
struct IPCInfo {
	U64 msg_size;
};

static HICON tray_create_icon(char letter) {
	const int size = 16;
	HDC       screen_dc = GetDC(NULL);
	HDC       mem_dc = CreateCompatibleDC(screen_dc);
	HBITMAP   color_bmp = CreateCompatibleBitmap(screen_dc, size, size);
	HBITMAP   old_bmp = (HBITMAP)SelectObject(mem_dc, color_bmp);

	RECT   rect = {0, 0, size, size};
	HBRUSH bg = CreateSolidBrush(RGB(0, 0, 0));
	FillRect(mem_dc, &rect, bg);
	DeleteObject(bg);

	HFONT font = CreateFontW(
		-12, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");
	HFONT old_font = (HFONT)SelectObject(mem_dc, font);
	SetBkMode(mem_dc, TRANSPARENT);
	SetTextColor(mem_dc, RGB(255, 255, 255));
	wchar_t text[2] = {(wchar_t)letter, 0};
	DrawTextW(mem_dc, text, 1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	SelectObject(mem_dc, old_font);
	SelectObject(mem_dc, old_bmp);

	HBITMAP  mask_bmp = CreateBitmap(size, size, 1, 1, NULL);
	ICONINFO icon_info = {0};
	icon_info.fIcon = TRUE;
	icon_info.hbmColor = color_bmp;
	icon_info.hbmMask = mask_bmp;
	HICON icon = CreateIconIndirect(&icon_info);

	DeleteObject(mask_bmp);
	DeleteObject(color_bmp);
	DeleteObject(font);
	DeleteDC(mem_dc);
	ReleaseDC(NULL, screen_dc);

	return icon;
}

static HICON tray_get_cached_icon(U32 workspace_index) {
	if (workspace_index >= ArrayCount(g_tray_icon_cache)) {
		return NULL;
	}
	if (g_tray_icon_cache[workspace_index] == NULL) {
		g_tray_icon_cache[workspace_index] = tray_create_icon((char)workspace_index);
	}
	return g_tray_icon_cache[workspace_index];
}

static void tray_set_workspace(U32 workspace_index) {
	if (g_main_hwnd == NULL || workspace_index == 0) {
		return;
	}
	if (workspace_index == g_tray_workspace_index) {
		return;
	}
	HICON icon = tray_get_cached_icon(workspace_index);
	if (icon == NULL) {
		return;
	}
	g_tray_icon_data.uFlags = NIF_ICON | NIF_TIP;
	g_tray_icon_data.hIcon = icon;
	swprintf(g_tray_icon_data.szTip, ArrayCount(g_tray_icon_data.szTip), L"Workspace %c", (wchar_t)workspace_index);
	Shell_NotifyIconW(NIM_MODIFY, &g_tray_icon_data);
	g_tray_workspace_index = workspace_index;
}

static void tray_init(HWND hwnd, U32 workspace_index) {
	if (hwnd == NULL) {
		return;
	}
	g_tray_icon_data = (NOTIFYICONDATAW){0};
	g_tray_icon_data.cbSize = sizeof(g_tray_icon_data);
	g_tray_icon_data.hWnd = hwnd;
	g_tray_icon_data.uID = 1;
	g_tray_icon_data.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	g_tray_icon_data.uCallbackMessage = (WM_APP + 1);
	g_tray_icon_data.hIcon = tray_get_cached_icon(workspace_index);
	swprintf(g_tray_icon_data.szTip, ArrayCount(g_tray_icon_data.szTip), L"Workspace %c", (wchar_t)workspace_index);
	Shell_NotifyIconW(NIM_ADD, &g_tray_icon_data);
	g_tray_workspace_index = workspace_index;
}

static void tray_cleanup(void) {
	if (g_tray_icon_data.hWnd != NULL) {
		Shell_NotifyIconW(NIM_DELETE, &g_tray_icon_data);
	}
	for (int i = 0; i < (int)ArrayCount(g_tray_icon_cache); i++) {
		if (g_tray_icon_cache[i] != NULL) {
			DestroyIcon(g_tray_icon_cache[i]);
			g_tray_icon_cache[i] = NULL;
		}
	}
	g_tray_icon_data = (NOTIFYICONDATAW){0};
	g_tray_workspace_index = 0;
}

typedef enum WndConfigFilterType WndConfigFilterType;
enum WndConfigFilterType {
	WndConfigFilterType_None = 0,
	WndConfigFilterType_Title = 0x1,
	WndConfigFilterType_ProcessName = 0x2,
	WndConfigFilterType_All = 3,
};

WindowState* alloc_wnd(WindowsList* windows_list) {
	// first, try to grab the top of the free list...
	WindowState* result = windows_list->first_free;
	if (result != 0) {
		SLLStackPop_N(windows_list->first_free, next_free);
		MemoryZeroStruct(result);
	}

	// if the free list was empty, push a new entity onto the arena
	else {
		result = (WindowState*)push_array(windows_list->arena, WindowState, 1);
	}

	SLLStackPush(windows_list->head, result);

	return result;
}

void release_wnd(WorkspacesData* workspaces_data, WindowsList* windows_list, WindowState* window_state) {
	printf("release_wnd: %s\n", wnd_get_state_info_string(g_temp_arena, window_state));
	workspaces_data->workspaces[window_state->workspace_index].active_window = NULL;
	WindowState** prev_next = &windows_list->head;
	for (WindowState* current = windows_list->head; current != NULL; current = current->next) {
		if (current == window_state) {
			*prev_next = current->next;
			SLLStackPush_N(windows_list->first_free, window_state, next_free);
			break;
		}
		prev_next = &current->next;
	}
}

WindowState* find_wnd(WindowsList* windows_list, HWND hwnd) {
	WindowState* current = windows_list->head;
	while (current != NULL) {
		if (current->hwnd == hwnd) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}

B32 release_wnd_by_hwnd(WorkspacesData* workspaces_data, WindowsList* windows_list, HWND hwnd) {
	WindowState* window_state = find_wnd(windows_list, hwnd);
	if (window_state != NULL) {
		release_wnd(workspaces_data, windows_list, window_state);
		return 1;
	}
	return 0;
}

B32 wnd_get_or_create(WindowsList* windows_list, HWND hwnd, WindowState** out_window_state) {
	WindowState* window_state = find_wnd(windows_list, hwnd);
	B32          result = 0;
	if (window_state == NULL) {
		window_state = alloc_wnd(windows_list);
		window_state->hwnd = hwnd;
		window_state->filter_index = -1;
		printf("wnd_get_or_create: create %s\n", wnd_get_info_string(g_temp_arena, hwnd));
		result = 1;
	}
	if (out_window_state != NULL) {
		*out_window_state = window_state;
	}
	return result;
}

void wnd_in_workspace(
	Arena* arena, WindowsList* windows_list, U32 workspace_index, WindowState*** out_window_state_array,
	U32* out_window_state_count) {
	U32 count = 0;
	for
		EachNode(window_state, WindowState, windows_list->head) {
			if (window_state->workspace_index == workspace_index) {
				count++;
			}
		}
	*out_window_state_array = push_array(arena, WindowState*, count);
	count = 0;
	for
		EachNode(window_state, WindowState, windows_list->head) {
			if (window_state->workspace_index == workspace_index) {
				(*out_window_state_array)[count++] = window_state;
			}
		}
	*out_window_state_count = count;
}

String16 get_window_name16(Arena* arena, HWND hwnd) {
	int length = GetWindowTextLengthW(hwnd);
	if (length != 0) {
		wchar_t* window_name = push_array(arena, wchar_t, length + 1);
		GetWindowTextW(hwnd, window_name, length + 1);
		return str16(window_name, length);
	}
	return str16(L"", 0);
}

String8 get_window_name(Arena* arena, HWND hwnd) {
	return str8_from_16(arena, get_window_name16(arena, hwnd));
}

String16 get_process_name16(Arena* arena, HWND hwnd) {
	DWORD process_id = 0;
	if (!GetWindowThreadProcessId(hwnd, &process_id)) {
		return str16(L"", 0);
	}

	HANDLE process_handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, process_id);

	if (process_handle != NULL) {
		wchar_t* buffer = push_array(arena, wchar_t, 255);
		if (GetModuleFileNameExW(process_handle, NULL, buffer, 255)) {
			// buffer содержит полный путь
			wchar_t* last_slash = wcsrchr(buffer, L'\\');
			if (last_slash != NULL) {
				memmove(buffer, last_slash + 1, (wcslen(last_slash + 1) + 1) * sizeof(wchar_t));
				return str16(buffer, wcslen(buffer));
			}
		}
		CloseHandle(process_handle);
	}
	return str16(L"", 0);
}

String8 get_process_name(Arena* arena, HWND hwnd) {
	return str8_from_16(arena, get_process_name16(arena, hwnd));
}

B32 wnd_is_corewindow(HWND hwnd) {
	wchar_t class_name[256];
	if (GetClassNameW(hwnd, class_name, ArrayCount(class_name)) == 0) {
		return 0;
	}
	return wcscmp(class_name, L"Windows.UI.Core.CoreWindow") == 0;
}

B32 wnd_is_visible(HWND hwnd) {
	if (!IsWindow(hwnd))
		return 0;
	if (!IsWindowVisible(hwnd))
		return 0;
	if (GetAncestor(hwnd, GA_ROOT) != hwnd)
		return 0;
	if (GetWindow(hwnd, GW_OWNER) != NULL)
		return 0;

	LONG_PTR ex = GetWindowLongPtr(hwnd, GWL_EXSTYLE);
	if ((ex & WS_EX_TOOLWINDOW) && !(ex & WS_EX_APPWINDOW))
		return 0;
	if (ex & WS_EX_NOACTIVATE)
		return 0;
	B32 is_task_deleted = GetProp(hwnd, "ITaskList_Deleted") != NULL;
	if (is_task_deleted)
		return 0;
	if (wnd_is_corewindow(hwnd))
		return 0;

	DWORD cloaked = 0;
	if (SUCCEEDED(DwmGetWindowAttribute(hwnd, DWMWA_CLOAKED, &cloaked, sizeof(cloaked))) && cloaked != 0) {
		return 0;
	}

	return 1;
}

void wnd_focus(HWND hwnd) {
	if (IsIconic(hwnd)) {
		ShowWindow(hwnd, SW_RESTORE);
	}
	INPUT inputs[1] = {{.type = INPUT_MOUSE}};
	SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
	SetForegroundWindow(hwnd);
}

void wnd_hide(HWND hwnd) {
	PostMessage(hwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
}

const char* wnd_get_info_string(Arena* arena, HWND hwnd) {
	String8 wnd_name = get_window_name(arena, hwnd);
	String8 process_name = get_process_name(arena, hwnd);
	char*   buffer = push_array(arena, char, 1024);
	sprintf(buffer, "hwnd: %p wnd_name: %.*s process_name: %.*s", hwnd, str8_varg(wnd_name), str8_varg(process_name));
	return buffer;
}

const char* wnd_get_state_info_string(Arena* arena, WindowState* window_state) {
	char* buffer = push_array(arena, char, 1024);
	sprintf(
		buffer, "%s workspace_index: %u (%c)", wnd_get_info_string(arena, window_state->hwnd),
		window_state->workspace_index, window_state->workspace_index);
	return buffer;
}

B32 wnd_attach_workspace(WindowState* window_state, WndConfigFilterType filter_type) {
	String8 wnd_name = get_window_name(g_temp_arena, window_state->hwnd);
	String8 process_name = get_process_name(g_temp_arena, window_state->hwnd);
	for (U32 i = 0; i < g_config.wnd_configs_count; i++) {
		WndConfig* wnd_config = &g_config.wnd_configs[i];
		U32        match_count = 0;
		U32        match_need = 0;
		if ((filter_type & WndConfigFilterType_Title) && wnd_config->titleFilter.size > 0) {
			match_need++;
			match_count += str8_wildcard(wnd_name, wnd_config->titleFilter);
		}
		if ((filter_type & WndConfigFilterType_ProcessName) && wnd_config->processNameFilter.size > 0) {
			match_need++;
			match_count += str8_wildcard(process_name, wnd_config->processNameFilter);
		}
		B32 is_match = match_need > 0 && match_count == match_need;
		if (is_match) {
			printf("Attach window by wnd_config: %d match\n", i);
			if (wnd_config->command.type == CommandType_WorkspaceMove) {
				window_state->workspace_index = wnd_config->command.workspace_index;
			}
			else {
				handle_command(&wnd_config->command);
				window_state->workspace_index = g_state.workspaces->active_workspace_index;
			}
			window_state->filter_index = i;
			return 1;
		}
	}
	printf(
		"Attach window to workspace %u (%c) by active workspace\n", g_state.workspaces->active_workspace_index,
		g_state.workspaces->active_workspace_index);
	window_state->workspace_index = g_state.workspaces->active_workspace_index;
	return 0;
}

BOOL CALLBACK init_enum_windows(HWND hwnd, LPARAM lParam) {
	B32     is_visible = wnd_is_visible(hwnd);
	String8 wnd_name = get_window_name(g_temp_arena, hwnd);
	if (wnd_name.size > 0 && is_visible) {
		WindowState* window_state = NULL;
		wnd_get_or_create(g_state.windows_list, hwnd, &window_state);
		wnd_attach_workspace(window_state, WndConfigFilterType_All);
	}
	return TRUE;
}

B32 parse_command(String8List str, Command* command) {
	if (str.first == NULL) {
		return 0;
	}
	String8     name = str.first->string;
	CommandType type = command_type_from_name(name);
	command->type = type;
	if (type == CommandType_None) {
		return 0;
	}
	CommandArgType arg_type = g_command_table[type].arg_type;
	if (arg_type == CommandArgType_None) {
		return 1;
	}
	if (str.first->next == NULL) {
		return 0;
	}
	String8 arg = str.first->next->string;
	switch (arg_type) {
		case CommandArgType_Int:
			if (!str8_is_integer(arg, 10)) {
				return 0;
			}
			command->workspace_index = (U32)u64_from_str8(arg, 10);
			break;
		case CommandArgType_Char:
			if (arg.size != 1) {
				return 0;
			}
			command->workspace_index = (U8)arg.str[0];
			break;
		case CommandArgType_String:
			if (command->arena == NULL) {
				return 0;
			}
			command->subprocess_command = push_str8_copy(command->arena, arg);
			break;
		default:
			return 0;
	}
	return 1;
}
String8List parse_command_parts(Arena* arena, String8 command_str) {
	U64         space_index = str8_index_of(command_str, str8_lit(" ").str, 1);
	String8List parts = {0};
	str8_list_push(arena, &parts, str8_prefix(command_str, space_index));
	if (space_index != command_str.size) {
		str8_list_push(arena, &parts, str8_skip(command_str, space_index + 1));
	}
	return parts;
}

B32 run_command(Arena* arena, String8 command_str) {
	Temp        scratch = temp_begin(arena);
	String8List parts = parse_command_parts(scratch.arena, command_str);
	Command     command = {0};
	command.arena = scratch.arena;
	B32 parsed = parse_command(parts, &command);
	if (parsed) {
		handle_command(&command);
	}
	temp_end(scratch);
	return parsed;
}

void CALLBACK HandleWinEvent(
	HWINEVENTHOOK hook, DWORD event, HWND hwnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime) {
	if (event != EVENT_OBJECT_CREATE && event != EVENT_OBJECT_DESTROY && event != EVENT_OBJECT_NAMECHANGE &&
		event != EVENT_OBJECT_SHOW && event != EVENT_OBJECT_HIDE && event != EVENT_SYSTEM_MINIMIZESTART &&
		event != EVENT_SYSTEM_MINIMIZEEND && event != EVENT_SYSTEM_FOREGROUND) {
		return;
	}
	if (idObject != OBJID_WINDOW || idChild != 0) {
		return;
	}
	switch (event) {
		case EVENT_SYSTEM_FOREGROUND:
		{
			// @TASK: FOREGROUND EVENT IS SHIT
			// There is no FOREGROUND event when click on minimized window in task bar. Probably because it's sends
			// minimizstart/end while animation. And wnd_is_visible_filter this out. Same time we track
			// MINIMIZESTART and MINIMIZEEND events because otherwise foreground event is sent when window is
			// minimizing. EVENT_SYSTEM_MINIMIZESTART: hwnd: 00000000000F085E wnd_name: Google [Work] - Google
			// Chrome process_name: chrome.exe workspace_index: 101 (e) EVENT_SYSTEM_FOREGROUND: hwnd:
			// 00000000000205F0 wnd_name: ● main.c - windowspace - Cursor process_name: Cursor.exe workspace_index:
			// 99 (c) EVENT_SYSTEM_MINIMIZEEND: hwnd: 00000000000F085E wnd_name: Google [Work] - Google Chrome
			// process_name: chrome.exe workspace_index: 101 (e)
			if (wnd_is_visible(hwnd)) {
				WindowState* window_state = find_wnd(g_state.windows_list, hwnd);
				if (window_state != NULL) {
					printf(
						"EVENT_SYSTEM_FOREGROUND: visible window %s\n",
						wnd_get_state_info_string(g_temp_arena, window_state));
					// workspace_set_active(g_state.workspaces, window_state->workspace_index);
					tray_set_workspace(window_state->workspace_index);
					g_state.workspaces->workspaces[window_state->workspace_index].active_window = window_state->hwnd;
				}
			}

			break;
		}
		case EVENT_OBJECT_CREATE:
		{
			break;
		}
		case EVENT_OBJECT_SHOW:
		{
			String8 wnd_name = get_window_name(g_temp_arena, hwnd);
			if (wnd_name.size > 0 && wnd_is_visible(hwnd)) {
				printf("EVENT_OBJECT_SHOW: %s\n", wnd_get_info_string(g_temp_arena, hwnd));
				WindowState* window_state = NULL;
				if (wnd_get_or_create(g_state.windows_list, hwnd, &window_state)) {
					wnd_attach_workspace(window_state, WndConfigFilterType_All);
					// Maybe switch to workspace here? It's strange when window is shown but workspace where
					// it's opened not focused. If we have some additional rules window might be opened in
					// different workspace than active.
				}
			}
			else {
				if (release_wnd_by_hwnd(g_state.workspaces, g_state.windows_list, hwnd)) {
					printf("EVENT_OBJECT_SHOW: released window %s\n", wnd_get_info_string(g_temp_arena, hwnd));
				}
			}
			break;
		}
		// @TASK: FOREGROUND EVENT IS SHIT
		// case EVENT_SYSTEM_MINIMIZESTART:
		// {
		//     WindowState *window_state = find_wnd(g_windows_list, hwnd);
		//     if (window_state != NULL) {
		//         printf("EVENT_SYSTEM_MINIMIZESTART: %s\n", wnd_get_state_info_string(g_temp_arena, window_state));
		//         window_state->is_minimizing = 1;
		//     }
		//     break;
		// }
		// case EVENT_SYSTEM_MINIMIZEEND:
		// {
		//     WindowState *window_state = find_wnd(g_windows_list, hwnd);
		//     if (window_state != NULL) {
		//         printf("EVENT_SYSTEM_MINIMIZEEND: %s\n", wnd_get_state_info_string(g_temp_arena, window_state));
		//         window_state->is_minimizing = 0;
		//     }
		//     break;
		// }
		case EVENT_OBJECT_NAMECHANGE:
		{
			String8 wnd_name = get_window_name(g_temp_arena, hwnd);
			if (wnd_name.size > 0 && wnd_is_visible(hwnd)) {
				printf("EVENT_OBJECT_NAMECHANGE: %s\n", wnd_get_info_string(g_temp_arena, hwnd));
				WindowState* window_state = NULL;
				B32          is_created = 0;
				if (wnd_get_or_create(g_state.windows_list, hwnd, &window_state)) {
					wnd_attach_workspace(window_state, WndConfigFilterType_All);
				}
				else if (window_state->filter_index == -1) {
					wnd_attach_workspace(window_state, WndConfigFilterType_All);
				}
			}
			else {
				if (release_wnd_by_hwnd(g_state.workspaces, g_state.windows_list, hwnd)) {
					printf("EVENT_OBJECT_NAMECHANGE: released window %s\n", wnd_get_info_string(g_temp_arena, hwnd));
				}
			}
			break;
		}
		case EVENT_OBJECT_HIDE:
		{
			if (release_wnd_by_hwnd(g_state.workspaces, g_state.windows_list, hwnd)) {
				printf("EVENT_OBJECT_DESTROY: released window %s\n", wnd_get_info_string(g_temp_arena, hwnd));
			}
			break;
		}
		case EVENT_OBJECT_DESTROY:
		{
			if (release_wnd_by_hwnd(g_state.workspaces, g_state.windows_list, hwnd)) {
				printf("EVENT_OBJECT_DESTROY: released window %s\n", wnd_get_info_string(g_temp_arena, hwnd));
			}
			break;
		}
		default:
			break;
	}
}

internal B32 command_binding_create(char* binding, CommandBinding* out_binding) {
	KeycodesUnsorted keycodes_unsorted;
	if (!parse_binding(binding, keycodes_unsorted)) {
		return 0;
	}

	KeycodesSparseMap keycodes_as_sparse_map;
	MemoryZeroArray(keycodes_as_sparse_map);
	keycodes_unsorted_to_sparse_map(keycodes_unsorted, keycodes_as_sparse_map);
	keycodes_sparse_map_to_sorted(keycodes_as_sparse_map, out_binding->keycodes);
	return 1;
}

internal CommandBinding* command_layers_get_current_bindings(CommandLayers* command_layers) {
	U32 layer_index = g_state.current_layer_index;
	return command_layers->command_bindings[layer_index];
}

internal Command* command_layers_get_current_commands(CommandLayers* command_layers) {
	U32 layer_index = g_state.current_layer_index;
	return command_layers->commands[layer_index];
}

internal void keyboard_hook_post_layer_change(U32 layer_index) {
	PostThreadMessage(g_keyboard_thread_id, WM_KEYHOOK_LAYER_CHANGE, (WPARAM)layer_index, 0);
}

internal void keyboard_hook_post_bindings_update(void) {
	Assert(g_keyboard_thread_id);
	for (;;) {
		if (os_semaphore_take(g_keyboard_bindings_update_semaphore, max_U64)) {
			Arena*                   arena = arena_alloc();
			KeyboardHookThreadState* keyboard_thread_state = push_array(arena, KeyboardHookThreadState, 1);
			keyboard_thread_state->current_layer_index = g_state.current_layer_index;
			keyboard_thread_state->arena = arena;
			MemoryCopy(
				keyboard_thread_state->command_bindings, g_config.command_layers->command_bindings,
				sizeof(CommandBinding) * COMMAND_LAYERS_COUNT * COMMAND_BINDINGS_COUNT);
			if (!PostThreadMessage(
					g_keyboard_thread_id, WM_KEYHOOK_BINDINGS_UPDATE, 0, (LPARAM)keyboard_thread_state)) {
				os_semaphore_drop(g_keyboard_bindings_update_semaphore);
			}
			break;
		}
	}
}

LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode >= 0) {
		if (wParam != WM_KEYDOWN && wParam != WM_SYSKEYDOWN) {
			return CallNextHookEx(g_keyboard_hook, nCode, wParam, lParam);
		}
		static KeycodesSparseMap current_keystate_sparse;
		for (int i = 0; i < KEYCODES_COUNT; i++) {
			current_keystate_sparse[i] = GetAsyncKeyState(i) < 0;
		}
		KBDLLHOOKSTRUCT* kb = (KBDLLHOOKSTRUCT*)lParam;
		WORD             vkCode = kb->vkCode;
		current_keystate_sparse[vkCode] = 1;
		// don't care about which modifiers l or r are pressed.
		current_keystate_sparse[VK_MENU] |= current_keystate_sparse[VK_LMENU] || current_keystate_sparse[VK_RMENU];
		current_keystate_sparse[VK_LMENU] = 0;
		current_keystate_sparse[VK_RMENU] = 0;
		current_keystate_sparse[VK_CONTROL] |=
			current_keystate_sparse[VK_LCONTROL] || current_keystate_sparse[VK_RCONTROL];
		current_keystate_sparse[VK_LCONTROL] = 0;
		current_keystate_sparse[VK_RCONTROL] = 0;
		current_keystate_sparse[VK_SHIFT] |= current_keystate_sparse[VK_LSHIFT] || current_keystate_sparse[VK_RSHIFT];
		current_keystate_sparse[VK_LSHIFT] = 0;
		current_keystate_sparse[VK_RSHIFT] = 0;

		// dbg
		// {
		//     printf("current_keystate_sparse: ");
		//     print_keycodes_sparce(current_keystate_sparse);
		//     printf("\n");
		// }

		static KeycodesSorted current_keystate_sorted;
		MemoryZeroArray(current_keystate_sorted);
		keycodes_sparse_map_to_sorted(current_keystate_sparse, current_keystate_sorted);
		// dbg
		// {
		//     printf("current_keystate_sorted: ");
		//     print_keycodes_sorted(current_keystate_sorted);
		//     printf("\n");
		// }
		KeyboardHookThreadState* state = g_keyboard_thread_state;
		U32                      layer_index = state->current_layer_index;
		CommandBinding*          current_bindings = state->command_bindings[layer_index];
		for (int i = 0; i < COMMAND_BINDINGS_COUNT; i++) {
			CommandBinding* binding = &current_bindings[i];
			if (binding->keycodes[0] == 0) {
				continue;
			}
			// dbg
			// {
			//     printf("command->keycodes: ");
			//     print_keycodes_sorted(command->keycodes);
			//     printf("\n");
			// }

			B32 is_match = MemoryMatchArray(current_keystate_sorted, binding->keycodes);
			if (is_match) {
				printf("is_match\n");
				PostThreadMessage(g_main_thread_id, WM_INPUT_COMMAND, 0, (LPARAM)i);
				return 1;
			}
		}
	}

	// ВАЖНО: всегда передаем событие дальше (не блокируем)
	return CallNextHookEx(g_keyboard_hook, nCode, wParam, lParam);
}

void handle_command(Command* command) {
	switch (command->type) {
		case CommandType_WindowClose:
		{
			printf("CommandType_WindowClose\n");
			HWND active_window = GetForegroundWindow();
			PostMessage(active_window, WM_CLOSE, 0, 0);
			break;
		}
		case CommandType_Subprocess:
		{
			printf("CommandType_Subprocess subprocess_command: %.*s\n", str8_varg(command->subprocess_command));
			OS_Handle handle = os_cmd_line_launch(command->subprocess_command);
			os_process_detach(handle);
			break;
		}
		case CommandType_BindingLayerChange:
		{
			printf("CommandType_BindingLayerChange workspace_index: %u\n", command->workspace_index);
			if (command->workspace_index >= COMMAND_LAYERS_COUNT) {
				break;
			}
			g_state.current_layer_index = command->workspace_index;
			keyboard_hook_post_layer_change(command->workspace_index);
			break;
		}
		case CommandType_ReloadConfig:
		{
			printf("CommandType_ReloadConfig\n");
			U32    current_layer_index = g_state.current_layer_index;
			Arena* old_arena = g_config.arena;
			Config new_config = {0};
			new_config.arena = arena_alloc();
			if (parse_toml(&new_config, g_temp_arena)) {
				arena_release(old_arena);
				g_config = new_config;
				g_state.current_layer_index = current_layer_index;
				keyboard_hook_post_bindings_update();
			}
			else {
				arena_release(new_config.arena);
			}
			break;
		}
		case CommandType_WorkspaceBackAndForth:
		{
			printf("CommandType_WorkspaceBackAndForth\n");
			Command command = {0};
			command.type = CommandType_WorkspaceFocus;
			command.workspace_index = g_state.workspaces->prev_active_workspace;
			handle_command(&command);
			break;
		}
		case CommandType_WorkspaceFocus:
		{
			printf(
				"CommandType_WorkspaceFocus workspace_index: %u (%c)\n", command->workspace_index,
				command->workspace_index);
			U32 workspace_index = command->workspace_index;
			workspace_set_active(g_state.workspaces, workspace_index);
			HWND last_active_window = g_state.workspaces->workspaces[workspace_index].active_window;
			for
				EachNode(window_state, WindowState, g_state.windows_list->head) {
					String8 window_name = get_window_name(g_temp_arena, window_state->hwnd);
					if (window_state->workspace_index == workspace_index) {
						printf("matched window: %s'\n", wnd_get_state_info_string(g_temp_arena, window_state));
						if (window_state->hwnd != last_active_window) {
							wnd_focus(window_state->hwnd);
						}
					}
					else {
						printf("minimizing window: %s\n", wnd_get_state_info_string(g_temp_arena, window_state));
						// THIS SHIT CALLS BIG ISSUES WITH FOREGROUND EVENT
						wnd_hide(window_state->hwnd);
					}
				}
			if (last_active_window != NULL) {
				printf("focused last active window: %s\n", wnd_get_info_string(g_temp_arena, last_active_window));
				wnd_focus(last_active_window);
			}

			break;
		}
		case CommandType_WorkspaceMove:
		{
			printf(
				"CommandType_WorkspaceMove workspace_index: %u (%c)\n", command->workspace_index,
				command->workspace_index);
			HWND         active_window = GetForegroundWindow();
			WindowState* active_window_state = find_wnd(g_state.windows_list, active_window);
			if (active_window_state != NULL) {
				if (active_window_state->workspace_index == command->workspace_index) {
					// Already in the workspace
					break;
				}
				active_window_state->workspace_index = command->workspace_index;
				// TODO: launch window as administrator
				printf(
					"moved window %s to workspace %u (%c)\n",
					wnd_get_state_info_string(g_temp_arena, active_window_state), command->workspace_index,
					command->workspace_index);
				wnd_hide(active_window_state->hwnd);
			}

			// Focus on next wnd in workspace
			for
				EachNode(window_state, WindowState, g_state.windows_list->head) {
					if (window_state->workspace_index == g_state.workspaces->active_workspace_index) {
						wnd_focus(window_state->hwnd);
						break;
					}
				}

			printf("CommandType_WorkspaceMove\n");
			break;
		}
		default:
			if (command->type == CommandType_WindowFocusPrev || command->type == CommandType_WindowFocusNext) {
				printf("CommandType_WindowFocusDir\n");
				WindowState** state_array = NULL;
				U32           state_count = 0;
				wnd_in_workspace(
					g_temp_arena, g_state.windows_list, g_state.workspaces->active_workspace_index, &state_array,
					&state_count);
				if (state_count <= 1) {
					break;
				}
				int  current_index = 0;
				HWND foreground_window = GetForegroundWindow();
				for (int i = 0; i < state_count; i++) {
					printf("wnd: %s\n", wnd_get_state_info_string(g_temp_arena, state_array[i]));
				}
				for (int i = 0; i < state_count; i++) {
					if (state_array[i]->hwnd == foreground_window) {
						current_index = i;
						break;
					}
				}
				if (command->type == CommandType_WindowFocusPrev) {
					current_index = (current_index + state_count - 1) % state_count;
				}
				else if (command->type == CommandType_WindowFocusNext) {
					current_index = (current_index + 1) % state_count;
				}
				wnd_focus(state_array[current_index]->hwnd);
				break;
			}
			else {
				printf("CommandType_Doesn't handled\n");
			}
			break;
	}
}
#define IPC_SHARED_MEMORY_BUFFER_SIZE MB(1)
#define IPC_RESPONSE_TIMEOUT_US (10 * 1000000) // 10 seconds

// sender -> main channel
#define IPC_S2M_SHM_NAME "_windowspace_ipc_s2m_shm_%u_"
#define IPC_S2M_SIGNAL_SEM_NAME "_windowspace_ipc_s2m_signal_%u_"
#define IPC_S2M_LOCK_SEM_NAME "_windowspace_ipc_s2m_lock_%u_"

// main -> sender channel (responses)
#define IPC_M2S_SHM_NAME "_windowspace_ipc_m2s_shm_%u_"
#define IPC_M2S_SIGNAL_SEM_NAME "_windowspace_ipc_m2s_signal_%u_"
#define IPC_M2S_LOCK_SEM_NAME "_windowspace_ipc_m2s_lock_%u_"

// sender -> main globals
global Semaphore g_ipc_s2m_signal_semaphore = {0};
global Semaphore g_ipc_s2m_lock_semaphore = {0};
global U8*       g_ipc_s2m_shared_memory_base = 0;

// main -> sender globals
global Semaphore g_ipc_m2s_signal_semaphore = {0};
global Semaphore g_ipc_m2s_lock_semaphore = {0};
global U8*       g_ipc_m2s_shared_memory_base = 0;

// Ring buffer for IPC messages (ipc thread -> main thread)
global U8      g_ipc_ring_buffer[MB(1)] = {0};
global U64     g_ipc_ring_write_pos = 0;
global U64     g_ipc_ring_read_pos = 0;
global Mutex   g_ipc_ring_mutex = {0};
global CondVar g_ipc_ring_cv = {0};

// Forward declaration
internal void ipc_send_response(String8 response);

////////////////////////////////
//~ IPC Ring Buffer Helpers

internal U64 ring_write(U8* ring, U64 ring_size, U64 pos, void* src, U64 src_size) {
	U64 index = pos % ring_size;
	U64 first_part = Min(src_size, ring_size - index);
	U64 second_part = src_size - first_part;
	MemoryCopy(ring + index, src, first_part);
	if (second_part > 0) {
		MemoryCopy(ring, (U8*)src + first_part, second_part);
	}
	return src_size;
}

internal U64 ring_read(U8* ring, U64 ring_size, U64 pos, void* dst, U64 dst_size) {
	U64 index = pos % ring_size;
	U64 first_part = Min(dst_size, ring_size - index);
	U64 second_part = dst_size - first_part;
	MemoryCopy(dst, ring + index, first_part);
	if (second_part > 0) {
		MemoryCopy((U8*)dst + first_part, ring, second_part);
	}
	return dst_size;
}

#define ring_write_struct(ring, ring_size, pos, ptr) ring_write((ring), (ring_size), (pos), (ptr), sizeof(*(ptr)))
#define ring_read_struct(ring, ring_size, pos, ptr) ring_read((ring), (ring_size), (pos), (ptr), sizeof(*(ptr)))

////////////////////////////////
//~ IPC Listener Thread

internal void ipc_listener_thread_entry(void* p) {
	for (;;) {
		// Wait for signal that new message arrived
		if (os_semaphore_take(g_ipc_s2m_signal_semaphore, max_U64)) {
			// Acquire lock to read shared memory
			if (os_semaphore_take(g_ipc_s2m_lock_semaphore, max_U64)) {
				IPCInfo* ipc_info = (IPCInfo*)g_ipc_s2m_shared_memory_base;
				String8  msg = str8((U8*)(ipc_info + 1), ipc_info->msg_size);
				msg.size = Min(msg.size, IPC_SHARED_MEMORY_BUFFER_SIZE - sizeof(IPCInfo));

				// Copy message to ring buffer
				MutexScope(g_ipc_ring_mutex) {
					for (;;) {
						U64 unconsumed_size = g_ipc_ring_write_pos - g_ipc_ring_read_pos;
						U64 available_size = sizeof(g_ipc_ring_buffer) - unconsumed_size;
						if (available_size >= sizeof(U64) + msg.size) {
							g_ipc_ring_write_pos += ring_write_struct(
								g_ipc_ring_buffer, sizeof(g_ipc_ring_buffer), g_ipc_ring_write_pos, &msg.size);
							g_ipc_ring_write_pos += ring_write(
								g_ipc_ring_buffer, sizeof(g_ipc_ring_buffer), g_ipc_ring_write_pos, msg.str, msg.size);
							break;
						}
						os_cond_var_wait(g_ipc_ring_cv, g_ipc_ring_mutex, max_U64);
					}
				}
				os_cond_var_broadcast(g_ipc_ring_cv);

				// Notify main thread
				PostThreadMessage(g_main_thread_id, WM_IPC_MESSAGE, 0, 0);

				// Clear message and release lock
				ipc_info->msg_size = 0;
				os_semaphore_drop(g_ipc_s2m_lock_semaphore);
			}
		}
	}
}

////////////////////////////////
//~ IPC Init (Main Instance)

internal B32 ipc_init_main_instance(void) {
	Temp scratch = temp_begin(g_temp_arena);
	U32  pid = GetCurrentProcessId();

	//- sender -> main channel
	String8 s2m_shm_name = push_str8f(scratch.arena, IPC_S2M_SHM_NAME, pid);
	String8 s2m_signal_sem_name = push_str8f(scratch.arena, IPC_S2M_SIGNAL_SEM_NAME, pid);
	String8 s2m_lock_sem_name = push_str8f(scratch.arena, IPC_S2M_LOCK_SEM_NAME, pid);

	OS_Handle s2m_shm = os_shared_memory_alloc(IPC_SHARED_MEMORY_BUFFER_SIZE, s2m_shm_name);
	g_ipc_s2m_shared_memory_base = (U8*)os_shared_memory_view_open(s2m_shm, r1u64(0, IPC_SHARED_MEMORY_BUFFER_SIZE));
	g_ipc_s2m_signal_semaphore = os_semaphore_alloc(0, 1, s2m_signal_sem_name);
	g_ipc_s2m_lock_semaphore = os_semaphore_alloc(1, 1, s2m_lock_sem_name);

	//- main -> sender channel (responses)
	String8 m2s_shm_name = push_str8f(scratch.arena, IPC_M2S_SHM_NAME, pid);
	String8 m2s_signal_sem_name = push_str8f(scratch.arena, IPC_M2S_SIGNAL_SEM_NAME, pid);
	String8 m2s_lock_sem_name = push_str8f(scratch.arena, IPC_M2S_LOCK_SEM_NAME, pid);

	OS_Handle m2s_shm = os_shared_memory_alloc(IPC_SHARED_MEMORY_BUFFER_SIZE, m2s_shm_name);
	g_ipc_m2s_shared_memory_base = (U8*)os_shared_memory_view_open(m2s_shm, r1u64(0, IPC_SHARED_MEMORY_BUFFER_SIZE));
	g_ipc_m2s_signal_semaphore = os_semaphore_alloc(0, 1, m2s_signal_sem_name);
	g_ipc_m2s_lock_semaphore = os_semaphore_alloc(1, 1, m2s_lock_sem_name);

	//- ring buffer synchronization
	g_ipc_ring_mutex = os_mutex_alloc();
	g_ipc_ring_cv = os_cond_var_alloc();

	if (g_ipc_s2m_shared_memory_base != 0 && g_ipc_m2s_shared_memory_base != 0) {
		MemoryZero(g_ipc_s2m_shared_memory_base, IPC_SHARED_MEMORY_BUFFER_SIZE);
		MemoryZero(g_ipc_m2s_shared_memory_base, IPC_SHARED_MEMORY_BUFFER_SIZE);
		os_thread_launch(ipc_listener_thread_entry, 0);
		printf("IPC: initialized (pid=%u)\n", pid);
		temp_end(scratch);
		return 1;
	}

	temp_end(scratch);
	return 0;
}

////////////////////////////////
//~ IPC Find Other Instance

#include <tlhelp32.h>

internal B32 ipc_instance_has_server(U32 pid) {
	String8   name = push_str8f(g_temp_arena, IPC_S2M_SIGNAL_SEM_NAME, pid);
	Semaphore sem = os_semaphore_open(name);
	os_semaphore_close(sem);
	return (sem.u64[0] != 0);
}

internal U32 ipc_find_other_instance(void) {
	U32 result = 0;
	U32 this_pid = GetCurrentProcessId();

	// Get our own exe name
	wchar_t this_exe_path[MAX_PATH] = {0};
	GetModuleFileNameW(NULL, this_exe_path, MAX_PATH);
	wchar_t* this_exe_name = wcsrchr(this_exe_path, L'\\');
	if (this_exe_name)
		this_exe_name++;
	else
		this_exe_name = this_exe_path;

	// Iterate all processes with matching exe name, pick the one that has IPC server
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshot != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32W entry = {0};
		entry.dwSize = sizeof(entry);

		if (Process32FirstW(snapshot, &entry)) {
			do {
				if (entry.th32ProcessID != this_pid && _wcsicmp(entry.szExeFile, this_exe_name) == 0) {
					if (ipc_instance_has_server(entry.th32ProcessID)) {
						result = entry.th32ProcessID;
						break;
					}
				}
			} while (Process32NextW(snapshot, &entry));
		}
		CloseHandle(snapshot);
	}

	return result;
}

////////////////////////////////
//~ IPC Sender Mode

internal int ipc_send_message(U32 target_pid, String8 message) {
	Temp scratch = temp_begin(arena_alloc());
	int  result = 0;

	//- Open sender -> main channel
	String8 s2m_shm_name = push_str8f(scratch.arena, IPC_S2M_SHM_NAME, target_pid);
	String8 s2m_signal_sem_name = push_str8f(scratch.arena, IPC_S2M_SIGNAL_SEM_NAME, target_pid);
	String8 s2m_lock_sem_name = push_str8f(scratch.arena, IPC_S2M_LOCK_SEM_NAME, target_pid);

	OS_Handle s2m_shm = os_shared_memory_open(s2m_shm_name);
	U8*       s2m_base = (U8*)os_shared_memory_view_open(s2m_shm, r1u64(0, IPC_SHARED_MEMORY_BUFFER_SIZE));
	Semaphore s2m_signal_sem = os_semaphore_open(s2m_signal_sem_name);
	Semaphore s2m_lock_sem = os_semaphore_open(s2m_lock_sem_name);

	//- Open main -> sender channel (for response)
	String8 m2s_shm_name = push_str8f(scratch.arena, IPC_M2S_SHM_NAME, target_pid);
	String8 m2s_signal_sem_name = push_str8f(scratch.arena, IPC_M2S_SIGNAL_SEM_NAME, target_pid);
	String8 m2s_lock_sem_name = push_str8f(scratch.arena, IPC_M2S_LOCK_SEM_NAME, target_pid);

	OS_Handle m2s_shm = os_shared_memory_open(m2s_shm_name);
	U8*       m2s_base = (U8*)os_shared_memory_view_open(m2s_shm, r1u64(0, IPC_SHARED_MEMORY_BUFFER_SIZE));
	Semaphore m2s_signal_sem = os_semaphore_open(m2s_signal_sem_name);
	Semaphore m2s_lock_sem = os_semaphore_open(m2s_lock_sem_name);

	if (s2m_base == 0 || s2m_signal_sem.u64[0] == 0 || s2m_lock_sem.u64[0] == 0) {
		printf("IPC: failed to connect to instance (pid=%u)\n", target_pid);
		result = 1;
		goto cleanup;
	}

	//- Send message
	B32 wrote_message = 0;
	if (os_semaphore_take(s2m_lock_sem, max_U64)) {
		IPCInfo* ipc_info = (IPCInfo*)s2m_base;
		U8*      buffer = (U8*)(ipc_info + 1);
		U64      buffer_max = IPC_SHARED_MEMORY_BUFFER_SIZE - sizeof(IPCInfo);

		ipc_info->msg_size = Min(buffer_max, message.size);
		MemoryCopy(buffer, message.str, ipc_info->msg_size);

		os_semaphore_drop(s2m_signal_sem);
		os_semaphore_drop(s2m_lock_sem);
		wrote_message = 1;

		printf("IPC: sent \"%.*s\"\n", str8_varg(message));
	}

	//- Wait for response
	if (wrote_message && m2s_base != 0 && m2s_signal_sem.u64[0] != 0) {
		U64 timeout_us = os_now_microseconds() + IPC_RESPONSE_TIMEOUT_US;
		if (os_semaphore_take(m2s_signal_sem, timeout_us)) {
			if (os_semaphore_take(m2s_lock_sem, max_U64)) {
				IPCInfo* ipc_info = (IPCInfo*)m2s_base;
				String8  response = str8((U8*)(ipc_info + 1), ipc_info->msg_size);
				response.size = Min(response.size, IPC_SHARED_MEMORY_BUFFER_SIZE - sizeof(IPCInfo));

				// Output response to stdout
				if (response.size > 0) {
					fwrite(response.str, 1, response.size, stdout);
					fwrite("\n", 1, 1, stdout);
					fflush(stdout);
				}

				ipc_info->msg_size = 0;
				os_semaphore_drop(m2s_lock_sem);
			}
		}
		else {
			printf("IPC: response timeout\n");
		}
	}

cleanup:
	//- Cleanup sender -> main
	if (s2m_base)
		os_shared_memory_view_close(s2m_shm, s2m_base, r1u64(0, IPC_SHARED_MEMORY_BUFFER_SIZE));
	if (s2m_shm.u64[0])
		os_shared_memory_close(s2m_shm);
	if (s2m_signal_sem.u64[0])
		os_semaphore_close(s2m_signal_sem);
	if (s2m_lock_sem.u64[0])
		os_semaphore_close(s2m_lock_sem);

	//- Cleanup main -> sender
	if (m2s_base)
		os_shared_memory_view_close(m2s_shm, m2s_base, r1u64(0, IPC_SHARED_MEMORY_BUFFER_SIZE));
	if (m2s_shm.u64[0])
		os_shared_memory_close(m2s_shm);
	if (m2s_signal_sem.u64[0])
		os_semaphore_close(m2s_signal_sem);
	if (m2s_lock_sem.u64[0])
		os_semaphore_close(m2s_lock_sem);

	temp_end(scratch);
	return result;
}

////////////////////////////////
//~ IPC Message Handler (called from main loop)

internal void ipc_process_pending_messages(void) {
	Temp scratch = temp_begin(g_temp_arena);

	for (;;) {
		String8 msg = {0};
		B32     has_message = 0;

		MutexScope(g_ipc_ring_mutex) {
			U64 unconsumed_size = g_ipc_ring_write_pos - g_ipc_ring_read_pos;
			if (unconsumed_size >= sizeof(U64)) {
				has_message = 1;
				g_ipc_ring_read_pos +=
					ring_read_struct(g_ipc_ring_buffer, sizeof(g_ipc_ring_buffer), g_ipc_ring_read_pos, &msg.size);
				msg.size = Min(msg.size, unconsumed_size - sizeof(U64));
				msg.str = push_array(scratch.arena, U8, msg.size);
				g_ipc_ring_read_pos +=
					ring_read(g_ipc_ring_buffer, sizeof(g_ipc_ring_buffer), g_ipc_ring_read_pos, msg.str, msg.size);
			}
		}

		if (has_message) {
			os_cond_var_broadcast(g_ipc_ring_cv);
		}

		if (msg.size == 0) {
			break;
		}

		printf("IPC: received: \"%.*s\"\n", str8_varg(msg));

		String8 response = {0};
		if (run_command(scratch.arena, msg)) {
			response = str8f(scratch.arena, "OK: command handled");
		}
		else {
			response = str8f(scratch.arena, "ERROR: failed to parse command");
		}
		ipc_send_response(response);
	}

	temp_end(scratch);
}

////////////////////////////////
//~ IPC Send Response (main -> sender)

internal void ipc_send_response(String8 response) {
	if (g_ipc_m2s_shared_memory_base == 0)
		return;

	if (os_semaphore_take(g_ipc_m2s_lock_semaphore, max_U64)) {
		IPCInfo* ipc_info = (IPCInfo*)g_ipc_m2s_shared_memory_base;
		U8*      buffer = (U8*)(ipc_info + 1);
		U64      buffer_max = IPC_SHARED_MEMORY_BUFFER_SIZE - sizeof(IPCInfo);

		ipc_info->msg_size = Min(buffer_max, response.size);
		MemoryCopy(buffer, response.str, ipc_info->msg_size);

		os_semaphore_drop(g_ipc_m2s_signal_semaphore); // Signal sender
		os_semaphore_drop(g_ipc_m2s_lock_semaphore);

		printf("IPC: sent response: \"%.*s\"\n", str8_varg(response));
	}
}
internal String8 get_config_path(Arena* temp_arena) {
	OS_ProcessInfo* process_info = os_get_process_info();
	String8 raw = str8_cat(temp_arena, process_info->user_program_data_path, str8_lit("/WindowSpace/windowspace.toml"));
	String8 path = path_convert_slashes(temp_arena, raw, PathStyle_SystemAbsolute);
	return path;
}

#include "DefaultConfig.h"
internal B32 create_default_config(Arena* temp_arena) {
	printf("create_default_config\n");
	Temp scratch = temp_begin(temp_arena);

	String8 path = get_config_path(temp_arena);
	String8 dir = str8_chop_last_slash(path);
	if (!os_make_directory(dir)) {
		printf("Failed to create directory: %.*s\n", str8_varg(dir));
		return 0;
	}

	if (os_file_path_exists) {
		printf("Config file already exists: %.*s\n", str8_varg(path));
		return 0;
	}

	String8 default_config_data_str = str8((U8*)default_config_data, sizeof(default_config_data));
	B32     result = os_write_data_to_file_path(path, default_config_data_str);
	if (!result) {
		printf("Failed to write default config to file: %.*s\n", str8_varg(path));
		return 0;
	}

	temp_end(scratch);
	return result;
}

internal B32 parse_toml(Config* config, Arena* temp_arena) {
	printf("parse_toml\n");
	String8 path = get_config_path(temp_arena);
	String8 data = os_data_from_file_path(temp_arena, path);
	if (data.size == 0) {
		printf("Config not found or empty: %.*s\n", str8_varg(path));
		return 0;
	}

	// Toml17c requires NUL terminated string. fuck this shit.
	String8 data_nt = {0};
	data_nt.str = push_array_no_zero(temp_arena, U8, data.size + 1);
	data_nt.size = data.size;
	MemoryCopy(data_nt.str, data.str, data.size);
	data_nt.str[data.size] = 0;

	toml_result_t result = toml_parse((const char*)data_nt.str, (int)data_nt.size);
	if (!result.ok) {
		printf("Failed to parse TOML file: %s\n", result.errmsg);
		return 0;
	}

	CommandLayers* parsed_layers = push_array(config->arena, CommandLayers, 1);
	WndConfig*     parsed_wnd_configs = 0;
	U32            parsed_wnd_count = 0;

	toml_datum_t default_workspace_index = toml_get(result.toptab, "default-workspace-index");

	B32 is_valid_default_workspace_index = 0;
	if (default_workspace_index.type == TOML_STRING) {
		String8 default_workspace_index_str =
			str8((U8*)default_workspace_index.u.str.ptr, (U64)default_workspace_index.u.str.len);
		if (default_workspace_index_str.size == 1) {
			is_valid_default_workspace_index = 1;
			config->default_workspace_index = (U8)default_workspace_index_str.str[0];
		}
	}
	if (!is_valid_default_workspace_index) {
		config->default_workspace_index = '1';
	}

	toml_datum_t mode = toml_get(result.toptab, "mode");
	if (mode.type == TOML_TABLE) {
		for (int i = 0; i < mode.u.tab.size; i++) {
			String8 layer_key = str8((U8*)mode.u.tab.key[i], (U64)mode.u.tab.len[i]);
			if (!str8_is_integer(layer_key, 10)) {
				continue;
			}
			U32 layer_index = (U32)u64_from_str8(layer_key, 10);
			if (layer_index >= COMMAND_LAYERS_COUNT) {
				continue;
			}

			toml_datum_t layer = mode.u.tab.value[i];
			if (layer.type != TOML_TABLE) {
				continue;
			}

			toml_datum_t binding = toml_get(layer, "binding");
			if (binding.type != TOML_TABLE) {
				continue;
			}

			U32 command_index = 0;
			for (int j = 0; j < binding.u.tab.size; j++) {
				if (command_index >= COMMAND_BINDINGS_COUNT) {
					break;
				}

				toml_datum_t value = binding.u.tab.value[j];
				if (value.type != TOML_STRING) {
					continue;
				}

				String8 binding_key = str8((U8*)binding.u.tab.key[j], (U64)binding.u.tab.len[j]);
				String8 command_str = str8((U8*)value.u.str.ptr, (U64)value.u.str.len);

				String8List command_parts = parse_command_parts(temp_arena, command_str);
				Command     command = {0};
				command.arena = config->arena;
				if (!parse_command(command_parts, &command)) {
					continue;
				}

				CommandBinding new_binding = {0};
				if (!command_binding_create((char*)binding_key.str, &new_binding)) {
					continue;
				}
				parsed_layers->command_bindings[layer_index][command_index] = new_binding;
				parsed_layers->commands[layer_index][command_index] = command;
				command_index++;
			}
		}
	}

	toml_datum_t wnd_array = toml_get(result.toptab, "on-window-detected");
	if (wnd_array.type == TOML_ARRAY) {
		if (wnd_array.u.arr.size > 0) {
			parsed_wnd_configs = push_array(config->arena, WndConfig, wnd_array.u.arr.size);
			MemoryZero(parsed_wnd_configs, sizeof(WndConfig) * wnd_array.u.arr.size);
		}
		for (int i = 0; i < wnd_array.u.arr.size; i++) {
			toml_datum_t entry = wnd_array.u.arr.elem[i];
			if (entry.type != TOML_TABLE) {
				continue;
			}

			WndConfig    wnd_config = {0};
			toml_datum_t title = toml_get(entry, "title");
			toml_datum_t process = toml_get(entry, "process");
			toml_datum_t command_value = toml_get(entry, "command");

			if (title.type == TOML_STRING) {
				String8 title_str = str8((U8*)title.u.str.ptr, (U64)title.u.str.len);
				wnd_config.titleFilter = push_str8_copy(config->arena, title_str);
			}
			if (process.type == TOML_STRING) {
				String8 process_str = str8((U8*)process.u.str.ptr, (U64)process.u.str.len);
				wnd_config.processNameFilter = push_str8_copy(config->arena, process_str);
			}
			if (command_value.type == TOML_STRING) {
				String8     command_str = str8((U8*)command_value.u.str.ptr, (U64)command_value.u.str.len);
				String8List command_parts = parse_command_parts(temp_arena, command_str);
				wnd_config.command.arena = config->arena;
				if (!parse_command(command_parts, &wnd_config.command)) {
					continue;
				}
			}
			else {
				continue;
			}

			parsed_wnd_configs[parsed_wnd_count++] = wnd_config;
		}
	}

	toml_free(result);

	config->command_layers = parsed_layers;
	config->wnd_configs = parsed_wnd_configs;
	config->wnd_configs_count = parsed_wnd_count;
	return 1;
}

internal void keyboard_hook_thread_entry(void* p) {
	g_keyboard_thread_id = GetCurrentThreadId();
	{
		MSG msg = {0};
		PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE);
	}
	{
		Arena* arena = arena_alloc();
		g_keyboard_thread_state = push_array(arena, KeyboardHookThreadState, 1);
		g_keyboard_thread_state->arena = arena;
	}
	os_semaphore_drop(g_keyboard_thread_ready_semaphore);

	HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookProc, NULL, 0);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		switch (msg.message) {
			case WM_KEYHOOK_LAYER_CHANGE:
			{
				U32 layer_index = (U32)msg.wParam;
				g_keyboard_thread_state->current_layer_index = layer_index;
				break;
			}
			case WM_KEYHOOK_BINDINGS_UPDATE:
			{
				arena_release(g_keyboard_thread_state->arena);
				g_keyboard_thread_state = (KeyboardHookThreadState*)msg.lParam;
				os_semaphore_drop(g_keyboard_bindings_update_semaphore);
				break;
			}
			default:
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				break;
			}
		}
	}
	arena_release(g_keyboard_thread_state->arena);
	UnhookWindowsHookEx(hook);
}

////////////////////////////////
//~ Auto Launch

#define AUTO_LAUNCH_REG_KEY L"Software\\Microsoft\\Windows\\CurrentVersion\\Run"
#define AUTO_LAUNCH_REG_NAME L"WindowSpace"
#define AUTO_LAUNCH_TASK_NAME L"WindowSpace"

//- Registry (no admin)

internal int setup_auto_launch(void) {
	wchar_t exe_path[MAX_PATH] = {0};
	DWORD   len = GetModuleFileNameW(NULL, exe_path, MAX_PATH);
	if (len == 0 || len >= MAX_PATH) {
		printf("Error: failed to get executable path\n");
		return 1;
	}

	HKEY hkey = NULL;
	LONG status = RegOpenKeyExW(HKEY_CURRENT_USER, AUTO_LAUNCH_REG_KEY, 0, KEY_SET_VALUE, &hkey);
	if (status != ERROR_SUCCESS) {
		printf("Error: failed to open registry key (error %ld)\n", status);
		return 1;
	}

	DWORD byte_size = (DWORD)((wcslen(exe_path) + 1) * sizeof(wchar_t));
	status = RegSetValueExW(hkey, AUTO_LAUNCH_REG_NAME, 0, REG_SZ, (const BYTE*)exe_path, byte_size);
	RegCloseKey(hkey);

	if (status != ERROR_SUCCESS) {
		printf("Error: failed to set registry value (error %ld)\n", status);
		return 1;
	}

	printf("Auto launch enabled: %ls\n", exe_path);
	return 0;
}

//- Task Scheduler (admin)

internal int run_schtasks(const wchar_t* params) {
	SHELLEXECUTEINFOW sei = {0};
	sei.cbSize = sizeof(sei);
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	sei.lpVerb = L"runas";
	sei.lpFile = L"schtasks.exe";
	sei.lpParameters = params;
	sei.nShow = SW_HIDE;

	if (!ShellExecuteExW(&sei)) {
		DWORD err = GetLastError();
		if (err == ERROR_CANCELLED) {
			printf("Error: UAC elevation was cancelled by user\n");
		}
		else {
			printf("Error: failed to launch schtasks (error %lu)\n", err);
		}
		return 1;
	}

	WaitForSingleObject(sei.hProcess, INFINITE);
	DWORD exit_code = 0;
	GetExitCodeProcess(sei.hProcess, &exit_code);
	CloseHandle(sei.hProcess);

	return (int)exit_code;
}

internal int setup_auto_launch_admin(void) {
	wchar_t exe_path[MAX_PATH] = {0};
	DWORD   len = GetModuleFileNameW(NULL, exe_path, MAX_PATH);
	if (len == 0 || len >= MAX_PATH) {
		printf("Error: failed to get executable path\n");
		return 1;
	}

	wchar_t params[1024];
	swprintf(
		params, ArrayCount(params),
		L"/Create /TN \"" AUTO_LAUNCH_TASK_NAME L"\" "
		L"/TR \"\\\"%ls\\\"\" "
		L"/SC ONLOGON /RL HIGHEST /F",
		exe_path);

	int result = run_schtasks(params);
	if (result != 0) {
		printf("Error: schtasks failed (exit code %d)\n", result);
		return 1;
	}

	printf("Auto launch enabled with admin privileges: %ls\n", exe_path);
	return 0;
}

//- Remove (cleans up both registry and task scheduler)

internal int remove_auto_launch(void) {
	B32 removed_any = 0;

	//- Remove registry entry
	{
		HKEY hkey = NULL;
		LONG status = RegOpenKeyExW(HKEY_CURRENT_USER, AUTO_LAUNCH_REG_KEY, 0, KEY_SET_VALUE, &hkey);
		if (status == ERROR_SUCCESS) {
			status = RegDeleteValueW(hkey, AUTO_LAUNCH_REG_NAME);
			RegCloseKey(hkey);
			if (status == ERROR_SUCCESS) {
				printf("Removed auto launch from registry\n");
				removed_any = 1;
			}
		}
	}

	//- Remove scheduled task
	{
		wchar_t params[512];
		swprintf(params, ArrayCount(params), L"/Delete /TN \"" AUTO_LAUNCH_TASK_NAME L"\" /F");

		int result = run_schtasks(params);
		if (result == 0) {
			printf("Removed auto launch from task scheduler\n");
			removed_any = 1;
		}
	}

	if (!removed_any) {
		printf("Auto launch was not set\n");
	}
	else {
		printf("Auto launch disabled\n");
	}
	return 0;
}

internal void print_help(Arena* temp_arena) {
	printf("Usage: windowspace [options] [--ipc [--pid <pid>] <command>]\n");
	printf("\nOptions:\n");
	printf("  --help                         Show this help message\n");
	printf("  --version                      Show version information\n");
	printf("  --create-default-config        Create default config file\n");
	printf("  --setup-auto-launch            Register program to start with Windows\n");
	printf("  --setup-auto-launch-admin      Register program to start with Windows (admin)\n");
	printf("  --remove-auto-launch           Remove program from Windows startup\n");
	printf("  --ipc [--pid <pid>] <command>  Send IPC command\n");
	String8List command_list = command_list_str(g_temp_arena, g_temp_arena);
	printf("\nIPC Commands:\n");
	for (String8Node* node = command_list.first; node != NULL; node = node->next) {
		printf("  %.*s\n", str8_varg(node->string));
	}
}
int main(int argc, char** argv) {
	SetConsoleOutputCP(CP_UTF8);
	g_main_thread_id = os_tid();
	g_temp_arena = arena_alloc();
	init_command_table();
	init_command_arg_type_names();
	//- Parse command line for IPC mode
	ExecMode exec_mode = ExecMode_Normal;
	U32      ipc_target_pid = 0;
	String8  ipc_message = {0};

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--help") == 0) {
			print_help(g_temp_arena);
			return 0;
		}
		else if (strcmp(argv[i], "--version") == 0) {
			printf("windowspace %s\n", WINDOWSPACE_VERSION);
			return 0;
		}
		else if (strcmp(argv[i], "--create-default-config") == 0) {
			return !create_default_config(g_temp_arena);
		}
		else if (strcmp(argv[i], "--setup_auto_launch") == 0) {
			return setup_auto_launch();
		}
		else if (strcmp(argv[i], "--setup_auto_launch_admin") == 0) {
			return setup_auto_launch_admin();
		}
		else if (strcmp(argv[i], "--remove_auto_launch") == 0) {
			return remove_auto_launch();
		}
		else if (strcmp(argv[i], "--ipc") == 0) {
			exec_mode = ExecMode_IPCSender;
		}
		else if (strcmp(argv[i], "--pid") == 0 && i + 1 < argc) {
			ipc_target_pid = (U32)atoi(argv[++i]);
		}
		else if (exec_mode == ExecMode_IPCSender && ipc_message.size == 0) {
			// Remaining args are the message
			String8List parts = {0};
			for (int j = i; j < argc; j++) {
				str8_list_push(g_temp_arena, &parts, str8_cstring(argv[j]));
			}
			StringJoin join = {str8_lit(""), str8_lit(" "), str8_lit("")};
			ipc_message = str8_list_join(g_temp_arena, &parts, &join);
			break;
		}
		else if(strlen(argv[i]) > 0){
			printf("Unknown option: %s\n", argv[i]);
			print_help(g_temp_arena);
			return 1;
		}
	}

	//- IPC Sender mode: send message and exit
	if (exec_mode == ExecMode_IPCSender) {
		if (ipc_message.size == 0) {
			printf("Error: no message provided\n");
			printf("Usage: windowspace --ipc [--pid <pid>] <message>\n");
			return 1;
		}

		// Auto-detect PID if not specified
		if (ipc_target_pid == 0) {
			ipc_target_pid = ipc_find_other_instance();
			if (ipc_target_pid == 0) {
				printf("Error: no running windowspace instance found\n");
				return 1;
			}
			printf("IPC: auto-detected instance pid=%u\n", ipc_target_pid);
		}

		return ipc_send_message(ipc_target_pid, ipc_message);
	}
	printf("Starting windowspace %s\n", WINDOWSPACE_VERSION);

	g_config = (Config){0};
	g_config.arena = arena_alloc();
	if (!parse_toml(&g_config, g_temp_arena)) {
		printf("Failed to parse config\n");
		return 1;
	}
	g_state.arena = arena_alloc();
	g_state.workspaces = push_array(g_state.arena, WorkspacesData, 1);
	g_state.windows_list = push_array(g_state.arena, WindowsList, 1);
	g_state.windows_list->arena = g_state.arena;
	g_state.workspaces->active_workspace_index = g_config.default_workspace_index;
	g_main_hwnd = GetConsoleWindow();
	tray_init(g_main_hwnd, g_state.workspaces->active_workspace_index);
	EnumWindows(init_enum_windows, (LPARAM)&g_state.windows_list);
	{
		Command initial_command = {0};
		initial_command.type = CommandType_WorkspaceFocus;
		initial_command.workspace_index = g_state.workspaces->active_workspace_index;
		handle_command(&initial_command);
	}
	g_keyboard_bindings_update_semaphore = os_semaphore_alloc(1, 1, str8_zero());
	g_keyboard_thread_ready_semaphore = os_semaphore_alloc(0, 1, str8_zero());
	Thread keyboard_hook_thread = os_thread_launch(keyboard_hook_thread_entry, NULL);
	os_semaphore_take(g_keyboard_thread_ready_semaphore, max_U64);
	keyboard_hook_post_bindings_update();
	//- Normal mode: initialize IPC listener
	ipc_init_main_instance();

	HWINEVENTHOOK win_hook = SetWinEventHook(
		EVENT_SYSTEM_FOREGROUND,                          // 0x0003
														  // EVENT_OBJECT_CREATE,        // 0x8000
		EVENT_OBJECT_NAMECHANGE,                          // 0x800C
		NULL,                                             // Handle to DLL.
		HandleWinEvent,                                   // The callback.
		0, 0,                                             // Process and thread IDs of interest (0 = all)
		WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS); // Flags.

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		switch (msg.message) {
			case WM_INPUT_COMMAND:
			{
				U32             command_index = (U32)msg.lParam;
				CommandBinding* current_bindings = command_layers_get_current_bindings(g_config.command_layers);
				Command*        current_commands = command_layers_get_current_commands(g_config.command_layers);
				Command*        command = &current_commands[command_index];
				printf("Run command: ");
				print_keycodes_sorted(current_bindings[command_index].keycodes);
				printf("\n");
				handle_command(command);
				break;
			}
			case WM_IPC_MESSAGE:
			{
				ipc_process_pending_messages();
				break;
			}
			default:
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				break;
			}
		}
		arena_clear(g_temp_arena);
	}
	os_thread_join(keyboard_hook_thread, 0);
	UnhookWinEvent(win_hook);
	tray_cleanup();
	arena_release(g_state.arena);
	arena_release(g_config.arena);
	return 0;
}
