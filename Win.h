#include <gl/glew.h>
#include <gl/wglew.h>
#include <Windows.h>

#include "Engine.h"

/*Main window creation functions*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

void SetHotKeys(HWND hwnd);
void DelHotKeys(HWND hwnd);

HWND CreateWin(const wchar_t* Title);

void MSGLoop();

HGLRC CreateGLCont(HWND hwnd);

/*Dummy context function, shouldn't need any changes*/
HWND CreateDummyWin(HWND parent);

LRESULT CALLBACK DummyProc(HWND dhwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

HGLRC CreateDummyCont(HDC hdc);