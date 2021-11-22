#ifndef _BASICAI_BUFFALEATORIO_H_
#define _BASICAI_BUFFALEATORIO_H_


#include "Object.h"
#include "Sprite.h"
#include "Timer.h"
enum BUFF {DISPARO};

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

public:
	BuffAleatorio();
	~BuffAleatorio();

	void Update();
	void Draw();
	void OnCollision(Object* obj);
	
};

#endif