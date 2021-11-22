#include "Inicio.h"
#include "Engine.h"
#include "Resources.h"

// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    // cria motor do jogo
    Engine* engine = new Engine();

    // configura janela
    engine->window->Mode(WINDOWED);
    engine->window->Size(728, 410);
    //engine->window->Mode(BORDERLESS);
    engine->window->Color(0, 0, 0);
    engine->window->Title("Space War");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    engine->window->HideCursor(true);
    //engine->graphics->VSync(true);

    // cria o jogo
    Game* game = new Inicio();

    // configura o jogo
    //game->Size(728, 410);

    // inicia execução
    int status = engine->Start(game);

    // destrói motor 
    delete engine;

    // encerra
    return status;
}