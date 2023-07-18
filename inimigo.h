//Implementação do inimigo, comandos, estruturas etc.
#ifndef INIMIGO_H
#define INIMIGO_H

typedef struct{
	float x;
	float y;
	float velocidade;
	float direcaoCano;
	int R;
	int G;
	int B;
	bool vivo;
	Projetil projetil;
}Inimigo;

#endif