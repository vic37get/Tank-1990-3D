//Implementação do mapa.

#ifndef MAPA_H
#define MAPA_H

#include <cstdio>
#include "bloco.h"
#include "jogador.h"
#include "inimigo.h"
#include "projetil.h"
#include "bonus.h"
#include "audio.h"
#include <sstream>
using std::stringstream;
#include <string>
using std::string;


//Texturas dos blocos
#include "texturas/texturaTijolo.h"
#include "texturas/texturaAgua.h"
#include "texturas/texturaMetal.h"
#include "texturas/texturaGelo.h"
#include "texturas/texturaArbusto.h"
#include "texturas/texturaParede.h"
#include "texturas/texturaChao.h"
#include "texturas/texturaAguia.h"
//Texturas dos bonus
#include "texturas/texturaBonusGun.h"
#include "texturas/texturaBonusStone.h"
#include "texturas/texturaBonusLife.h"
#include "texturas/texturaBonusSpeed.h"
#include "texturas/texturaBonusBoat.h"
#include "texturas/texturaTank.h"
#include "texturas/texturaFundo.h"



#define tamMapa 15

//Texturas
#define QUANT_TEX 14
int coluna = 0;
float tam_tank = 0.8;
unsigned int id_texturas[15]; //nomes identificadores de textura

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
  
  glBindTexture(GL_TEXTURE_2D, id_texturas[5]); //Textura parede
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_parede, TEXTURE_parede, 0, GL_RGB, GL_UNSIGNED_BYTE, parede_data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  
  glBindTexture(GL_TEXTURE_2D, id_texturas[6]); 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_chao, TEXTURE_chao, 0, GL_RGB, GL_UNSIGNED_BYTE, chao_data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  
  glBindTexture(GL_TEXTURE_2D, id_texturas[7]); 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_aguia, TEXTURE_aguia, 0, GL_RGB, GL_UNSIGNED_BYTE, aguia_data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
  
  //Texturas dos bonus
  glBindTexture(GL_TEXTURE_2D, id_texturas[8]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_bonus_gun, TEXTURE_bonus_gun, 0, GL_RGB, GL_UNSIGNED_BYTE, textura_bonus_gun_data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  
  glBindTexture(GL_TEXTURE_2D, id_texturas[9]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_bonus_stone, TEXTURE_bonus_stone, 0, GL_RGB, GL_UNSIGNED_BYTE, textura_bonus_stone_data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  
  glBindTexture(GL_TEXTURE_2D, id_texturas[10]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_bonus_life, TEXTURE_bonus_life, 0, GL_RGB, GL_UNSIGNED_BYTE, textura_bonus_life_data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  
  glBindTexture(GL_TEXTURE_2D, id_texturas[11]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_bonus_speed, TEXTURE_bonus_speed, 0, GL_RGB, GL_UNSIGNED_BYTE, textura_bonus_speed_data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  
  glBindTexture(GL_TEXTURE_2D, id_texturas[12]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_bonus_boat, TEXTURE_bonus_boat, 0, GL_RGB, GL_UNSIGNED_BYTE, textura_bonus_boat_data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  
  
  //Textura do Tank
  glBindTexture(GL_TEXTURE_2D, id_texturas[13]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_tank, TEXTURE_tank, 0, GL_RGB, GL_UNSIGNED_BYTE, textura_tank_data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  
  
  //Textura do Background
  glBindTexture(GL_TEXTURE_2D, id_texturas[14]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_fundo, TEXTURE_fundo, 0, GL_RGB, GL_UNSIGNED_BYTE, textura_fundo_data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
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

int mapa[tamMapa][tamMapa] =   {{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
								{7, 2, 2, 2, 0, 0, 2, 6, 2, 0, 2, 2, 2, 2, 7},
								{7, 2, 3, 2, 0, 0, 2, 2, 2, 0, 2, 5, 5, 5, 7},
								{7, 5, 2, 2, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 7},			
								{7, 5, 3, 2, 0, 0, 0, 0, 0, 0, 5, 0, 0, 4, 7},
								{7, 5, 5, 5, 5, 0, 2, 3, 3, 0, 1, 3, 1, 4, 7},
								{7, 1, 1, 1, 5, 1, 1, 0, 2, 0, 1, 0, 0, 4, 7},	
								{7, 4, 4, 4, 5, 3, 1, 4, 4, 0, 1, 4, 4, 4, 7},
								{7, 5, 4, 2, 5, 2, 1, 1, 1, 0, 1, 2, 2, 4, 7},
								{7, 4, 4, 3, 0, 3, 1, 0, 2, 0, 3, 3, 2, 4, 7},
								{7, 4, 1, 1, 1, 1, 1, 0, 2, 2, 1, 1, 2, 3, 7},
								{7, 4, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 2, 2, 7},
								{7, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 0, 0, 0, 7},
								{7, 0, 0, 0, 3, 0, 0, 0, 2, 2, 2, 0, 0, 0, 7},
								{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}
};

// Plano de fundo
void background() {
    // Define a matriz de projeção como matriz de trabalho atual
    glMatrixMode(GL_PROJECTION);
    // Salva a matriz de projeção atual na pilha
    glPushMatrix();
    // Carrega a matriz identidade para a matriz de projeção
    glLoadIdentity();
    // Define uma projeção ortográfica 2D com coordenadas de recorte de (0,0) a (1,1) no plano XY
    glOrtho(0, 1, 0, 1, -1, 1);
    // Desabilita o teste de profundidade, para que a textura do plano de fundo não seja obscurecida por objetos 3D
    glDisable(GL_DEPTH_TEST);
    // Desabilita a iluminação, para que a textura do plano de fundo seja renderizada sem sombreamento
    glDisable(GL_LIGHTING);
    // Desabilita a escrita no buffer de profundidade, para que a textura do plano de fundo não afete outros objetos 3D
    glDepthMask(GL_FALSE);
    // Associa a textura com o ID id_texturas[14] ao plano de fundo
    glBindTexture(GL_TEXTURE_2D, id_texturas[14]);
    // Inicia a definição de um polígono (quadrilátero) para renderizar a textura
    glBegin(GL_QUADS);
    // Define a cor do polígono como branco
    glColor3f(1.0, 1.0, 1.0);
    // Define as coordenadas de textura e vértices do quadrilátero
    glTexCoord2i(0, 0); glVertex2i(-1, -1);
    glTexCoord2i(1, 0); glVertex2i(1, -1);
    glTexCoord2i(1, 1); glVertex2i(1, 1);
    glTexCoord2i(0, 1); glVertex2i(-1, 1);
    // Finaliza a definição do polígono
    glEnd();
    // Habilita novamente o teste de profundidade para objetos 3D futuros
    glEnable(GL_DEPTH_TEST);
    // Habilita novamente a iluminação para objetos 3D futuros
    glEnable(GL_LIGHTING);
    // Habilita novamente a escrita no buffer de profundidade para objetos 3D futuros
    glDepthMask(GL_TRUE);
    // Restaura a matriz de projeção anterior que estava na pilha
    glPopMatrix();
    // Define a matriz de modelo e visualização como matriz de trabalho atual
    glMatrixMode(GL_MODELVIEW);
}




void desenhaBonus(int tipo_bonus, float i, float j, int rotacao){
	switch(tipo_bonus){
	case 1:
		//Cria uma barreira de pedra ao redor da aguia.
		glBindTexture(GL_TEXTURE_2D, id_texturas[9]);
		visualBonus(i, j, rotacao);
		break;
	case 2:
		glBindTexture(GL_TEXTURE_2D, id_texturas[10]);
		//Adiciona uma vida ao jogador.
		visualBonus(i, j, rotacao);
		break;
	case 3:
		//Adiciona velocidade de movimento ao jogador e velocidade de tiro.
		glBindTexture(GL_TEXTURE_2D, id_texturas[11]);
		visualBonus(i, j, rotacao);
		break;
	case 4:
		//Permite andar na água.
		glBindTexture(GL_TEXTURE_2D, id_texturas[12]);
		visualBonus(i, j, rotacao);
		break;
	case 5:
		//Destroi blocos de metal.
		glBindTexture(GL_TEXTURE_2D, id_texturas[8]);
		visualBonus(i, j, rotacao);
		break;
	default:
		break;
	}
	
}

void desenhaTank(float i, float j, int direcao, int R, int G, int B){
	//Corpo do tank.
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, id_texturas[13]);
		glColor3f(R, G, B);
		glTranslatef (j*1, i*1, 0.5);
		glScalef (tam_tank, tam_tank, 0.5);
		draw_object_smooth();
		glRotatef(direcao, 0.0 , 0.0 , 1.0);
		glDisable(GL_TEXTURE_2D);
		//Esteira direita.
		glPushMatrix();
			glColor3f(0.1, 0.1, 0.1);
			glTranslatef(0.55, 0, 0);
			glScalef (0.3, 1.3, 0.6);
			draw_object_smooth();
		glPopMatrix();
		//Esteira esquerda.
		glPushMatrix();
			glColor3f(0.1, 0.1, 0.1);
			glTranslatef(-0.55, 0, 0);
			glScalef (0.3, 1.3, 0.6);
			draw_object_smooth();
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
		//Parte de cima do tank.
		glPushMatrix();
			glColor3f(R - 0.5, G - 0.5, B - 0.5);
			glTranslatef(0, 0, 0.5);
			glScalef(0.6, 0.6, 0.7);
			draw_object_smooth();
        glPopMatrix();
		//Cano do tank.
		glPushMatrix();
			glTranslatef(0, 0.5, 0.3);
			glScalef (0.3, 1.2, 0.3);
			draw_object_smooth();
		glPopMatrix();
    glPopMatrix();
}
 	

void criaMapa(Jogador jogador, Inimigo inimigo1, Inimigo inimigo2, Inimigo inimigo3){
	GLfloat w = 1.0, h = 1.0, x = 0, y = 0; 
	for (int i = 0; i < tamMapa; i++){
		for (int j = 0; j < tamMapa; j++){
			if (mapa[i][j] == 0.0){
				//Desenha o Chão.
				glBindTexture(GL_TEXTURE_2D, id_texturas[6]);
				chao(i, j, x, y, h, w);
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
				glBindTexture(GL_TEXTURE_2D, id_texturas[3]);
				gelo(i, j, x, y, h, w);
			}
			else if(mapa[i][j] == 6.0){
				//Desenha a Aguia.
				glBindTexture(GL_TEXTURE_2D, id_texturas[7]);
				aguia(i, j, x, y, h, w);
			}
			else if(mapa[i][j] == 7.0){
				//Parede.
				glBindTexture(GL_TEXTURE_2D, id_texturas[5]);
				parede(i, j, x, y, h, w);
			}
		}
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