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
#include "texturaTijolo.h"
#include "texturaAgua.h"
#include "texturaMetal.h"
#include "texturaGelo.h"
#include "texturaArbusto.h"
#define tamMapa 15

//Texturas
#define QUANT_TEX 5
unsigned int id_texturas[QUANT_TEX]; //nomes identificadores de textura

void textura(){
	
	/* Prepara a textura */
  glGenTextures(QUANT_TEX, id_texturas); //gera nomes identificadores de texturas
  
  glBindTexture(GL_TEXTURE_2D, id_texturas[0]); //Textura tijolo
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_tijolo, TEXTURE_tijolo, 0, GL_RGB, GL_UNSIGNED_BYTE, tijolo_data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  
  glBindTexture(GL_TEXTURE_2D, id_texturas[1]); //Textura agua
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_agua, TEXTURE_agua, 0, GL_RGB, GL_UNSIGNED_BYTE, agua_data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  
  glBindTexture(GL_TEXTURE_2D, id_texturas[2]); //Textura metal
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_metal, TEXTURE_metal, 0, GL_RGB, GL_UNSIGNED_BYTE, metal_data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  
  glBindTexture(GL_TEXTURE_2D, id_texturas[3]); //Textura gelo
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_gelo, TEXTURE_gelo, 0, GL_RGB, GL_UNSIGNED_BYTE, gelo_data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  
  glBindTexture(GL_TEXTURE_2D, id_texturas[4]); //Textura arbusto
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_arbusto, TEXTURE_arbusto, 0, GL_RGB, GL_UNSIGNED_BYTE, arbusto_data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
  glEnable(GL_TEXTURE_2D);
}

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
				glDisable(GL_TEXTURE_2D);
				chao(i, j, x, y, h, w);
				glEnable(GL_TEXTURE_2D);
			}
			else if(mapa[i][j] == 1.0){
				//Desenha a Água.
				glBindTexture(GL_TEXTURE_2D, id_texturas[1]);
				agua(i, j, x, y, h, w);
			}
			else if(mapa[i][j] == 2.0){
				//Desenha o Tijolo.
				glBindTexture(GL_TEXTURE_2D, id_texturas[0]);
				tijolo(i, j, x, y, h, w);
			}
			else if(mapa[i][j] == 3.0){
				//Desenha o Metal.
				glBindTexture(GL_TEXTURE_2D, id_texturas[2]);
				metal(i, j, x, y, h, w);
			}
			else if(mapa[i][j] == 4.0){
				//Desenha o Arbusto.
				glBindTexture(GL_TEXTURE_2D, id_texturas[4]);
				arbusto(i, j, x, y, h, w);
			}
			else if(mapa[i][j] == 5.0){
				//Desenha o gelo.
				glBindTexture(GL_TEXTURE_2D, id_texturas[1]);
				gelo(i, j, x, y, h, w);
			}
			else if(mapa[i][j] == 6.0){
				//Desenha o Aguia.
				glDisable(GL_TEXTURE_2D);
				aguia(i, j, x, y, h, w);
				glEnable(GL_TEXTURE_2D);
			}
			else if(mapa[i][j] == 7.0){
				//Tijolos Laterais.
				glDisable(GL_TEXTURE_2D);
				parede(i, j, x, y, h, w);
				glEnable(GL_TEXTURE_2D);
			}
		}
	}
	
	glDisable(GL_TEXTURE_2D);
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
	glEnable(GL_TEXTURE_2D);
}
#endif