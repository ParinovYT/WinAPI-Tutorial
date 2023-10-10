#include <windows.h>

LRESULT CALLBACK WindowProcess(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInst,
    HINSTANCE hPrevInst,
    LPSTR pCommandLine,
    int nCommandShow) {
    TCHAR className[] = L"Мой класс";
    HWND hWindow;
    MSG message;
    WNDCLASSEX windowClass;

    windowClass.cbSize = sizeof(windowClass);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WindowProcess;
    windowClass.lpszMenuName = NULL;
    windowClass.lpszClassName = className;
    windowClass.cbWndExtra = NULL;
    windowClass.cbClsExtra = NULL;
    windowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    windowClass.hInstance = hInst;

    if (!RegisterClassEx(&windowClass))
    {
        MessageBox(NULL, L"Не получилось зарегистрировать класс!", L"Ошибка", MB_OK);
        return NULL;
    }
    hWindow = CreateWindow(className,
        L"Программа ввода символов",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        NULL,
        CW_USEDEFAULT,
        NULL,
        (HWND)NULL,
        NULL,
        HINSTANCE(hInst),
        NULL
    );
    if (!hWindow) {
        MessageBox(NULL, L"Не получилось создать окно!", L"Ошибка", MB_OK);
        return NULL;
    }
    ShowWindow(hWindow, nCommandShow);
    UpdateWindow(hWindow);
    while (GetMessage(&message, NULL, NULL, NULL)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
    return message.wParam;
}

LRESULT CALLBACK WindowProcess(HWND hWindow,
    UINT uMessage,
    WPARAM wParameter,
    LPARAM lParameter)
{
    HDC hDeviceContext;
    PAINTSTRUCT paintStruct;
    RECT rectPlace;
    HFONT hFont;
    static char text[2] = { ' ','\0' };
    switch (uMessage)
    {
    case WM_CREATE:
        MessageBox(NULL,
            L"Пожалуйста, вводите символы и они будут отображаться на экране!",
            L"ВНИМАНИЕ!!!", MB_ICONASTERISK | MB_OK);
        break;
    case WM_PAINT:
        hDeviceContext = BeginPaint(hWindow, &paintStruct);
        GetClientRect(hWindow, &rectPlace);
        SetTextColor(hDeviceContext, NULL);
        hFont = CreateFont(90, 0, 0, 0, 0, 0, 0, 0,
            DEFAULT_CHARSET,
            0, 0, 0, 0,
            L"Arial Bold"
        );
        SelectObject(hDeviceContext, hFont);
        DrawText(hDeviceContext, (LPCWSTR)text, 1, &rectPlace, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        EndPaint(hWindow, &paintStruct);
        break;
    case WM_KEYDOWN:
        switch (wParameter)
        {
        case VK_HOME:case VK_END:case VK_PRIOR:
        case VK_NEXT:case VK_LEFT:case VK_RIGHT:
        case VK_UP:case VK_DOWN:case VK_DELETE:
        case VK_SHIFT:case VK_SPACE:case VK_CONTROL:
        case VK_CAPITAL:case VK_MENU:case VK_TAB:
        case VK_BACK:case VK_RETURN:
            break;
        default:
            text[0] = (char)wParameter;
            InvalidateRect(hWindow, NULL, TRUE);
            break;
        }break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWindow, uMessage, wParameter, lParameter);
    }
    return NULL;
}