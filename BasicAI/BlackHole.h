
#ifndef _BASICAI_BLACKHOLE_H_
#define _BASICAI_BLACKHOLE_H_

// ---------------------------------------------------------------------------------

#include "Object.h"    
#include "Types.h"
#include "Sprite.h"
#include "Vector.h"
#include "Player.h"

// ---------------------------------------------------------------------------------

class BlackHole : public Object
{
private:
    Sprite* sprite;                            // sprite do objeto
    //Player* player;                            // ponteiro para jogador
    
    float forca;                               // fator de escala
    Vector speed;                               // velocidade e direção

public:
    BlackHole(float pX, float pY);       // construtor
    ~BlackHole();                                    // destrutor

    void OnCollision(Object* obj);              // resolução da colisão
    void Update();                              // atualização
    void Draw();                                // desenho
    float Forca();
};

// ---------------------------------------------------------------------------------

inline float BlackHole::Forca() { return forca; }

#endif