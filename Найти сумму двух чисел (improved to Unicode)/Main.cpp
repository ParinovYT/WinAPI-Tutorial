#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Функция преобразования строки в число
int StrToInt(wchar_t* s)
{
    int temp = 0; // число
    int i = 0;
    int sign = 0; // знак числа 0- положительное, 1 - отрицательное
    if (s[i] == '-')
    {
        sign = 1;
        i++;
    }
    while (s[i] >= 0x30 && s[i] <= 0x39)
    {
        temp = temp + (s[i] & 0x0F);
        temp = temp * 10;
        i++;
    }
    temp = temp / 10;
    if (sign == 1)
        temp = -temp;
    return(temp);
}
// Функция преобразования числа в строку
wchar_t* IntToStr(int n)
{
    wchar_t s[40], t, * temp;
    int i, k;
    int sign = 0;
    i = 0;
    k = n;
    if (k < 0)
    {
        sign = 1;
        k = -k;
    }
    do {
        t = k % 10;
        k = k / 10;
        s[i] = t | 0x30;
        i++;
    } while (k > 0);
    if (sign == 1)
    {
        s[i] = '-';
        i++;
    }
    temp = new wchar_t[i];
    k = 0;
    i--;
    while (i >= 0) {
        temp[k] = s[i];
        i--; k++;
    }
    temp[k] = '\0';
    return(temp);
}
// Стартовая функция
int  WINAPI  WinMain(HINSTANCE  hInstance,
    HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HWND hwnd; // дескриптор окна
    MSG msg;   // структура сообщения
    WNDCLASSW w; // структура класса окна
    memset(&w, 0, sizeof(WNDCLASSW)); // очистка памяти для структуры
    w.style = CS_HREDRAW | CS_VREDRAW;
    w.lpfnWndProc = WndProc;
    w.hInstance = hInstance;
    w.hbrBackground = CreateSolidBrush(0x00FFFFFF);
    w.lpszClassName = L"MyClass";
    RegisterClass(&w); // регистрация класса окна
    // Создание окна
    hwnd = CreateWindow(L"MyClass", L"Сумма двух чисел",
        WS_OVERLAPPEDWINDOW,
        500, 300, 500, 380,
        NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow); // отображение окна
    UpdateWindow(hwnd);         // перерисовка окна
    // Цикл обработки сообщений
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
// Функция обработки сообщений
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message,
    WPARAM wparam, LPARAM lparam) {
    HDC hdc;
    HINSTANCE hInst;
    PAINTSTRUCT ps;
    static HWND hBtn; // дескриптор кнопки
    static HWND hEdt1, hEdt2, hEdt3; // дескрипторы полей редактирования
    static HWND hStat; // дескриптор статического текста
    TCHAR StrA[20];
    int a, b, c, sum, Len;
    switch (Message) {
    case WM_CREATE: // сообщение создания окна
        hInst = ((LPCREATESTRUCT)lparam)->hInstance; // дескриптор приложения
        // Создаем и показываем первое поле редактирования
        hEdt1 = CreateWindow(L"edit", L"0",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 50, 50, 60, 20,
            hwnd, 0, hInst, NULL);
        ShowWindow(hEdt1, SW_SHOWNORMAL);
        // Создаем и показываем второе поле редактирования
        hEdt2 = CreateWindow(L"edit", L"0",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 150, 50, 60,
            20, hwnd, 0, hInst, NULL);
        ShowWindow(hEdt2, SW_SHOWNORMAL);
        hEdt3 = CreateWindow(L"edit", L"0",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 250, 50, 60,
            20, hwnd, 0, hInst, NULL);
        ShowWindow(hEdt3, SW_SHOWNORMAL);
        // Создаем и показываем кнопку
        hBtn = CreateWindow(L"button", L"Рассчитать",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            50, 100, 120, 30, hwnd, 0, hInst, NULL);
        ShowWindow(hBtn, SW_SHOWNORMAL);
        // Создаем и показываем поле текста для результата
        hStat = CreateWindow(L"static", L"0", WS_CHILD | WS_VISIBLE,
            150, 180, 120, 20, hwnd, 0, hInst, NULL);
        ShowWindow(hStat, SW_SHOWNORMAL);
        break;
    case WM_COMMAND:  // сообщение о команде
        if (lparam == (LPARAM)hBtn)    // если нажали на кнопку
        {
            Len = GetWindowText(hEdt1, StrA, 20);
            a = StrToInt(StrA); // считываем число из первого поля
            Len = GetWindowText(hEdt2, StrA, 20);
            b = StrToInt(StrA); // считываем число из второго поля
            Len = GetWindowText(hEdt3, StrA, 20);
            c = StrToInt(StrA); // считываем число из второго поля
            sum = a + b + c;  // находим сумму двух чисел
            SetWindowText(hStat, IntToStr(sum)); // выводим результат в статическое поле
        }
        break;
    case WM_PAINT: // перерисовка окна
        hdc = BeginPaint(hwnd, &ps); // начало перерисовки
        TextOut(hdc, 50, 20, L"Введите три числа", 18); // вывод текстовых сообщений
        TextOut(hdc, 50, 180, L"Результат:", 10);
        EndPaint(hwnd, &ps); // конец перерисовки
        break;
    case WM_DESTROY: // закрытие окна
        PostQuitMessage(0);
        break;
    default: // обработка сообщения по умолчанию
        return DefWindowProc(hwnd, Message, wparam, lparam);
    }
    return 0;
}
