
#ifndef _BASICAI_MISSEL_H_
#define _BASICAI_MISSEL_H_

// --------------------------------------------------------------------------------

#include "Vector.h"
#include "Object.h"
#include "Sprite.h"
#include "Player.h" 
#include "Timer.h"
// --------------------------------------------------------------------------------

class Missel : public Object
{
private:
    //static Player* & player;            // referência para o player
    Sprite* sprite;                    // sprite do míssil
    Vector speed;                       // velocidade do míssil  
    Object* alvo;
    
    Timer timer;
    float start;
    float tempoDeVida;

    bool naoColidiu;

public:
    Missel(float angle,float inicialX, float inicialY ,Object * obj);               // construtor
    ~Missel();                         // destrutor

    Vector& Speed();                    // retona vetor velocidade
    void Update();                      // atualização
    void Draw();                        // desenho
    void OnCollision(Object* obj);
};

// ------------------------------------------------------------------------------

inline Vector& Missel::Speed()
{
    return speed;
}

inline void Missel::Draw()
{
    sprite->Draw(x, y, Layer::UPPER, scale, rotation);
}

// ------------------------------------------------------------------------------

#endif