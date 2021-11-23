
#ifndef _SPACEWAR_H_
#define _SPACEWAR_H_

#include "Game.h"
#include "Engine.h"

class SpaceWar : public Game {

private:
    static Game* level;

public:

    void Init();                    
    void Update();                  
    void Draw();                    
    void Finalize();                

    template<class T>
    static void NextLevel()      
    {
        if (level)
        {
            level->Finalize();
            delete level;
            level = new T();
            level->Init();
        }
    };
};

#endif