#include "ConsoleSetUp.h"
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <cstdio>

void ConsoleSetUp()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    _setmode(_fileno(stdout), _O_U16TEXT);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_FONT_INFOEX cfi{};
    cfi.cbSize = sizeof(cfi);
    cfi.dwFontSize.X = 12;
    cfi.dwFontSize.Y = 16;
    wcscpy_s(cfi.FaceName, L"Consolas");

    SetCurrentConsoleFontEx(hOut, FALSE, &cfi);
}
