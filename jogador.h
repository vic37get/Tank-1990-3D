//Implementação do jogador, comandos, estruturas etc.
#ifndef JOGADOR_H
#define JOGADOR_H

#include "projetil.h"

typedef struct{
	float x;
	float y;
	float velocidade;
	//Direção do cano do tank.
	float direcaoCano;
	//Definição das cores do tank.
	float R;
	float G;
	float B;
	//3 vidas
	float vida;
	//Vivo ou morto
	bool vivo;
	Projetil projetil;
}Jogador;

#endif

