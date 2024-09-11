#include "pch.h"
#include "input.hpp"

menu_cfg cfg;
WndProc_sig og_wndproc;
PollEvents_sig PollEvents;

int HandleEvent(SDL_Event* sdl_event)
{
	const int status = PollEvents(sdl_event);

	if (cfg.menu_open)
	{
		ImGui_ImplSDL2_ProcessEvent(sdl_event);
		if (cfg.block_input) return 0;
	}

	return status;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_KEYDOWN && wParam == VK_INSERT)
	{
		SDL_SetRelativeMouseMode((SDL_bool)cfg.menu_open);

		cfg.menu_open = !cfg.menu_open;
		ImGui::GetIO().WantCaptureMouse = cfg.menu_open;
		ImGui::GetIO().WantCaptureKeyboard = cfg.menu_open;

		return true;
	} 

	return og_wndproc(hWnd, msg, wParam, lParam);
}