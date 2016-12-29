TCHAR szProgName[] = "Имя программы";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASS w;

	w.lpszClassName = szProgName; //имя программы - объявлено выше
	w.hInstance = hInstance; //идентификатор текущего приложения
	w.lpfnWndProc = WndProc; //указатель на функцию окна
	w.hCursor = LoadCursor(NULL, IDC_ARROW); //загружаем курсор
	w.hIcon = 0;
	w.lpszMenuName = 0;
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //цвет фона окна
	w.style = CS_HREDRAW | CS_VREDRAW;
	w.cbClsExtra = 0;
	w.cbWndExtra = 0;

	//Если не удалось зарегистрировать класс окна - выходим
	if (!RegisterClass(&w))
		return 0;
	//Создадим окно в памяти, заполнив аргументы CreateWindow
	hWnd = CreateWindow(szProgName, //Имя программы
		"Лабораторная работа №8 Вариант 18", //Заголовок окна
		WS_OVERLAPPEDWINDOW, //Стиль окна - перекрывающееся
		50, //положение окна на экране по х
		50, //положение по у
		1200, //ширина
		500, //высота
		(HWND)NULL, //идентификатор родительского окна
		(HMENU)NULL, //идентификатор меню
		(HINSTANCE)hInstance, //идентификатор экземпляра программы
		(HINSTANCE)NULL); //отсутствие дополнительных параметров

						  //Выводим окно из памяти на экран
	ShowWindow(hWnd, nCmdShow);
	//Обновим содержимое окна
	UpdateWindow(hWnd);

	//Цикл обработки сообщений

	while (GetMessage(&lpMsg, NULL, 0, 0)) {
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
	}
	return(lpMsg.wParam);
}

//Функция окна
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc; //создаём контекст устройства
	PAINTSTRUCT ps; //создаём экземпляр структуры графического вывода
	LOGFONT lf;
	HFONT hFont;
	RECT r;
	HBRUSH hBrush;
	HPEN hPen;
	


	//Цикл обработки сообщений
	switch (messg)
	{
		//сообщение рисования
	/*case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		//рисуем овал
		hBrush = CreateHatchBrush(HS_CROSS, RGB(8, 114, 255));
		hPen = CreatePen(PS_DASHDOT, 1, RGB(255, 38, 77));
		SelectObject(hdc, hBrush);
		SelectObject(hdc, hPen);
		Ellipse(hdc, 20, 100, 200, 200);
		ValidateRect(hWnd, NULL);
		EndPaint(hWnd, &ps);
		break;*/
	case WM_MOUSEMOVE:
		static int x, y, x1, y1;
		
		if (wParam & MK_LBUTTON) // Нажата правая клавиша
		{
			//POINT cp;
			hdc = GetDC(hWnd);
			x1 = LOWORD(lParam);
			y1 = HIWORD(lParam);
			x = x1 + 1;
			y = y1 + 1;
			hdc = GetDC(hWnd);
			hBrush = CreateHatchBrush(HS_HORIZONTAL, RGB(255, 255, 0));
			hPen = CreatePen(PS_DOT, 1, RGB(0, 255, 0));
			//GetCursorPos(&cp);
			SelectObject(hdc, hBrush);
			SelectObject(hdc, hPen);
			//MoveToEx(hdc, cp.x, cp.y, NULL);
			Ellipse(hdc, x1, y1, 0, 0);
			//SetCursorPos(cp.x, cp.y);
			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hWnd, hdc);
		}
		else if (wParam & MK_RBUTTON) InvalidateRect(hWnd, NULL, TRUE);
		
		break;

		//сообщение выхода - разрушение окна
	case WM_DESTROY:
		PostQuitMessage(0); //Посылаем сообщение выхода с кодом 0 - нормальное завершение
		//DeleteObject(hPen);
		//DeleteObject(hBrush);
		break;

	default:
		return(DefWindowProc(hWnd, messg, wParam, lParam)); //освобождаем очередь приложения от нераспознаных
	}
	return 0;
}