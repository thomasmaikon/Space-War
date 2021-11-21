#include "Arma.h"
#include "BasicAI.h"
#include "Missile.h"
Arma::Arma(uint tipoDeArma) {
	tipoArma = tipoDeArma;
}

Arma::~Arma() {

}

void Arma::Disparo(float angulo, Object* obj) {

	switch (tipoArma) {
		case TipoArma::FOGUETE:
			BasicAI::audio->Play(FIRE);
			BasicAI::scene->Add(new Missile(angulo,obj->X(),obj->Y()), STATIC);
			break;

	}
}

void Arma::ModificarArma(uint escolha) {
	tipoArma = escolha;
}