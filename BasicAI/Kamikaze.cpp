#include "Kamikaze.h"
#include "BasicAI.h"
#include "Player.h"

// -------------------------------------------------------------------------------
Kamikaze::Kamikaze(Object * obj)
{
    // tipo de arma utilizada pelo chefao
    arma = new Arma(TipoArma::LASER);

    // sprite do chefao
    sprite = new Sprite("Resources/ResourcesUnidade3/kamikaze.png");

    // Inicializa o chefao
    vida = 50;
    intervaloDisparo= 1.5f;

    alvo = obj;

    speed.RotateTo(90.0f);
    speed.ScaleTo(0.0f);
    BBox(new Circle(18.0f));
    MoveTo(400, 400);

    type = Ids::KAMIKAZE;

    timer.Start();
    start = timer.Stamp();

    keysCtrl = true;
    colidiu = false;
}

// -------------------------------------------------------------------------------

Kamikaze::~Kamikaze()
{
    delete sprite;
    delete arma;
}


// -------------------------------------------------------------------------------

void Kamikaze::Move(Vector&& v)
{
    // soma vetor movimento (v) ao vetor velocidade
    speed.Add(v);

    // limita velocidade máxima
    if (speed.Magnitude() > 10.0f)
        speed.ScaleTo(10.0f);
}

// -------------------------------------------------------------------------------

void Kamikaze::Update()
{
    // ajusta ângulo do vetor
    float angle = Line::Angle(Point(x, y), Point(alvo->X(), alvo->Y()));
    speed.RotateTo(angle);

    Move(Vector(angle, 10 * gameTime));
    Translate(speed.XComponent() * 50.0f * gameTime, -speed.YComponent() * 50.0f * gameTime);
    

    // A nave vai atirar para o mesmo objeto que esta olhando
    if (keysCtrl)
    {
        // se há qualquer seta pressionada
        keysCtrl = false;
        start = timer.Stamp();
        arma->Disparo(angle, this, BasicAI::player);
    }
    // senão aguarda o momento certo
    else if (timer.Elapsed(start, intervaloDisparo))
    {
        keysCtrl = true;
    }

    if (colidiu || vida <=0 )
        BasicAI::scene->Delete();
}

// ---------------------------------------------------------------------------------

void Kamikaze::Draw()
{
    sprite->Draw(x, y, Layer::MIDDLE, 1.0f, -speed.Angle() + 90.0f);
}

// -------------------------------------------------------------------------------

void Kamikaze::OnCollision(Object* obj)
{
    switch (obj->Type()) {
    case Ids::PLAYER: {

        auto player = (Player*)obj;
        player->DanoSofrido(75);
        colidiu = true;
        break;
    }
    
    case Ids::KAMIKAZE: {
        RotateTo(180.0f);
        break;
    }

    }
    if (obj->Type() == Ids::PLAYER) {
    }

}

// -------------------------------------------------------------------------------

void Kamikaze::DanoSofrido(float dano) {
    vida = vida - dano;
}

// -------------------------------------------------------------------------------

float Kamikaze::Vida() { return vida; }

// -------------------------------------------------------------------------------
