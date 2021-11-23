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

#ifndef _BASICAI_BOSS_H_
#define _BASICAI_BOSS_H_

// ---------------------------------------------------------------------------------

#include "Object.h"                     // objetos do jogo
#include "Sprite.h"                     // desenho de sprites
#include "Vector.h"                     // representa��o de vetores
#include "Particles.h"                  // sistema de part�culas
#include "Controller.h"                 // entrada pelo controle
#include "Timer.h"                      // controle do tempo
#include "Arma.h"

// ---------------------------------------------------------------------------------

enum NIVEL {FACIL, MODERADO, DIFICIL};

class Boss : public Object
{
private:
    Sprite* sprite;                    // sprite do objeto
    Arma* arma;

    float vida[3];
    float intervaloDisparo[3];
    uint nivel;


    Timer timer;                        // controla tempo dos disparos
    llong start;                        // marca��o de in�cio do disparo
    bool axisCtrl;                      // habilita leitura de disparos
    bool keysCtrl;                      // habilita disparos pelas setas
    bool keysPressed;                   // qualquer seta pressionada
    float firingAngle;                  // dire��o dos disparos
    
    void Atualizar(uint nivel);

public:
    //static Image* missile;             // imagem do m�ssil
    Vector speed;                       // velocidade e dire��o de movimento

    Boss();                           // construtor
    ~Boss();                          // destrutor

    bool AxisTimed(int axisX, int axisY, float time);
    bool KeysTimed(bool pressed, float time);

    void Move(Vector&& v);             // movimenta jogador
    void Update();                      // atualiza��o
    void Draw();                        // desenho

    void OnCollision(Object* obj);

    void DanoSofrido(float dano);
    float Vida();

    void AdicionarKamicazi(int qtd);
};
// ---------------------------------------------------------------------------------

#endif