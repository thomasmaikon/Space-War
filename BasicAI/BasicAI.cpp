/**********************************************************************************
// BasicAI (Código Fonte)
// 
// Criação:     23 Out 2012
// Atualização: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Demonstração de todas as IAs

//
**********************************************************************************/

#include "Resources.h"
#include "BasicAI.h"
#include "Engine.h"    
#include "Delay.h"
#include "BlackHole.h"
#include "Boss.h"
#include "BuffAleatorio.h"
// ------------------------------------------------------------------------------

Player * BasicAI::player  = nullptr;
Audio  * BasicAI::audio   = nullptr;
Scene  * BasicAI::scene   = nullptr;
bool     BasicAI::viewHUD = false;
Image  * BasicAI::blue    = nullptr;
Image  * BasicAI::green   = nullptr;
Image  * BasicAI::magenta = nullptr;
Image  * BasicAI::orange  = nullptr;
BlackHole* BasicAI::blackHole = nullptr;

// ------------------------------------------------------------------------------

void BasicAI::Init() 
{
    // cria sistema de áudio
    audio = new Audio();
    audio->Add(START, "Resources/Start.wav");
    audio->Add(THEME, "Resources/Theme.wav");
    audio->Add(FIRE, "Resources/Fire.wav", 2);
    audio->Add(HITWALL, "Resources/Hitwall.wav", 5);
    audio->Add(EXPLODE, "Resources/Explode.wav", 3);
    audio->Add(ORANGE, "Resources/Orange.wav", 1);
    audio->Add(MAGENTA, "Resources/Magenta.wav", 2);
    audio->Add(BLUE, "Resources/Blue.wav", 2);
    audio->Add(GREEN, "Resources/Green.wav", 2);
    audio->Add(BATTLE, "Resources/ResourcesUnidade3/fight.wav", 1);

    // ajusta volumes
   // audio->Volume(START, 0.30f);
   // audio->Volume(THEME, 0.60f);
   // audio->Volume(FIRE, 0.10f);
   // audio->Volume(EXPLODE, 0.15f);
   // audio->Volume(ORANGE, 0.90f);
   // audio->Volume(MAGENTA, 0.40f);
   // audio->Volume(BLUE, 0.20f);
   // audio->Volume(GREEN, 0.75f);

    
    blackHole = new BlackHole(600,600);
    BuffAleatorio * buff = new BuffAleatorio();
   
    // carrega imagens das geometrias
  /*  blue = new Image("Resources/Blue.png");
    green   = new Image("Resources/Green.png");
    magenta = new Image("Resources/Magenta.png");
    orange  = new Image("Resources/Orange.png");*/

    // carrega/incializa objetos
    backg   = new Background("Resources/ResourcesUnidade3/BackGround.png");
    player  = new Player();
    scene   = new Scene();  
    hud     = new Hud();

    // adiciona objetos na cena
    scene->Add(player, MOVING);
    scene->Add(new Delay(), STATIC);
    scene->Add(blackHole, STATIC);
    scene->Add(buff, STATIC);
    scene->Add(new Boss(), MOVING);

    // ----------------------
    // inicializa a viewport
    // ----------------------

    // calcula posição para manter viewport centralizada
    float difx = (game->Width() - window->Width()) / 2.0f;
    float dify = (game->Height() - window->Height()) / 2.0f;

    // inicializa viewport para o centro do mundo
    viewport.left = 0.0f + difx;
    viewport.right = viewport.left + window->Width();
    viewport.top = 0.0f + dify;
    viewport.bottom = viewport.top + window->Height();

    audio->Play(BATTLE, true);
}

// ------------------------------------------------------------------------------

void BasicAI::Update()
{
    // sai com o pressionamento da tecla ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    if (BasicAI::player->Vida() <= 0) {
        window->Close();
    }
    // atualiza cena e calcula colisões
    scene->Update();
    scene->CollisionDetection();

    // ---------------------------------------------------
    // atualiza a viewport
    // ---------------------------------------------------

    viewport.left   = player->X() - window->CenterX();
    viewport.right  = player->X() + window->CenterX();
    viewport.top    = player->Y() - window->CenterY();
    viewport.bottom = player->Y() + window->CenterY();
            
    if (viewport.left < 0)
    {
        viewport.left  = 0;
        viewport.right = window->Width();
    }
    else if (viewport.right > game->Width())
    {  
        viewport.left  = game->Width() - window->Width();
         viewport.right = game->Width();
    }
                  
    if (viewport.top < 0)
    {
        viewport.top  = 0;
        viewport.bottom = window->Height();
    }
    else if (viewport.bottom > game->Height())
    {
        viewport.top = game->Height() - window->Height();
        viewport.bottom = game->Height();
    }

    // ---------------------------------------------------

    // atualiza o painel de informações
    hud->Update();

    // ativa ou desativa a bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;

    // ativa ou desativa o heads up display
    if (window->KeyPress('H'))
        viewHUD = !viewHUD;
} 

// ------------------------------------------------------------------------------

void BasicAI::Draw()
{
    // desenha pano de fundo
    backg->Draw(viewport);

    // desenha a cena
    scene->Draw();

    // desenha o painel de informações
    if (viewHUD)
        hud->Draw();

    // desenha bounding box
    if (viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void BasicAI::Finalize()
{
    delete audio;
    delete hud;
    delete scene;
    delete backg;

    delete blue;
    delete green;
    delete magenta;
    delete orange;
}

// ----------------------------------------------------------------------------