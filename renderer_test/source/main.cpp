/**
 * @file main.cpp
 * @author khalilhenoud@gmail.com
 * @brief base test for renderer.
 * @version 0.1
 * @date 2023-01-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <windows.h>
#include <application.h>
#include <renderer/renderer_opengl.h>
#include <renderer/platform/opengl_platform.h>


HWND		g_hWnd;
HDC			g_hWindowDC;

void 
ComputeWindowPosition(
  int32_t &x, 
  int32_t &y, 
  int32_t width, 
  int32_t height,
  int32_t screen_width,
  int32_t screen_height)
{
  x = y = 0;
	if (screen_width <= width || screen_width <= height)
    return;

	x = (screen_width - width)/2;
	y = (screen_height - height)/2;
}

LRESULT 
CALLBACK 
WndProc(
  HWND g_hWnd, 
  UINT message, 
  WPARAM wParam, 
  LPARAM lParam)
{
	switch (message) {
    case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(g_hWnd, message, wParam, lParam);
	}

	return 0;
}

int 
APIENTRY 
WinMain(
  HINSTANCE hInstance, 
  HINSTANCE hPrevInstance, 
  PSTR lpCmdLine, 
  int nCmdShow)
{
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = 0;
	wcex.hCursor = LoadCursor(0, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = "OGL";
	wcex.hIconSm = 0;
	RegisterClassEx(&wcex);

  int32_t screenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
  int32_t screenHeight = GetSystemMetrics(SM_CYFULLSCREEN);
  int32_t client_width = screenWidth/2;
  int32_t client_height = screenHeight/2;
	RECT r = { 0, 0, client_width, client_height };
  AdjustWindowRect(&r, WS_CAPTION, FALSE);
	int32_t x, y;
	ComputeWindowPosition(x, y, client_width, client_height, screenWidth, screenHeight);
  g_hWnd = CreateWindow("OGL", "", WS_CAPTION, x, y, r.right - r.left, r.bottom - r.top, 0, 0, hInstance, 0);

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	g_hWindowDC = GetDC(g_hWnd);

  opengl_parameters_t params{&g_hWindowDC};
  opengl_initialize(&params);
  app_initialize(client_width, client_height);

	MSG msg;
	while (true) {
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
				goto End;
			else
				DispatchMessage(&msg);
		}

    if (GetAsyncKeyState(VK_ESCAPE)) {
      PostQuitMessage(0);
      continue;
    }

    app_update();
    opengl_swapbuffer();
	}

End:
  app_cleanup();
  opengl_cleanup();
	ReleaseDC(g_hWnd, g_hWindowDC);

	return (int)msg.wParam;
}
