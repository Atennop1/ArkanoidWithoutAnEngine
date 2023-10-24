#include "main.h"
#include "../Game/game.h"
#include "Application/application.h"

//----------------------------------------------------------------------------------------------------
int APIENTRY wWinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE previous_instance, _In_ LPWSTR application_command_line, _In_ int window_showing_type)
{    
    const auto application = new Application(instance, previous_instance, application_command_line, window_showing_type);
    application->Activate();
}

//----------------------------------------------------------------------------------------------------
