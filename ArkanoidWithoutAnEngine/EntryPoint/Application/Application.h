#pragma once
#include "../../framework.h"
#include "../../Game/Game.h"

class Application
{
private:
    int m_cmdShow;
    LPWSTR m_lpCmdLine;

    WCHAR m_sizeTitle[100];
    WCHAR m_sizeWindowClass[100];
    
    HINSTANCE m_instance;
    HINSTANCE m_previousInstance;
    
    Game *m_game;
    HDC m_currentHDC;
    
    BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
    ATOM RegisterWindow(HINSTANCE hInstance) const;
    
public:
    Application(HINSTANCE instance, HINSTANCE previousInstance, LPWSTR lpCmdLine, int cmdShow);
    
    MSG Run();
    LRESULT CALLBACK ProcessWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
