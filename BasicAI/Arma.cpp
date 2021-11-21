#include "Arma.h"
#include "BasicAI.h"
#include "Laser.h"
#include "Missel.h"

Arma::Arma(uint tipoDeArma) {
	tipoArma = tipoDeArma;
}

Arma::~Arma() {

}

void Arma::Disparo(float angulo, Object* obj, Object * inimigo) {

	switch (tipoArma) {
	case TipoArma::MISSEL:{
		BasicAI::audio->Play(FIRE);
		BasicAI::scene->Add(new Missel(angulo, obj->X(),obj->Y() ,inimigo), STATIC);
		break;
	}
	case TipoArma::LASER: {
			BasicAI::audio->Play(FIRE);
			BasicAI::scene->Add(new Laser(angulo,obj->X(),obj->Y()), STATIC);
			break;
		}
	}
}



void Arma::ModificarArma(uint escolha) {
	tipoArma = escolha;
}