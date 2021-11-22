

#ifndef _INICIO_H_
#define _INICIO_H_


#include "Background.h"
#include "Game.h"

class Inicio : public Game
{
private:
    Background* backg = nullptr;   // pano de fundo
    
public:
    void Init();                    // inicialização
    void Update();                  // atualização
    void Draw();                    // desenho
    void Finalize();                // finalização
};

#endif