#ifndef WINDOWSPACE_H
#define WINDOWSPACE_H

#define WINDOWSPACE_VERSION "v0.1.6"

#define KEYCODES_COUNT 256
// Unsorted list of keycodes as values
// VK_B, VK_A, VK_C, ...
typedef U8 KeycodesUnsorted[KEYCODES_COUNT];
// Each keycode is index in the list. Values is state
// ..., VK_A, VK_B, VK_C, ...
// ..., 1,       0,    1, ...
typedef U8 KeycodesSparseMap[KEYCODES_COUNT];
// Sorted list of keycodes as values
// VK_A, VK_B, VK_C, ...
typedef U8 KeycodesSorted[KEYCODES_COUNT];

typedef struct WindowState WindowState;
const char*                wnd_get_info_string(Arena* arena, HWND hwnd);
const char*                wnd_get_state_info_string(Arena* arena, WindowState* window_state);

typedef enum CommandType CommandType;
enum CommandType {
	CommandType_None = 0,
	CommandType_WorkspaceFocus,
	CommandType_WorkspaceMove,
	CommandType_WorkspaceBackAndForth,
	CommandType_WindowFocusNext,
	CommandType_WindowFocusPrev,
	CommandType_WindowClose,
	CommandType_BindingLayerChange,
	CommandType_Subprocess,
	CommandType_ReloadConfig,
	CommandType_COUNT,
};

typedef enum CommandArgType CommandArgType;
enum CommandArgType {
	CommandArgType_None = 0,
	CommandArgType_Int,
	CommandArgType_Char,
	CommandArgType_String,
	CommandArgType_COUNT,
};

typedef struct CommandTable CommandTable;
struct CommandTable {
	String8        name;
	CommandArgType arg_type;
	String8        description;
};

internal CommandTable g_command_table[CommandType_COUNT];

void init_command_table() {
	CommandTable command_table[CommandType_COUNT] = {
		{str8_lit("none"), CommandArgType_None},
		{str8_lit("workspace_focus"), CommandArgType_Char, str8_lit("Focus workspace by index")},
		{str8_lit("workspace_move"), CommandArgType_Char, str8_lit("Move window to workspace by index")},
		{str8_lit("workspace_back_and_forth"), CommandArgType_None,
		 str8_lit("Focus between current and previous workspaces")},
		{str8_lit("window_focus_next"), CommandArgType_None, str8_lit("Focus next window")},
		{str8_lit("window_focus_prev"), CommandArgType_None, str8_lit("Focus previous window")},
		{str8_lit("window_close"), CommandArgType_None, str8_lit("Close window")},
		{str8_lit("binding_layer_change"), CommandArgType_Int, str8_lit("Change binding layer by index")},
		{str8_lit("subprocess"), CommandArgType_String, str8_lit("Run subprocess")},
		{str8_lit("reload_config"), CommandArgType_None, str8_lit("Reload config file")},
	};
	MemoryCopyArray(g_command_table, command_table);
}

String8 command_type_name(CommandType type) {
	return g_command_table[type].name;
}

CommandType command_type_from_name(String8 name) {
	for (int i = 1; i < CommandType_COUNT; i++) {
		if (str8_equals(g_command_table[i].name, name)) {
			return (CommandType)i;
		}
	}
	return CommandType_None;
}

internal String8 g_command_arg_type_names[CommandArgType_COUNT];

void init_command_arg_type_names() {
	g_command_arg_type_names[CommandArgType_None] = str8_lit("none");
	g_command_arg_type_names[CommandArgType_Int] = str8_lit("int");
	g_command_arg_type_names[CommandArgType_Char] = str8_lit("char");
	g_command_arg_type_names[CommandArgType_String] = str8_lit("string");
}

String8 command_arg_type_name(CommandArgType type) {
	return g_command_arg_type_names[type];
}

CommandArgType command_arg_type_from_name(String8 name) {
	for (int i = 1; i < CommandArgType_COUNT; i++) {
		if (str8_equals(g_command_arg_type_names[i], name)) {
			return (CommandArgType)i;
		}
	}
	return CommandArgType_None;
}

String8List command_list_str(Arena* arena, Arena* temp_arena) {
	String8List command_list = {0};

	// Step 1: Build left column strings
	String8 left_parts[CommandType_COUNT] = {0};
	U64     max_left_width = 0;
	for (int i = 1; i < CommandType_COUNT; i++) {
		String8 name = command_type_name((CommandType)i);
		if (g_command_table[i].arg_type == CommandArgType_None) {
			left_parts[i] = str8f(temp_arena, "%.*s", str8_varg(name));
		}
		else {
			String8 arg_type_name = command_arg_type_name(g_command_table[i].arg_type);
			left_parts[i] = str8f(temp_arena, "%.*s (<%.*s>)", str8_varg(name), str8_varg(arg_type_name));
		}
		if (left_parts[i].size > max_left_width) {
			max_left_width = left_parts[i].size;
		}
	}

	// Step 2: Combine with aligned descriptions
	for (int i = 1; i < CommandType_COUNT; i++) {
		int padding = (int)(max_left_width - left_parts[i].size);
		str8_list_push(
			arena, &command_list,
			str8f(
				arena, "%.*s%*s %.*s", str8_varg(left_parts[i]), padding, "",
				str8_varg(g_command_table[i].description)));
	}
	return command_list;
}

typedef struct Command Command;
struct Command {
	CommandType type;
	U32         workspace_index;
	String8     subprocess_command;
	Arena*      arena;
};

typedef struct WndConfig WndConfig;
struct WndConfig {
	String8 titleFilter;
	String8 processNameFilter;
	Command command;
};

typedef struct CommandBinding CommandBinding;
struct CommandBinding {
	KeycodesSorted keycodes;
};

#define COMMAND_LAYERS_COUNT 16
#define COMMAND_BINDINGS_COUNT 256
typedef struct CommandLayers CommandLayers;
struct CommandLayers {
	// Actually this is a lot of memory
	CommandBinding command_bindings[COMMAND_LAYERS_COUNT][COMMAND_BINDINGS_COUNT];
	Command        commands[COMMAND_LAYERS_COUNT][COMMAND_BINDINGS_COUNT];
};

typedef struct KeyboardHookThreadState KeyboardHookThreadState;
struct KeyboardHookThreadState {
	CommandBinding command_bindings[COMMAND_LAYERS_COUNT][COMMAND_BINDINGS_COUNT];
	U32            current_layer_index;
	Arena*         arena;
};

typedef struct Config Config;
struct Config {
	CommandLayers* command_layers;
	WndConfig*     wnd_configs;
	U32            wnd_configs_count;
	Arena*         arena;
	U32            default_workspace_index;
};

struct WindowState {
	HWND         hwnd;
	// @TASK: FOREGROUND EVENT IS SHIT
	// B32 is_minimizing;
	U32          workspace_index;
	U32          filter_index;
	WindowState* next;
	WindowState* next_free;
};

typedef struct WindowsList WindowsList;
struct WindowsList {
	Arena*       arena;
	WindowState* head;
	WindowState* first_free;
};

typedef struct Workspace Workspace;

struct Workspace {
	HWND active_window;
};

typedef struct WorkspacesData WorkspacesData;
struct WorkspacesData {
	Workspace workspaces[256];
	U32       active_workspace_index;
	U32       prev_active_workspace;
};

typedef struct State State;
struct State {
	U32             current_layer_index;
	Arena*          arena;
	WorkspacesData* workspaces;
	WindowsList*    windows_list;
};

void handle_command(Command* command);

#define WM_INPUT_COMMAND (WM_USER + 1)
#define WM_KEYHOOK_LAYER_CHANGE (WM_USER + 2)
#define WM_KEYHOOK_BINDINGS_UPDATE (WM_USER + 3)
#define WM_IPC_MESSAGE (WM_USER + 100)

#endif
