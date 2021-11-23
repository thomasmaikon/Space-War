

#ifndef _INICIO_H_
#define _INICIO_H_


#include "Background.h"
#include "Game.h"
#include "Engine.h"
#include "Font.h"
#include <sstream>
using namespace std;


enum MENU { JOGAR, SAIR };

class Inicio : public Game
{
private:
    Background* backg = nullptr;
    // static Game* level;            
    uint seletor;

    stringstream txt;

public:
    static Font* gameFont;


    void Init();
    void Update();
    void Draw();
    void Finalize();
};

#endif