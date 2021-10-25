#include <Windows.h>
#include <stdlib.h>

#define SPRITE_STEP 3
#define DIRECTION int
#define LEFT 0
#define UP 4
#define RIGHT 8
#define DOWN 12

const wchar_t CLASS_NAME[] = L"MyWindowClass";

const int RectSize = 50;
const int XSprite = 100;
const int YSprite = 100;

RECT SpriteRect = { XSprite, YSprite, XSprite + RectSize, YSprite + RectSize };
RECT MainRect;



LRESULT CALLBACK WindProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
void moveSprite(DIRECTION direction, int offset);
int getAllowedOffset(DIRECTION direction, int offset);



int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, PWSTR args, int nCmdShow)
{
	//MessageBox(NULL, L"HELLO", "meafecd", MB_OK);

	HWND hwnd;
	WNDCLASS wc = { };
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindProc;
	wc.hInstance = hInst;
	wc.lpszClassName = CLASS_NAME;


	if (!RegisterClass(&wc))
		return -1;
	hwnd = CreateWindowEx(0, CLASS_NAME, L"FISICS", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hInst, NULL);

	/*   HWND hwnd = CreateWindowEx(
			0,                              // Optional window styles.
			CLASS_NAME,                     // Window class
			L"Learn to Program Windows",    // Window text
			WS_OVERLAPPEDWINDOW,            // Window style

			// Size and position
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

			NULL,       // Parent window
			NULL,       // Menu
			hInst,  // Instance handle
			NULL        // Additional application data
		);
	*/
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	MSG msg = { };
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WindProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	PAINTSTRUCT ps;
	HDC hdc, hCmpDC;
	HBITMAP bitmap;
	switch (msg)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &MainRect);
		hCmpDC = CreateCompatibleDC(hdc);
		bitmap = CreateCompatibleBitmap(hdc, MainRect.right - MainRect.left, MainRect.bottom - MainRect.top);
		SelectObject(hCmpDC, bitmap);
		LOGBRUSH br;
		br.lbStyle = BS_SOLID;
		br.lbColor = 0xEECCCC;
		HBRUSH brush, SpriteBrush;
		brush = CreateBrushIndirect(&br);
		FillRect(hCmpDC, &MainRect, brush);
		DeleteObject(brush);
		br.lbStyle = BS_SOLID;
		br.lbColor = 0x00ff00;
		SpriteBrush = CreateBrushIndirect(&br);
		FillRect(hCmpDC, &SpriteRect, SpriteBrush);
		DeleteObject(SpriteBrush);
		SetStretchBltMode(hdc, COLORONCOLOR);
		BitBlt(hdc, 0, 0, MainRect.right - MainRect.left, MainRect.bottom - MainRect.top, hCmpDC, 0, 0, SRCCOPY);
		DeleteDC(hCmpDC);
		DeleteObject(bitmap);
		hCmpDC = NULL;
		EndPaint(hwnd, &ps);
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	case WM_KEYDOWN:
		switch (wp) {
		case VK_LEFT:
			moveSprite(LEFT, SPRITE_STEP);
			break;
		case VK_RIGHT:
			moveSprite(RIGHT, SPRITE_STEP);
			break;
		case VK_UP:
			moveSprite(UP, SPRITE_STEP);
			break;
		case VK_DOWN:
			moveSprite(DOWN, SPRITE_STEP);
			break;
		}
		InvalidateRect(hwnd, &MainRect, false);
		break;
	case WM_SIZE:
		GetClientRect(hwnd, &MainRect);
		//SetWindowSize(Rect.right - Rect.left, Rect.bottom - Rect.top);
		break;
	case WM_ERASEBKGND:
		return 1;
		break;
	default:
		return DefWindowProc(hwnd, msg, wp, lp);
	}
	return 0;
}

void moveSprite(DIRECTION direction, int offset) {

	offset = getAllowedOffset(direction, offset);

	switch (direction) {
	case UP:
		OffsetRect(&SpriteRect, 0, -offset);
		break;
	case DOWN:
		OffsetRect(&SpriteRect, 0, offset);
		break;
	case LEFT:
		OffsetRect(&SpriteRect, -offset, 0);
		break;
	case RIGHT:
		OffsetRect(&SpriteRect, offset, 0);
		break;
	}
}

int getAllowedOffset(DIRECTION direction, int offset) {
	LONG firstPosition;
	LONG secondPosition;

	switch (direction) {
	case UP:
		firstPosition = SpriteRect.top - offset;
		secondPosition = MainRect.top;
		break;
	case DOWN:
		firstPosition = MainRect.bottom;
		secondPosition = SpriteRect.bottom + offset;
		break;
	case LEFT:
		firstPosition = SpriteRect.left - offset;
		secondPosition = MainRect.left;
		break;
	case RIGHT:
		firstPosition = MainRect.right;
		secondPosition = SpriteRect.right + offset;
		break;
	}

	if ((secondPosition - firstPosition) > -1) {
		return -10 * offset;
	}

	return offset;
}