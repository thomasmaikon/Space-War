/**********************************************************************************
// Player (Arquivo de Cabe�alho)
//
// Cria��o:     10 Out 2012
// Atualiza��o: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Define a classe jogador
//
**********************************************************************************/

#ifndef _BASICAI_ARMA_H_
#define _BASICAI_ARMA_H_

// ---------------------------------------------------------------------------------

#include "Object.h"                     // objetos do jogo
#include "Sprite.h"                     // desenho de sprites
#include "Vector.h"                     // representa��o de vetores
#include "Particles.h"                  // sistema de part�culas
#include "Controller.h"                 // entrada pelo controle
#include "Timer.h"                      // controle do tempo

enum TipoArma {FOGUETE = 0};

// ---------------------------------------------------------------------------------

class Arma : public Object
{
private:
    uint tipoArma;

public:
    
    Arma(uint tipoDeArma);                           // construtor
    ~Arma();                          // destrutor
    
    void Update();                      // atualiza��o
    void Draw();                        // desenho

    void Disparo(float angulo, Object* obj);
    void ModificarArma(uint escolha);
};
// ---------------------------------------------------------------------------------
inline void Arma::Update(){}
inline void Arma::Draw(){}
//

#endif