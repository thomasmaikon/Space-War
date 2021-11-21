/**********************************************************************************
// Player (Arquivo de Cabeçalho)
//
// Criação:     10 Out 2012
// Atualização: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define a classe jogador
//
**********************************************************************************/

#ifndef _BASICAI_ARMA_H_
#define _BASICAI_ARMA_H_

// ---------------------------------------------------------------------------------

#include "Object.h"                     // objetos do jogo
#include "Sprite.h"                     // desenho de sprites
#include "Vector.h"                     // representação de vetores
#include "Particles.h"                  // sistema de partículas
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
    
    void Update();                      // atualização
    void Draw();                        // desenho

    void Disparo(float angulo, Object* obj);
    void ModificarArma(uint escolha);
};
// ---------------------------------------------------------------------------------
inline void Arma::Update(){}
inline void Arma::Draw(){}
//

#endif