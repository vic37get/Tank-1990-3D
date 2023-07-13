//Implementação do mapa.
#include <cstdio>
#include "bloco.h"
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

void criaMapa(){
	GLfloat w = 1.0, h = 1.0, x = 0, y = 0;
	for (int i = 0; i < tamMapa; i++){
		for (int j = 0; j < tamMapa; j++){
			if (mapa[i][j] == 0){
				//Desenha o Chão.
				chao(h, w, x, y, j, i);
			}
			else if(mapa[i][j] == 1){
				//Desenha a Água.
				agua(h, w, x, y, j, i);
			}
			else if(mapa[i][j] == 2){
				//Desenha o Tijolo.
				tijolo(h, w, x, y, j, i);
			}
			else if(mapa[i][j] == 3){
				//Desenha o Metal.
				metal(h, w, x, y, j, i);
			}
			else if(mapa[i][j] == 4){
				//Desenha o Arbusto.
				arbusto(h, w, x, y, j, i);
			}
			else if(mapa[i][j] == 5){
				//Desenha o Pista.
				pista(h, w, x, y, j, i);
			}
			else if(mapa[i][j] == 6){
				//Desenha o Aguia.
				aguia(h, w, x, y, j, i);
			}
			else if(mapa[i][j] == 7){
				//Tijolos Laterais.
				parede(h, w, x, y, j, i);
			}
		}
	}
	
}