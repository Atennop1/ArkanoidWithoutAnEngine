#include "Main.h"
#include "../Game/Game.h"
#include "Application/Application.h"
 
//----------------------------------------------------------------------------------------------------
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    auto application = Application(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
    const MSG message = application.Run();
    
    return (int)message.wParam;
}

//----------------------------------------------------------------------------------------------------
