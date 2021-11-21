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

class Laser : public Object
{
private:
    //static Player* & player;            // refer�ncia para o player
    Sprite * sprite;                    // sprite do m�ssil
    Vector speed;                       // velocidade do m�ssil  
    bool naoColidiu;
    
public:
    Laser(float angle,uint positionX, uint positionY);               // construtor
    ~Laser();                         // destrutor

    Vector& Speed();                    // retona vetor velocidade
    void Update();                      // atualiza��o
    void Draw();                        // desenho
    void OnCollision(Object* obj);
}; 

// ------------------------------------------------------------------------------

inline Vector& Laser::Speed()
{ return speed; }

inline void Laser::Draw()
{ sprite->Draw(x, y, Layer::UPPER, scale, rotation); }

// ------------------------------------------------------------------------------

#endif