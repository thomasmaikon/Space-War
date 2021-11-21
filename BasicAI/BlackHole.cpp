#include "BasicAI.h"
#include "BlackHole.h"
#include "Random.h" 
#include "Image.h"
// ---------------------------------------------------------------------------------

BlackHole::BlackHole(float pX, float pY)
{
    sprite = new Sprite("Resources/ResourcesUnidade3/buracoNegro.png");
    BBox(new Circle(50.0f));
    MoveTo(pX, pY);
    type = Ids::BLACKHOLE;
    forca = 30.0f;
    /* sprite = new Sprite(BasicAI::orange);

     // ajusta o vetor velocidade
     speed.RotateTo(ang);
     speed.ScaleTo(400);
     RotateTo(-speed.Angle());
     BBox(new Circle(20.0f));
     type = ORANGE;

     // configura��o do emissor de part�culas
     Generator emitter;
     emitter.imgFile = "Resources/Spark.png";    // arquivo de imagem
     emitter.angle = speed.Angle() + 180;        // �ngulo base do emissor
     emitter.spread = 5;                         // espalhamento em graus
     emitter.lifetime = 0.4f;                    // tempo de vida em segundos
     emitter.frequency = 0.010f;                 // tempo entre gera��o de novas part�culas
     emitter.percentToDim = 0.8f;                // desaparece ap�s 60% da vida
     emitter.minSpeed = 100.0f;                  // velocidade m�nima das part�culas
     emitter.maxSpeed = 200.0f;                  // velocidade m�xima das part�culas
     emitter.color.r = 1.0f;                     // componente Red da part�cula
     emitter.color.g = 0.5;                      // componente Green da part�cula
     emitter.color.b = 0.0f;                     // componente Blue da part�cula
     emitter.color.a = 1.0f;                     // transpar�ncia da part�cula

     // cria sistema de part�culas
     tail = new Particles(emitter);
     tailCount = 0;

     // incrementa contagem
     ++Hud::oranges;*/
}

// ---------------------------------------------------------------------------------

BlackHole::~BlackHole()
{
    /*delete sprite;
    delete tail;

    // decrementa contagem
    Hud::particles -= tailCount;
    --Hud::oranges;*/
}

// -------------------------------------------------------------------------------

void BlackHole::OnCollision(Object* obj)
{
    
    switch(obj->Type())
    {

   
    case Ids::PLAYER: {
        auto* player = (Player*)obj;
        float x = RandF(10, 3830).Rand();
        float y = RandF(10, 2150).Rand();
        player->MoveTo(x, y);
        //player->ScaleTo(player->Scale() - 5);
        break;
    }
    
    }
    
    /*if (obj->Type() == MISSILE)
    {
        BasicAI::scene->Delete(obj, STATIC);
        BasicAI::scene->Delete(this, MOVING);
        BasicAI::scene->Add(new Explosion(x, y), STATIC);
        BasicAI::audio->Play(EXPLODE);
    }*/
}

// -------------------------------------------------------------------------------

void BlackHole::Update()
{
    Rotate(10);
    /*// movimenta objeto pelo seu vetor velocidade
    Translate(speed.XComponent() * gameTime, -speed.YComponent() * gameTime);

    // ajusta �ngulo do vetor na dire��o oposta
    if (x < 50 || y < 50 || x > game->Width() - 50 || y > game->Height() - 50)
    {
        Rotate(180);
        speed.Rotate(180);
        Translate(speed.XComponent() * gameTime, -speed.YComponent() * gameTime);
    }

    // atualiza calda da nave
    tail->Config().angle = speed.Angle();
    tail->Generate(x - 10 * cos(speed.Radians()), y + 10 * sin(speed.Radians()));
    tail->Update(gameTime);

    Hud::particles -= tailCount;
    tailCount = tail->Size();
    Hud::particles += tailCount;*/
}

// ---------------------------------------------------------------------------------

void BlackHole::Draw()
{
    sprite->Draw(x, y, Layer::MIDDLE, scale, rotation);
    /*sprite->Draw(x, y, Layer::LOWER, scale, rotation);
    tail->Draw(Layer::LOWER, 1.0f);*/
}

// -------------------------------------------------------------------------------