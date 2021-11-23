#include "BasicAI.h"
#include "BuffAleatorio.h"
#include "Random.h"

BuffAleatorio::BuffAleatorio() {
	bolha = new Sprite("Resources/ResourcesUnidade3/bolha.png");
	
	BBox(new Circle(25.0f));
	NovaPosicao();
	GerarNovoBuff();

	coletado = false;
	intervaloSurgimentoBuffer = 10.0f;

	type = BUFFER;
}

BuffAleatorio::~BuffAleatorio() {
	delete bolha;
	delete buff;
}

void BuffAleatorio::OnCollision(Object* obj) {
	if (obj->Type() == Ids::PLAYER) {
		auto player = (Player*)obj;
		
		switch (tipo)
		{
		case BUFF::DISPARO: {
			player->Disparo(2);
			break;
		}

		}
		
		coletado = true;
		start = timer.Stamp();
		MoveTo(-50000, -50000);
	}
}

void BuffAleatorio::Update() {
	if (coletado) {
		if (timer.Elapsed(start, intervaloSurgimentoBuffer)) {
			NovaPosicao();
			GerarNovoBuff();
			coletado = false;
		}
	}
}

void BuffAleatorio::Draw() {
	if (!coletado) {
		bolha->Draw(x, y);
		buff->Draw(x, y);
	}
}

void BuffAleatorio::GerarNovoBuff() {
	tipo = RandI(0,1).Rand();

	switch (tipo)
	{
		case BUFF::DISPARO: {
			buff = new Sprite("Resources/ResourcesUnidade3/buffDisparo.png");
			break;
		}
		case BUFF::ESCUDO: {
			buff = new Sprite("Resources/ResourcesUnidade3/escudo.png");
			break;
		}
	}
}

void BuffAleatorio::NovaPosicao() {
	float posicaoX = RandF(40, 3800).Rand();
	float posicaoY = RandF(60, 2100).Rand();
	MoveTo(posicaoX, posicaoY);
}