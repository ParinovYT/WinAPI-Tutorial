#include <windows.h> // содержит API

// Основная функция:
int WINAPI WinMain(HINSTANCE hInst, // дескриптор экземпляра приложения
    HINSTANCE hPreviousInst, // в Win32 не используется, но объявление нужно
    LPSTR lpCommandLine, // нужен для запуска окошка в режиме командной строки
    int nCommandShow) // режим отображения окна
{
    int result = MessageBox(NULL, L"Вам нравится WINAPI?!", L"Задача",
        MB_ICONQUESTION | MB_YESNO);
    switch (result)
    {
    case IDYES: MessageBox(NULL, L"Продолжайте в том же духе!!!",
        L"Ответ", MB_OK | MB_ICONASTERISK); break;
    case IDNO:  MessageBox(NULL, L"Очень жаль!!!", L"Ответ",
        MB_OK | MB_ICONSTOP); break;
    }
    return NULL;
}