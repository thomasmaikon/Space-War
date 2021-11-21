#include "Boss.h"
#include "BasicAI.h"
#include "Player.h"

// -------------------------------------------------------------------------------
Boss::Boss()
{

    arma = new Arma(TipoArma::FOGUETE);

    sprite = new Sprite("Resources/Player.png");
    //missile = new Image("Resources/Missile.png");
    speed.RotateTo(90.0f);
    speed.ScaleTo(0.0f);
    BBox(new Circle(18.0f));
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

bool Boss::KeysTimed(bool pressed, float time)
{
    // se j� passou o tempo para o pr�ximo disparo
    if (keysCtrl)
    {
        // se h� qualquer seta pressionada
        if (pressed)
        {
            keysCtrl = false;
            start = timer.Stamp();
            return true;
        }
    }
    // sen�o aguarda o momento certo
    else if (timer.Elapsed(start, time))
    {
        keysCtrl = true;
    }

    // teclas n�o pressionadas ou tempo n�o atingido
    return false;
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
        arma->Disparo(angle,this);
    }
    // sen�o aguarda o momento certo
    else if (timer.Elapsed(start, 1.0f))
    {
        keysCtrl = true;
    }
}

// ---------------------------------------------------------------------------------

void Boss::Draw()
{
    sprite->Draw(x, y, Layer::MIDDLE, 1.0f, -speed.Angle() + 90.0f);
}

void Boss::OnCollision(Object* obj)
{
}

// -------------------------------------------------------------------------------
