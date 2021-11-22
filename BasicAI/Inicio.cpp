
#include "Inicio.h"

void Inicio::Init() {
	backg = new Background("Resources/ResourcesUnidade3/Home.jpg");

	viewport.left   = 0;
	viewport.top    = 0;
	viewport.right  = backg->Width();
	viewport.bottom = backg->Height();
}

void Inicio::Finalize() {
	delete backg;
}

void Inicio::Draw() {
	backg->Draw(viewport);
}

void Inicio::Update() {

}