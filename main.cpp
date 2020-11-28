#include <iostream>
#include <windows.h>
#include <math.h>
#include <wingdi.h>

HDC hdc;


bool checkPixelGrey(int x, int y) {
	COLORREF color = GetPixel(hdc, x, y);
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);
	return r == g && r == b && g == b && r != 255;
}

int main() {
	hdc = GetDC(NULL);

	std::cout << "AutoTapper made by Marko Borkovic" << std::endl;
	POINT resPoints[2];
	int clicked = 0;
	std::cout << "Choose your coordinates(up arrow): " << std::endl;

	while (clicked < 2) {
		if (GetAsyncKeyState(VK_UP) < 0) {
			GetCursorPos(&resPoints[clicked++]);
			std::cout << "click" << std::endl;
			while (GetAsyncKeyState(VK_UP) < 0) {}
		}
	}

	int squareDelta = resPoints[1].x - resPoints[0].x;
	std::cout << "Click one: " << resPoints[0].x << ", " << resPoints[0].y << std::endl;
	std::cout << "Click two: " << resPoints[1].x << ", " << resPoints[1].y << std::endl;
	std::cout << "Square delta: " << squareDelta << std::endl;

	std::cout << "Press the right arrow to start and the left arrow to stop!" << std::endl;
	while (!GetAsyncKeyState(VK_RIGHT)) {}

	int zeroX = resPoints[0].x;
	int zeroY = resPoints[0].y;
	while (!GetAsyncKeyState(VK_LEFT)) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (checkPixelGrey(zeroX + squareDelta * i, zeroY + squareDelta * j)) {
					SetCursorPos(zeroX + squareDelta * i, zeroY + squareDelta * j);
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				}
			}
		}
	}

	return 0;
}
