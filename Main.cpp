#include "Win.h"

int main() {
	HWND hwnd = CreateWin(L"Node System");

	MSGLoop();

	return 0;
}