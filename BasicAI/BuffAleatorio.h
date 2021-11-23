#ifndef _BASICAI_BUFFALEATORIO_H_
#define _BASICAI_BUFFALEATORIO_H_


#include "Object.h"
#include "Sprite.h"
#include "Timer.h"
enum BUFF {DISPARO, ESCUDO};

class BuffAleatorio : public Object {
private:
	Sprite* bolha;
	Sprite* buff;

	Timer timer;
	float start;
	float intervaloSurgimentoBuffer;

	bool coletado;
	void GerarNovoBuff();
	void NovaPosicao();

	uint tipo;

public:
	BuffAleatorio();
	~BuffAleatorio();

	void Update();
	void Draw();
	void OnCollision(Object* obj);
	uint Tipo();

	Sprite* Escudo();
};

inline uint BuffAleatorio::Tipo() { return tipo; }
inline Sprite* BuffAleatorio::Escudo() { return new Sprite("Resources/ResourcesUnidade3/bolha.png");}
#endif