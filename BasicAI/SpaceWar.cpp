
#include "SpaceWar.h"
#include "Inicio.h"
#include "Resources.h"
#include "BasicAI.h"
Game* SpaceWar::level = nullptr;
Audio* SpaceWar::audio = nullptr;

void SpaceWar::Init() {
    audio = new Audio();
    audio->Add(5, "Resources/ResourcesUnidade3/fight.wav", 1);
    
    level = new Inicio();
    level->Init();
}

void SpaceWar::Update()
{
    level->Update();
}

void SpaceWar::Draw()
{
    level->Draw();
}

void SpaceWar::Finalize()
{
    level->Finalize();
    delete level;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    // cria motor do jogo
    Engine* engine = new Engine();
    // configura janela
    //engine->window->Mode(WINDOWED);
    //engine->window->Size(728, 410);
    engine->window->Mode(BORDERLESS);
    engine->window->Color(0, 0, 0);
    engine->window->Title("Space War");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    engine->window->HideCursor(true);
    //engine->graphics->VSync(true);
    // cria o jogo
    Game* game = new BasicAI();
    // configura o jogo
    game->Size(3840, 2160);

    
    int status = engine->Start(game);
    
    delete engine;
    
    return status;
}