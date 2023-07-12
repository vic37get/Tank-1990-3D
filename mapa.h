//Implementação do mapa.
#include <cstdio>
#include "bloco.h"

/*
- Detalhamento do Mapa
	- Chão: 0
	- Agua: 1
	- Tijolo: 2
	- Metal: 3
	- Arbusto: 4
	- Pista: 5
	- Aguia: 6
*/

int mapa[13][13] = {
                                     {0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0},
									 {4, 2, 2, 2, 2, 0, 0, 0, 0, 2, 0, 0, 0},
									 {4, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 2, 2},
									 {4, 1, 1, 1, 1, 1, 0, 2, 2, 1, 1, 2, 3},
									 {4, 4, 3, 3, 3, 1, 0, 2, 0, 3, 3, 2, 4},
									 {2, 4, 2, 2, 2, 1, 1, 1, 0, 1, 2, 2, 4},
									 {4, 4, 4, 4, 3, 1, 4, 4, 3, 1, 4, 4, 4},
									 {1, 1, 1, 0, 1, 1, 2, 2, 0, 1, 0, 0, 4},
									 {2, 0, 0, 0, 0, 2, 3, 3, 0, 1, 1, 3, 4},
									 {5, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
									 {5, 2, 2, 0, 0, 0, 0, 0, 3, 2, 2, 0, 5},
									 {3, 2, 2, 0, 0, 2, 2, 2, 0, 2, 5, 5, 5},
									 {2, 2, 2, 0, 0, 2, 6, 2, 0, 2, 2, 2, 2}
}; 	

void criaMapa(){
	for (int i = 0; i < 13; i++){
		for (int j = 0; j < 13; j++){
			if (mapa[i][j] == 0){
				//Desenha o Chão.
				printf("Ponto: %d, Chao\n", mapa[i][j]);
				chao();
			}
			else if(mapa[i][j] == 1){
				//Desenha a Água.
				printf("Ponto: %d, Agua\n", mapa[i][j]);
				agua();
			}
			else if(mapa[i][j] == 2){
				//Desenha o Tijolo.
				printf("Ponto: %d, Tijolo\n", mapa[i][j]);	
				tijolo();
			}
			else if(mapa[i][j] == 3){
				//Desenha o Metal.
				printf("Ponto: %d, Metal\n", mapa[i][j]);
				metal();
			}
			else if(mapa[i][j] == 4){
				//Desenha o Arbusto.
				printf("Ponto: %d, Arbusto\n", mapa[i][j]);
				arbusto();
			}
			else if(mapa[i][j] == 5){
				//Desenha o Pista.
				printf("Ponto: %d, Pista\n", mapa[i][j]);
				pista();
			}
			else if(mapa[i][j] == 6){
				//Desenha o Aguia.
				printf("Ponto: %d, Aguia\n", mapa[i][j]);
				aguia();
			}
		}
	}
	
}