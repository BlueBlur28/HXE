#pragma once
#include <windows.h>
#include <stdint.h>

void gpu_set_window(HWND hWnd, HDC hDC);
void gpu_patch_pbkit(void);
void gpu_dump_pbkit_patterns(void);
void gpu_patch_d3d(void* xbe_header);
