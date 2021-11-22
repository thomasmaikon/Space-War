

#ifndef _INICIO_H_
#define _INICIO_H_


#include "Background.h"
#include "Game.h"

class Inicio : public Game
{
private:
    Background* backg = nullptr;   // pano de fundo
    
public:
    void Init();                    // inicializa��o
    void Update();                  // atualiza��o
    void Draw();                    // desenho
    void Finalize();                // finaliza��o
};

#endif