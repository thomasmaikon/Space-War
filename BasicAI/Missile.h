/**********************************************************************************
// Missile (Arquivo de Cabe�alho)
// 
// Cria��o:     23 Nov 2011
// Atualiza��o: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Define uma classe para um m�ssil
//
**********************************************************************************/

#ifndef _BASICAI_MISSILE_H_
#define _BASICAI_MISSILE_H_

// --------------------------------------------------------------------------------

#include "Vector.h"
#include "Object.h"
#include "Sprite.h"
#include "Player.h" 

// --------------------------------------------------------------------------------

class Missile : public Object
{
private:
    //static Player* & player;            // refer�ncia para o player
    Sprite * sprite;                    // sprite do m�ssil
    Vector speed;                       // velocidade do m�ssil  
    bool naoColidiu;
    
public:
    Missile(float angle,uint positionX, uint positionY);               // construtor
    ~Missile();                         // destrutor

    Vector& Speed();                    // retona vetor velocidade
    void Update();                      // atualiza��o
    void Draw();                        // desenho
    void OnCollision(Object* obj);
}; 

// ------------------------------------------------------------------------------

inline Vector& Missile::Speed()
{ return speed; }

inline void Missile::Draw()
{ sprite->Draw(x, y, Layer::UPPER, scale, rotation); }

// ------------------------------------------------------------------------------

#endif