#ifndef _BASICAI_KAMIKAZE_H_
#define _BASICAI_KAMIKAZE_H_

// ---------------------------------------------------------------------------------

#include "Object.h"                     // objetos do jogo
#include "Sprite.h"                     // desenho de sprites
#include "Vector.h"                     // representação de vetores
#include "Particles.h"                  // sistema de partículas
#include "Controller.h"                 // entrada pelo controle
#include "Timer.h"                      // controle do tempo
#include "Arma.h"

// ---------------------------------------------------------------------------------

class Kamikaze : public Object
{
private:
    Sprite* sprite;                    // sprite do objeto
    Arma* arma;
    Object* alvo;

    float vida;
    float intervaloDisparo;
    
    Timer timer;                        // controla tempo dos disparos
    llong start;                        // marcação de início do disparo

    bool keysCtrl;                      // habilita disparos pelas setas
    bool colidiu;
public:
    //static Image* missile;             // imagem do míssil
    Vector speed;                       // velocidade e direção de movimento

    Kamikaze(Object * obj);                           // construtor
    ~Kamikaze();                          // destrutor

//    bool AxisTimed(int axisX, int axisY, float time);
//    bool KeysTimed(bool pressed, float time);

    void Move(Vector&& v);             // movimenta jogador
    void Update();                      // atualização
    void Draw();                        // desenho

    void OnCollision(Object* obj);

    void DanoSofrido(float dano);
    float Vida();
};
// ---------------------------------------------------------------------------------

#endif