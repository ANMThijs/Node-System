#include "Win.h"

Engine eng;

LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
	HDC hdc = NULL;
	HGLRC hrc = NULL;
	switch (umsg) {
	case WM_MOUSEMOVE:
		hdc = GetDC(hwnd);

		eng.OnMouseMove();

		SwapBuffers(hdc);
		break;
	case WM_HOTKEY:
		hdc = GetDC(hwnd);

		eng.OnHotKey(wparam);

		SwapBuffers(hdc);
		break;
	case WM_KEYDOWN:
		hdc = GetDC(hwnd);

		eng.OnKey();

		SwapBuffers(hdc);
		break;
	case WM_LBUTTONDOWN:
		hdc = GetDC(hwnd);

		eng.OnLMouse();

		SwapBuffers(hdc);
		break;
	case WM_PAINT:
		hdc = GetDC(hwnd);

		eng.Render();

		SwapBuffers(hdc);
		break;
	case WM_CREATE:
		SetHotKeys(hwnd);

		hdc = GetDC(hwnd);
		hrc = CreateGLCont(hwnd);
		wglMakeCurrent(hdc, hrc);

		eng.Init();
		break;
	case WM_DESTROY:
		eng.Destroy();
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hrc);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProcW(hwnd, umsg, wparam, lparam);
}

void SetHotKeys(HWND hwnd) {
	RegisterHotKey(hwnd, HK_VPMODE_DEFAULT, MOD_ALT | MOD_CONTROL, 'D');
	RegisterHotKey(hwnd, HK_VPMODE_DRAW_NODE, MOD_ALT | MOD_CONTROL, 'T');
	RegisterHotKey(hwnd, HK_VPMODE_DRAW_WIRE, MOD_ALT | MOD_CONTROL, 'W');
	RegisterHotKey(hwnd, HK_DRAW_WIRE, MOD_CONTROL, 'W');
	RegisterHotKey(hwnd, HK_SELECT_BOX, MOD_CONTROL, 'B');
}

void DelHotKeys(HWND hwnd) {
	UnregisterHotKey(hwnd, HK_VPMODE_DEFAULT);
	UnregisterHotKey(hwnd, HK_VPMODE_DRAW_NODE);
	UnregisterHotKey(hwnd, HK_VPMODE_DRAW_WIRE);
	UnregisterHotKey(hwnd, HK_DRAW_WIRE);
	UnregisterHotKey(hwnd, HK_SELECT_BOX);
}

HWND CreateWin(const wchar_t* Title) {
	int winx = GetSystemMetrics(SM_CXSCREEN);
	int winy = GetSystemMetrics(SM_CYSCREEN);

	HINSTANCE hInst = GetModuleHandleW(NULL);

	WNDCLASS wc = {};

	wc.hInstance = hInst;
	wc.lpszClassName = L"Main class";
	wc.lpfnWndProc = WndProc;

	RegisterClassW(&wc);

	HWND hwnd = CreateWindowExW(0, wc.lpszClassName, Title,
		WS_VISIBLE | WS_OVERLAPPEDWINDOW | WS_MAXIMIZE,
		0, 0, winx, winy,
		NULL, NULL, hInst, NULL);

	return hwnd;
}

void MSGLoop() {
	MSG msg = { };
	while (GetMessageW(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

HGLRC CreateGLCont(HWND hwnd) {
	HWND dhwnd = CreateDummyWin(hwnd);

	glewInit();

	PIXELFORMATDESCRIPTOR pfd = {};

	HDC hdc = GetDC(hwnd);

	int attribslist[] = {
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		WGL_SAMPLE_BUFFERS_ARB, 1,
		WGL_SAMPLES_ARB, 0,
		0
	};

	int iPixFor;
	UINT numfor;

	wglChoosePixelFormatARB(hdc, attribslist, NULL, 1, &iPixFor, &numfor);
	SetPixelFormat(hdc, iPixFor, &pfd);

	int attribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 2,
		WGL_CONTEXT_MINOR_VERSION_ARB, 1,
		WGL_CONTEXT_FLAGS_ARB, 0,
		0
	};

	HGLRC hrc = wglCreateContextAttribsARB(hdc, 0, attribs);

	DestroyWindow(dhwnd);

	return hrc;
}

HWND CreateDummyWin(HWND parent) {
	WNDCLASS dwc = {};

	dwc.lpfnWndProc = DummyProc;
	dwc.lpszClassName = L"Dummy class";

	RegisterClassW(&dwc);

	HWND dhwnd = CreateWindowExW(0, dwc.lpszClassName, NULL,
		WS_CHILD,
		0, 0, 0, 0,
		parent, NULL, NULL, NULL);

	return dhwnd;
}

LRESULT CALLBACK DummyProc(HWND dhwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
	HDC dhdc = GetDC(dhwnd);
	HGLRC hrc = NULL;
	switch (umsg) {
	case WM_CREATE:
		hrc = CreateDummyCont(dhdc);

		wglMakeCurrent(dhdc, hrc);
		break;
	case WM_DESTROY:
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hrc);
		break;
	}
	return DefWindowProcW(dhwnd, umsg, wparam, lparam);
}

HGLRC CreateDummyCont(HDC hdc) {
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
		PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
		32,                   // Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                   // Number of bits for the depthbuffer
		8,                    // Number of bits for the stencilbuffer
		0,                    // Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	int iPixFor = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, iPixFor, &pfd);

	HGLRC hrc = wglCreateContext(hdc);

	return hrc;
}