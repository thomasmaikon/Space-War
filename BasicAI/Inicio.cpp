
#include "Inicio.h"
#include "Resources.h"
#include "BasicAI.h"
#include "SpaceWar.h"

Font* Inicio::gameFont = nullptr;     // fonte do jogo

void Inicio::Init() {

    gameFont = new Font("Resources/ResourcesUnidade3/Tahoma16.png");
    gameFont->Spacing("Resources/ResourcesUnidade3/Tahoma16.dat");

    backg = new Background("Resources/ResourcesUnidade3/Home.png");

    viewport.left = 0;
    viewport.top = 0;
    viewport.right = backg->Width();
    viewport.bottom = backg->Height();

    seletor = 1;
}

void Inicio::Finalize() {
    delete backg;
    delete gameFont;
}

void Inicio::Draw() {
    backg->Draw(viewport);

    txt.str("");
    txt << " JOGAR ";
    gameFont->Draw(window->Width() / 2 - 45, window->Height() / 2 + 60, txt.str(), (seletor == JOGAR) ? Color{ 0.0f,0.5f,1.0f,1.0f } : Color{ 1.0f,1.0f,1.0f,1.0f });

    txt.str("");
    txt << " SAIR ";
    gameFont->Draw(window->Width() / 2 + 45, window->Height() / 2 + 60, txt.str(), (seletor == SAIR) ? Color{ 0.0f,0.5f,1.0f,1.0f } : Color{ 1.0f,1.0f,1.0f,1.0f });

}

void Inicio::Update() {

    switch (seletor)
    {
    case MENU::JOGAR:
        SpaceWar::NextLevel<BasicAI>();
        break;

    case MENU::SAIR:
        if (window->KeyPress(VK_RETURN))
            window->Close();
        break;

    }

    if (window->KeyPress(VK_LEFT)) {
        seletor = (seletor - 1) % 2;
        if (seletor == -1)
            seletor = 1;
    }
    if (window->KeyPress(VK_RIGHT)) {
        seletor = (seletor + 1) % 2;
    }
}

