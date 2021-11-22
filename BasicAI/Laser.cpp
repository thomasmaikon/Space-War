
#include "Laser.h"
#include "WallHit.h"
#include "BasicAI.h"
#include "Hud.h"
#include "Boss.h"
#include "Kamikaze.h"
#include "BuffAleatorio.h"
// ------------------------------------------------------------------------------

//Player* & Missile::player = BasicAI::player;        // referência para o player

// ------------------------------------------------------------------------------

Laser::Laser(float angle, uint positionX, uint positionY)
{
    // inicializa sprite
    sprite = new Sprite("Resources/ResourcesUnidade3/laser.png");

    // cria bounding box
    BBox(new Circle(8));
    
    // inicializa velocidade
    speed.RotateTo(angle);
    speed.ScaleTo(15.0f);
    
    // move para posição
    MoveTo(positionX + 40 * cos(speed.Radians()), positionY - 40 * sin(speed.Radians()));
    RotateTo(-speed.Angle() + 90.0f);

    // define tipo
    type = MISSILE;

    // incrementa contagem
    ++Hud::missiles;
    naoColidiu = true;
}

// ------------------------------------------------------------------------------

Laser::~Laser()
{
    delete sprite;

    // decrementa contagem
    --Hud::missiles;
}

// -------------------------------------------------------------------------------

void Laser::Update()
{
    // move míssel com vetor resultante
    Translate(speed.XComponent() * 90.0f * gameTime, -speed.YComponent() * 90.0f * gameTime);

    /*// remove míssil da cena se ele sair da área de jogo
    if (x > game->Width() - 50 || x < 50 || y > game->Height() - 50 || y < 50)
    {
        // volume do som de destruição depende da distância para o jogador
        const float MaxDistance = 4406;
        const float BaseVolume = 0.8f;
        float distance = Point::Distance(Point(x, y), Point(BasicAI::player->X(), BasicAI::player->Y()));
        float level = (MaxDistance - distance) / MaxDistance;
        BasicAI::audio->Volume(HITWALL, level * BaseVolume);
        BasicAI::audio->Play(HITWALL);

        // adiciona explosão na cena
        BasicAI::scene->Add(new WallHit(x,y), STATIC);

        // remove míssil da cena
        BasicAI::scene->Delete();
    }*/
    
    if(!naoColidiu)
        BasicAI::scene->Delete();
}

// -------------------------------------------------------------------------------

void Laser::OnCollision(Object* obj) {
    
    switch (obj->Type()) {
    case Ids::PLAYER: {
        auto player = (Player*)obj;
        if(!player->BufferHabilitado() && player->TipoBuffer() != ESCUDO)
            player->DanoSofrido(15);
        break;
    }
    case Ids::BOSS: {
        auto boss = (Boss*)obj;
        boss->DanoSofrido(10);
        break;
    }
    case Ids::KAMIKAZE:{
        auto kamikaze = (Kamikaze*)obj;
        kamikaze->DanoSofrido(15);
        break;
    }
    
    }
    
    const float MaxDistance = 4406;
    const float BaseVolume = 0.8f;
    float distance = Point::Distance(Point(x, y), Point(BasicAI::player->X(), BasicAI::player->Y()));
    float level = (MaxDistance - distance) / MaxDistance;
    BasicAI::audio->Volume(HITWALL, level * BaseVolume);
    BasicAI::audio->Play(HITWALL);

    // adiciona explosão na cena
    BasicAI::scene->Add(new WallHit(x, y), STATIC);
    naoColidiu = false;
}