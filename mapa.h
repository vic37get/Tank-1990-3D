//Implementação do mapa.

#ifndef MAPA_H
#define MAPA_H

#include <cstdio>
#include "bloco.h"
#include "tank.h"
#include "jogador.h"
#include "inimigo.h"
#include "projetil.h"
#include "bonus.h"
#define tamMapa 15

/*
- Detalhamento do Mapa
	- Chão: 0
	- Agua: 1
	- Tijolo: 2
	- Metal: 3
	- Arbusto: 4
	- Gelo: 5
	- Aguia: 6
	- Parede externa: 7
*/

bool startGame = false;
bool gameOverAudio = false;
bool explosion = false;
bool atiraAudio = false;

int mapa[tamMapa][tamMapa] =   {{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
								{7, 2, 2, 2, 0, 0, 2, 6, 2, 0, 2, 2, 2, 2, 7},
								{7, 2, 3, 2, 0, 0, 2, 2, 2, 0, 2, 5, 5, 5, 7},
								{7, 5, 2, 2, 0, 0, 0, 0, 0, 0, 5, 5, 0, 5, 7},			
								{7, 5, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 7},
								{7, 5, 5, 5, 5, 0, 2, 3, 3, 0, 1, 3, 1, 4, 7},
								{7, 1, 1, 1, 5, 1, 1, 0, 2, 0, 1, 0, 0, 4, 7},	
								{7, 4, 4, 4, 5, 3, 1, 4, 4, 0, 1, 4, 4, 4, 7},
								{7, 5, 4, 2, 5, 2, 1, 1, 1, 0, 1, 2, 2, 4, 7},
								{7, 4, 4, 3, 5, 3, 1, 0, 2, 0, 3, 3, 2, 4, 7},
								{7, 4, 1, 1, 1, 1, 1, 0, 2, 2, 1, 1, 2, 3, 7},
								{7, 4, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 2, 2, 7},
								{7, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 0, 0, 0, 7},
								{7, 0, 0, 0, 3, 0, 0, 0, 2, 2, 2, 0, 0, 0, 7},
								{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}
}; 
 	

void criaMapa(Jogador jogador, Inimigo inimigo1, Inimigo inimigo2, Inimigo inimigo3){
	GLfloat w = 1.0, h = 1.0, x = 0, y = 0; 
	for (int i = 0; i < tamMapa; i++){
		for (int j = 0; j < tamMapa; j++){
			if (mapa[i][j] == 0.0){
				//Desenha o Chão.
				chao(i, j, x, y, h, w);
			}
			else if(mapa[i][j] == 1.0){
				//Desenha a Água.
				agua(i, j, x, y, h, w);
			}
			else if(mapa[i][j] == 2.0){
				//Desenha o Tijolo.
				tijolo(i, j, x, y, h, w);
			}
			else if(mapa[i][j] == 3.0){
				//Desenha o Metal.
				metal(i, j, x, y, h, w);
			}
			else if(mapa[i][j] == 4.0){
				//Desenha o Arbusto.
				arbusto(i, j, x, y, h, w);
			}
			else if(mapa[i][j] == 5.0){
				//Desenha o Pista.
				gelo(i, j, x, y, h, w);
			}
			else if(mapa[i][j] == 6.0){
				//Desenha o Aguia.
				aguia(i, j, x, y, h, w);
			}
			else if(mapa[i][j] == 7.0){
				//Tijolos Laterais.
				parede(i, j, x, y, h, w);
			}
		}
	}
	
	if(startGame == false){
		PlaySound("sounds/gamestart.wav", NULL, SND_ASYNC|SND_FILENAME);
		startGame = true;
	}
	
	if(gameOverAudio){
		PlaySound("sounds/gameover.wav", NULL, SND_ASYNC|SND_FILENAME);
		gameOverAudio = false;
	}
	
	if(explosion){
		PlaySound("sounds/explosion.wav", NULL, SND_ASYNC|SND_FILENAME);
		explosion = false;
	}
	
	if(atiraAudio){
		PlaySound("sounds/fire.wav", NULL, SND_ASYNC|SND_FILENAME);
		atiraAudio = false;
	}
	
	//Se o jogador ainda estiver vivo, ele é desenhado.
	if(jogador.vivo){
		desenhaTank(jogador.x, jogador.y, jogador.direcaoCano, jogador.R, jogador.G, jogador.B);
	}
	
	if(inimigo1.vivo){
		desenhaTank(inimigo1.x, inimigo1.y, inimigo1.direcaoCano, inimigo1.R, inimigo1.G, inimigo1.B);
	}
	
	if(inimigo2.vivo){
		desenhaTank(inimigo2.x, inimigo2.y, inimigo2.direcaoCano, inimigo2.R, inimigo2.G, inimigo2.B);
	}
	
	if(inimigo3.vivo){
		desenhaTank(inimigo3.x, inimigo3.y, inimigo3.direcaoCano, inimigo3.R, inimigo3.G, inimigo3.B);
	}
		
}
#endif