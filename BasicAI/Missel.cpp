

#include "Missel.h"
#include "WallHit.h"
#include "BasicAI.h"
#include "Hud.h"
#include "Boss.h"
#include "BuffAleatorio.h"
// ------------------------------------------------------------------------------

//Player* & Missile::player = BasicAI::player;        // referência para o player

// ------------------------------------------------------------------------------

Missel::Missel(float angle,float inicialX, float inicialY ,Object * obj)
{
    // inicializa sprite
    sprite = new Sprite("Resources/ResourcesUnidade3/missel.png");

    // cria bounding box
    BBox(new Rect(
        -1.0f * sprite->Width() / 2.0f,
        -1.0f * sprite->Height() / 2.0f,
        sprite->Width() / 2.0f,
        sprite->Height() / 2.0f));

    // inicializa velocidade
    speed.RotateTo(angle);
    speed.ScaleTo(10.0f);
    
    tempoDeVida = 3.0f;
   
    alvo = obj;

    // move para posição
    MoveTo(inicialX + 50 * cos(speed.Radians()), inicialY - 50 * sin(speed.Radians()));
    RotateTo(speed.Angle() + 90.0f);

    // define tipo
    type = MISSILE;

    // incrementa contagem
    ++Hud::missiles;
    naoColidiu = true;
    
    timer.Start();
    start = timer.Stamp();
    
}

// ------------------------------------------------------------------------------

Missel::~Missel()
{
    delete sprite;

    // decrementa contagem
    --Hud::missiles;
}

// -------------------------------------------------------------------------------

void Missel::Update()
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
        BasicAI::scene->Add(new WallHit(x, y), STATIC);

        // remove míssil da cena
        BasicAI::scene->Delete();
    }*/

    // atualiza a direcao que o objeto esta perseguindo
    float angle = Line::Angle(Point(x, y), Point(alvo->X(), alvo->Y()));
    float spaceBetween = Point::Distance(Point(x, y), Point(alvo->X(), alvo->Y()));
    if(spaceBetween <= 150)
        speed.RotateTo(angle);
    RotateTo(-speed.Angle() + 90.0f);

    if (!naoColidiu || timer.Elapsed(start,2.0f))
        BasicAI::scene->Delete();
}

// -------------------------------------------------------------------------------

void Missel::OnCollision(Object* obj) {

    switch (obj->Type()) {
    case Ids::PLAYER: {
        auto player = (Player*)obj;
        if (!player->BufferHabilitado() && player->TipoBuffer() != ESCUDO)
            player->DanoSofrido(15);
        break;
    }
    case Ids::BOSS: {
        auto boss = (Boss*)obj;
        boss->DanoSofrido(10);
        break;
    }
    }

    const float MaxDistance = 4406;
    const float BaseVolume = 0.8f;
    float distance = Point::Distance(Point(x, y), Point(BasicAI::player->X(), BasicAI::player->Y()));
    float level = (MaxDistance - distance) / MaxDistance;
    //BasicAI::audio->Volume(HITWALL, level * BaseVolume);
    //BasicAI::audio->Play(HITWALL);

    // adiciona explosão na cena
    BasicAI::scene->Add(new WallHit(x, y), STATIC);
    naoColidiu = false;
}