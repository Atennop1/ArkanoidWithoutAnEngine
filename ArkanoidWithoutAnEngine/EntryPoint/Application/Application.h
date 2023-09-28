#pragma once
#include "../../framework.h"
#include "../../Game/Game.h"

class Application
{
private:
    HINSTANCE m_instance;
    HINSTANCE m_previousInstance;

    int m_cmdShow;
    LPWSTR m_lpCmdLine;

    WCHAR m_sizeTitle[100];
    WCHAR m_sizeWindowClass[100];
    
    BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
    ATOM RegisterWindow(HINSTANCE hInstance) const;
    static LRESULT CALLBACK ProceedWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    
public:
    Application(HINSTANCE instance, HINSTANCE previousInstance, LPWSTR lpCmdLine, int cmdShow);
    MSG Run();

    Game *Game;
    HDC CurrentHDC;
};
