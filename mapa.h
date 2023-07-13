//Implementação do mapa.

#ifndef MAPA_H
#define MAPA_H
#endif

#include <cstdio>
#include "bloco.h"
#include "tank.h"
#include "jogador.h"
#include "inimigo.h"
#define tamMapa 15



/*
- Detalhamento do Mapa
	- Chão: 0
	- Agua: 1
	- Tijolo: 2
	- Metal: 3
	- Arbusto: 4
	- Pista: 5
	- Aguia: 6
	- Parede externa: 7
*/

int mapa[tamMapa][tamMapa] = {	{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
								{7, 2, 2, 2, 0, 0, 2, 6, 2, 0, 2, 2, 2, 2, 7},
								{7, 3, 2, 2, 0, 0, 2, 2, 2, 0, 2, 5, 5, 5, 7},
								{7, 5, 2, 2, 0, 3, 0, 0, 0, 0, 2, 2, 0, 5, 7},			
								{7, 5, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 7},
								{7, 2, 0, 0, 0, 0, 2, 3, 3, 0, 1, 1, 3, 4, 7},
								{7, 1, 1, 1, 0, 1, 1, 0, 2, 0, 1, 0, 0, 4, 7},	
								{7, 4, 4, 4, 0, 3, 1, 4, 4, 3, 1, 4, 4, 4, 7},
								{7, 2, 4, 2, 0, 2, 1, 1, 1, 0, 1, 2, 2, 4, 7},
								{7, 4, 4, 3, 0, 3, 1, 0, 2, 0, 3, 3, 2, 4, 7},
								{7, 4, 1, 1, 1, 1, 1, 0, 2, 2, 1, 1, 2, 3, 7},
								{7, 4, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 2, 2, 7},
								{7, 4, 2, 2, 2, 2, 0, 0, 0, 0, 2, 0, 0, 0, 7},
								{7, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 7},
								{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}
}; 	

void criaMapa(Jogador jogador, Inimigo inimigo1, Inimigo inimigo2, Inimigo inimigo3){
	for (int i = 0; i < tamMapa; i++){
		for (int j = 0; j < tamMapa; j++){
			if (mapa[i][j] == 0){
				//Desenha o Chão.
				chao(i, j);
			}
			else if(mapa[i][j] == 1){
				//Desenha a Água.
				agua(i, j);
			}
			else if(mapa[i][j] == 2){
				//Desenha o Tijolo.
				tijolo(i, j);
			}
			else if(mapa[i][j] == 3){
				//Desenha o Metal.
				metal(i, j);
			}
			else if(mapa[i][j] == 4){
				//Desenha o Arbusto.
				arbusto(i, j);
			}
			else if(mapa[i][j] == 5){
				//Desenha o Pista.
				pista(i, j);
			}
			else if(mapa[i][j] == 6){
				//Desenha o Aguia.
				aguia(i, j);
			}
			else if(mapa[i][j] == 7){
				//Tijolos Laterais.
				parede(i, j);
			}
		}
	}
	desenhaTank(jogador.x, jogador.y, jogador.direcaoCano, jogador.R, jogador.G, jogador.B);
	
	desenhaTank(inimigo1.x, inimigo1.y, inimigo1.direcaoCano, inimigo1.R, inimigo1.G, inimigo1.B);
	desenhaTank(inimigo2.x, inimigo2.y, inimigo2.direcaoCano, inimigo2.R, inimigo2.G, inimigo2.B);
	desenhaTank(inimigo3.x, inimigo3.y, inimigo3.direcaoCano, inimigo3.R, inimigo3.G, inimigo3.B);
}