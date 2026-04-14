#include <windows.h>
#include <gl/GL.h>

extern unsigned char xbox_memory_blob[];

// Window + OpenGL created here (exe's main thread) then passed to DLL
static HWND  g_hWnd = NULL;
static HDC   g_hDC = NULL;
static HGLRC g_hRC = NULL;

static void create_gpu_window(void)
{
    g_hWnd = CreateWindowExA(0, "STATIC", "HXE - Xbox Emulator",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100, 100, 640, 480, NULL, NULL, NULL, NULL);

    if (!g_hWnd) return;

    g_hDC = GetDC(g_hWnd);

    PIXELFORMATDESCRIPTOR pfd = { 0 };
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;

    int format = ChoosePixelFormat(g_hDC, &pfd);
    SetPixelFormat(g_hDC, format, &pfd);

    g_hRC = wglCreateContext(g_hDC);
    wglMakeCurrent(g_hDC, g_hRC);
}

typedef void (*EmulateFn)(HWND, HDC);

DWORD CALLBACK rawMain(void)
{
    (void)xbox_memory_blob;

    create_gpu_window();

    HMODULE dll = LoadLibraryA("Xemu-dll.dll");
    if (!dll) {
        OutputDebugStringA("HXE: Failed to load Xemu-dll.dll\n");
        return 1;
    }

    EmulateFn Emulate = (EmulateFn)GetProcAddress(dll, "Emulate");
    if (!Emulate) {
        OutputDebugStringA("HXE: Failed to find Emulate in DLL\n");
        return 1;
    }

    Emulate(g_hWnd, g_hDC);
    return 0;
}
