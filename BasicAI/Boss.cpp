#include "Boss.h"
#include "BasicAI.h"
#include "Player.h"
#include "Kamikaze.h"
// -------------------------------------------------------------------------------
Boss::Boss()
{
    // tipo de arma utilizada pelo chefao
    arma = new Arma(TipoArma::LASER);

    // sprite do chefao
    sprite = new Sprite("Resources/ResourcesUnidade3/boss.png");
    
    // Inicializa o chefao
    vida[NIVEL::FACIL] = 200;
    intervaloDisparo[NIVEL::FACIL] = 2.0f;
    
    vida[NIVEL::MODERADO] = 400;
    intervaloDisparo[NIVEL::MODERADO] = 1.0f;
    
    vida[NIVEL::DIFICIL] = 1000;
    intervaloDisparo[NIVEL::DIFICIL] = 0.2f;

    nivel = NIVEL::FACIL;

    
    speed.RotateTo(90.0f);
    Point vertex[16] =
    {
        Point(-187,10), Point(-130,-187), Point(-127,10), Point(-70,35),
        Point(-60,-80), Point(-40,-120), Point(0,-130), Point(40,-120),
        Point(60,-80), Point(70,35), Point(127,10), Point(130,-187), Point(187,10), Point(50,187),
        Point(-50,187), Point(-187,10)
    };

    BBox(new Poly(vertex, 16));
    MoveTo(300, 300);
    
    type = Ids::BOSS;

    // diparo habilitado
    firingAngle = 0.0f;
    keysPressed = false;
    axisCtrl = true;
    keysCtrl = true;
    start = 0;
    timer.Start();
}

// -------------------------------------------------------------------------------

Boss::~Boss()
{
    delete sprite;
    //delete missile;
}

// -------------------------------------------------------------------------------

bool Boss::AxisTimed(int axisX, int axisY, float time)
{
    // se j� passou o tempo para o pr�ximo disparo
    /*if (axisCtrl)
    {
        // a magnitude � a dist�ncia do eixo para o seu centro
        float magnitude = Point::Distance(Point(0, 0), Point(float(gamepad->Axis(axisX)), float(gamepad->Axis(axisY))));

        // se h� qualquer movimento no eixo
        if (magnitude > 0)
        {
            axisCtrl = false;
            start = timer.Stamp();
            return true;
        }
    }
    // sen�o aguarda o momento certo para testar
    else if (timer.Elapsed(start, time))
    {
        axisCtrl = true;
    }

    // eixo n�o acionado ou tempo n�o atingido*/
    return false;
}

// -------------------------------------------------------------------------------

void Boss::Move(Vector&& v)
{
    // soma vetor movimento (v) ao vetor velocidade
    speed.Add(v);

    // limita velocidade m�xima
    if (speed.Magnitude() > 10.0f)
        speed.ScaleTo(10.0f);
}

// -------------------------------------------------------------------------------

void Boss::Update()
{
    // ajusta �ngulo do vetor
    float angle = Line::Angle(Point(x, y), Point(BasicAI::player->X(), BasicAI::player->Y()));
    speed.RotateTo(angle);
    RotateTo(-angle + 90);
    Move(Vector(angle, 10 * gameTime));

    // movimenta objeto pelo seu vetor velocidade
    float spaceBetweenShips = Point::Distance(Point(x, y), Point(BasicAI::player->X(), BasicAI::player->Y()));
    if (spaceBetweenShips >= 500) {
        Translate(speed.XComponent() * 50.0f * gameTime, -speed.YComponent() * 50.0f * gameTime);
    }else if(Point::Distance(Point(x, y), Point(BasicAI::player->X(), BasicAI::player->Y())) < 400){
        speed.RotateTo(angle);
        speed.ScaleTo(-300.0f * gameTime);
        Translate(speed.XComponent() * 100.0f * gameTime, -speed.YComponent() * 100.0f * gameTime);
    }

    // A nave vai atirar para o mesmo objeto que esta olhando
    if (keysCtrl)
    {
        // se h� qualquer seta pressionada
        keysCtrl = false;
        start = timer.Stamp();
        switch (nivel) {
        case FACIL: {
            arma->ModificarArma(MISSEL);
           
            if (vida[nivel] <= 50) {
                arma->DisparoPosicao(angle, x - 30, y-20, BasicAI::player);
                arma->DisparoPosicao(angle, x + 30, y+20, BasicAI::player);
                intervaloDisparo[NIVEL::FACIL] = 0.7f;
            }
            else if (vida[nivel] <= 100) {
                // acionar voz
                float randX = RandF(x - 15.0f, x + 30.0f).Rand();
                arma->DisparoPosicao(angle, randX, y, BasicAI::player);
                intervaloDisparo[NIVEL::FACIL] = 1.2f;
            }
            else {
                arma->DisparoPosicao(angle, x - 30, y - 20, BasicAI::player);
                arma->DisparoPosicao(angle, x + 30, y + 20, BasicAI::player);
            }
            break;
        }

        case MODERADO: {
            arma->ModificarArma(LASER);
            arma->DisparoPosicao(angle, x, y-187, BasicAI::player);
            break;
        }
        case DIFICIL: {
            arma->ModificarArma(LASER);
            arma->DisparoPosicao(angle, x + 185*cos(speed.Radians()), y - 120*sin(speed.Radians()), BasicAI::player);
            arma->ModificarArma(MISSEL);
            arma->DisparoPosicao(angle, (x - 80) + 185 * cos(speed.Radians()), y - 120 * sin(speed.Radians()), BasicAI::player);
            arma->DisparoPosicao(angle, (x + 80) + 185 * cos(speed.Radians()), y - 120 * sin(speed.Radians()), BasicAI::player);
            break;
        }
        }
        
    }
    // sen�o aguarda o momento certo
    else if (timer.Elapsed(start, intervaloDisparo[nivel]))
    {
        keysCtrl = true;
    }

    if (vida[nivel] <= 0 && nivel != NIVEL::DIFICIL) {// se chegar no ultimo nivel nao tem mais o que fazer
        nivel = (nivel + 1) % 3; // numero de niveis que o boss fica durante a batalha
        AdicionarKamicazi(10);
    }

    if (nivel == NIVEL::DIFICIL && vida[nivel] <= 0)
        window->Close();
}

// ---------------------------------------------------------------------------------

void Boss::Draw()
{
    sprite->Draw(x, y, Layer::MIDDLE, 1.0f, -speed.Angle() + 90.0f);
}

// -------------------------------------------------------------------------------

void Boss::OnCollision(Object* obj)
{
  
     
}

// -------------------------------------------------------------------------------

void Boss::DanoSofrido(float dano) {
    vida[nivel] = vida[nivel] - dano;
    
}

// -------------------------------------------------------------------------------

float Boss::Vida() { return vida[nivel]; }

// -------------------------------------------------------------------------------

void Boss::AdicionarKamicazi(int qtd) {
    for (int i = 0; i < qtd; ++i) {
        float posicaoX = RandF(40, 3800).Rand();
        float posicaoY = RandF(60, 2100).Rand();
        BasicAI::scene->Add(new Kamikaze(BasicAI::player,posicaoX,posicaoY), MOVING);
    }
}