/*
 * Computação Gráfica
 * Codigo: Jogo Tank-1990 3D
 * Autores: Jhoisnáyra Vitoria Rodrigues de Almeida, Victor Ribeiro da Silva
 */

// Bibliotecas utilizadas pelo OpenGL
#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include <cmath>
#include <cstdio>
#include <cstdlib>

#include <mmsystem.h>

#include "mapa.h"
#include "jogador.h"
#include "inimigo.h"
#include "projetil.h"

// Variaveis Globais
int h, w = 0;

//Partida
bool venceu = false;
bool game_over = false;

//Bonus
bool bonus_ativo = false;
int posicaoBonus, tipo_bonus;
float bonusX, bonusY;
bool bonus_boat = false;
bool bonus_gun = false;
bool bonus_wall = false;

//Movimentos Inimigos
int mov_inimigo1, mov_inimigo2, mov_inimigo3;

//Instancia de Jogador.
//X, Y, Velocidade, DirecaoCano, R, G, B, Vidas, Vivo. Projetil{ x, y, velocidade, distancia, direcao, tiro.}
Jogador jogador = {1, 4, 0.1, 0, 1.0, 1.0, 0.0, 3, true, {1, 4, 0.25f, 5.0f, 0, false}};

//Instancia de Inimigo.
//x, y, velocidade, direcaoCano, R, G, B, vivo. Projetil{ x, y, velocidade, distancia, direcao, tiro.}
Inimigo inimigo1 = {13, 13, 0.1, 180, 1.0, 0.0, 0.0, true, {13, 13, 0.25f, 5.0f, 0, false}};
Inimigo inimigo2 = {13, 6, 0.1, 180, 1.0, 0.0, 1.0, true, {13, 13, 0.25f, 5.0f, 0, false}};
Inimigo inimigo3 = {13, 1, 0.1, -90, 0.0, 1.0, 1.0, true, {13, 13, 0.25f, 5.0f, 0, false}};

//CallBacks das funções.
void init(void);
void keyboard (unsigned char key, int x, int y);
void display(void);
void reshape (int w, int h);
void atira(int value);
bool colidir(float jogadorX, float jogadorY, float tam_tank, float blocoX, float blocoY, float tam_bloco);
void bonus();
void aplicaBonus(int tipo_bonus);

void init(void){
  glClearColor (1.0, 1.0, 1.0, 1.0);
  glEnable(GL_DEPTH_TEST); // Algoritmo Z-Buffer
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  // Ativa o modelo de sombreamento de Gouraud.
  glShadeModel(GL_SMOOTH);
}

void display(){
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpa o Buffer de Cores
    glLoadIdentity();
    criaMapa(jogador, inimigo1, inimigo2, inimigo3);
    
    if(jogador.projetil.tiro){
		desenhaProjetil(jogador.projetil.xOrigem, jogador.projetil.yOrigem, jogador.projetil.direcao);
	}
	if(inimigo1.projetil.tiro){
		desenhaProjetil(inimigo1.projetil.xOrigem, inimigo1.projetil.yOrigem, inimigo1.projetil.direcao);
	}
	if(inimigo2.projetil.tiro){
		desenhaProjetil(inimigo2.projetil.xOrigem, inimigo2.projetil.yOrigem, inimigo2.projetil.direcao);
	}
	if(inimigo3.projetil.tiro){
		desenhaProjetil(inimigo3.projetil.xOrigem, inimigo3.projetil.yOrigem, inimigo3.projetil.direcao);
	}
	if(bonus_ativo == true){
		bonus();
	}
	
    glutSwapBuffers();
}

void reshape (int w, int h){
    // muda para o modo GL_PROJECTION e reinicia a matriz de projecao
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();

    // define o tamanho da area de desenho da janela
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    
    gluPerspective(40, (float)w/(float)h, 1.0, 50.0);
    gluLookAt(6.0,-5.0,15.0, 	// posição da câmera (olho) 
			  6.0,6.0,0.0, 	// centro da cena
			  0.0,1.0,0.0);
    glMatrixMode (GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y){
	switch (key) {
		//Atirar
		case 'q':
		case 'Q':
			if (jogador.projetil.tiro != true){
				PlaySound("sounds/fire.wav", NULL, SND_ASYNC);
				jogador.projetil.tiro = true;
				jogador.projetil.xOrigem = jogador.x;
				jogador.projetil.yOrigem = jogador.y;
				jogador.projetil.direcao = jogador.direcaoCano;
			}
			break;
	}
    glutPostRedisplay();
}

//************COLISÕES DO JOGADOR ***********//

void colisaoTiroBlocoJogador(Jogador *jogador){
	for(int i = 0; i < tamMapa; i++){
		for(int j = 0; j < tamMapa; j++){
			if (colidir(jogador->projetil.xOrigem, jogador->projetil.yOrigem, tam_projetil, i * tam_bloco, j * tam_bloco, tam_bloco) == true){
				//Se for um bloco que deve colidir
				if((mapa[i][j] == 2) || (mapa[i][j] == 3) || (mapa[i][j] == 6) || (mapa[i][j] == 7)){
					jogador->projetil.tiro = false;
					//Se tiver com BonusGun, destroi metal.
					if(bonus_gun){
						if(mapa[i][j] == 3){
							mapa[i][j] = 0;
						}
					}
					//Se for tijolo.
					if(mapa[i][j] == 2){
						//Destroi o bloco.
						mapa[i][j] = 0;
					}
					if (mapa[i][j] == 6){
						mapa[i][j] = 0;
						game_over = true;
						gameOverAudio = true;
					}
				}
			}
		}
	}
	glutPostRedisplay();
}

void colisaoTiroTanksJogador(Jogador *jogador, Inimigo *primeiroInimigo, Inimigo *segundoInimigo, Inimigo *terceiroInimigo){
	if (colidir(jogador->projetil.xOrigem, jogador->projetil.yOrigem, tam_projetil, primeiroInimigo->x * 1.0, primeiroInimigo->y * 1.0, 1.0) == true){
		primeiroInimigo->vivo = false;
		//Remove do tabuleiro
		primeiroInimigo->x = 99;
		primeiroInimigo->y = 99;
		jogador->projetil.tiro = false;
		explosion = true;
	}
	
	if (colidir(jogador->projetil.xOrigem, jogador->projetil.yOrigem, tam_projetil, segundoInimigo->x * 1.0, segundoInimigo->y * 1.0, 1.0) == true){
		segundoInimigo->vivo = false;
		//Remove do tabuleiro
		segundoInimigo->x = 99;
		segundoInimigo->y = 99;
		jogador->projetil.tiro = false;
		explosion = true;
	}
		
	if (colidir(jogador->projetil.xOrigem, jogador->projetil.yOrigem, tam_projetil, terceiroInimigo->x * 1.0, terceiroInimigo->y * 1.0, 1.0) == true){
		terceiroInimigo->vivo = false;
		//Remove do tabuleiro
		terceiroInimigo->x = 99;
		terceiroInimigo->y = 99;
		jogador->projetil.tiro = false;
		explosion = true;
	}
	glutPostRedisplay();
}
	
//************ COLISÕES DO INIMIGO ***********//

void colisaoTiroBlocoInimigo(Inimigo *inimigoAtual){
	for(int i = 0; i < tamMapa; i++){
		for(int j = 0; j < tamMapa; j++){
			if (colidir(inimigoAtual->projetil.xOrigem, inimigoAtual->projetil.yOrigem, tam_projetil, i * tam_bloco, j * tam_bloco, tam_bloco) == true){
				//Se for um bloco que deve colidir
				if((mapa[i][j] == 2) || (mapa[i][j] == 3) || (mapa[i][j] == 6) || (mapa[i][j] == 7)){
					inimigoAtual->projetil.tiro = false;
					//Se for tijolo.
					if(mapa[i][j] == 2){
						//Destroi o bloco.
						mapa[i][j] = 0;
					}
					if (mapa[i][j] == 6){
						mapa[i][j] = 0;
						explosion = true;
						game_over = true;
						gameOverAudio = true;
					}
				}
			}
		}
	}
	glutPostRedisplay();
}

void colisaoTiroTanksInimigo(Inimigo *inimigoAtual, Jogador *player){
	if (colidir(inimigoAtual->projetil.xOrigem, inimigoAtual->projetil.yOrigem, tam_projetil, player->x * 1.0, player->y * 1.0, 1.0) == true){
		inimigoAtual->projetil.tiro = false;
			//Decrementa a vida do jogador em 1.
			player->vida--;
			//Se ficar com 0 vidas, game over.
			printf("Vida: %d\n", player->vida);
			if(player->vida == 0){
				explosion = true;
				player->vivo = false;
				//Remove do tabuleiro
				player->x = 99;
				player->y = 99;
				game_over = true;
				gameOverAudio = true;
			}
	}
	glutPostRedisplay();
}
	

void atira(int value){
	/*
	*Função utilizada para fazer os tiros do jogador.
	*jogador.projetil.tiro verifica se o tiro foi efetuado.
	*jogador.projetil.direcao é a variavel que armazena a direção do tiro quando a tecla Q foi pressionada.	*
	*/
    if (jogador.projetil.tiro && jogador.vivo) {
    	switch(jogador.projetil.direcao){
			case 0:
				jogador.projetil.xOrigem += jogador.projetil.velocidade;
	        	if (jogador.projetil.xOrigem > jogador.x + jogador.projetil.distancia){
	            	jogador.projetil.tiro = false;
	            	jogador.projetil.xOrigem = jogador.x;
	        	}
				break;
			
			case 180:
				jogador.projetil.xOrigem -= jogador.projetil.velocidade;
				if (jogador.projetil.xOrigem < jogador.x - jogador.projetil.distancia){
		         	jogador.projetil.tiro = false;
		          	jogador.projetil.xOrigem = jogador.x;
				}
	        	break;
   	     
	        case -90:
				jogador.projetil.yOrigem += jogador.projetil.velocidade;
	        	if (jogador.projetil.yOrigem > jogador.y + jogador.projetil.distancia){
	            	jogador.projetil.tiro = false;
	            	jogador.projetil.yOrigem = jogador.y;
	        	}
	        	break;
	        
	        case 90:
				jogador.projetil.yOrigem -= jogador.projetil.velocidade;
	        	if (jogador.projetil.yOrigem < jogador.y - jogador.projetil.distancia){
	            	jogador.projetil.tiro = false;
	            	jogador.projetil.yOrigem = jogador.y;
	        	}
	        	break;
	        
			default:
				break;
		}
		colisaoTiroBlocoJogador(&jogador);
		colisaoTiroTanksJogador(&jogador, &inimigo1, &inimigo2, &inimigo3);
    }
    //Atualiza o tiro 60 frames por segundo, fazendo a animação da bala.
    glutPostRedisplay();
    glutTimerFunc(16, atira, 0);
}


void atiraInimigo(int value){
	/*
	*Função utilizada para fazer os tiros do inimigo.
	*inimigo.projetil.tiro verifica se o tiro foi efetuado.
	*inimigo.projetil.direcao é a variavel que armazena a direção do tiro.
	*/
	
	//Para o inimigo 1.
	
    if (inimigo1.projetil.tiro) {
    	switch(inimigo1.projetil.direcao){
			case 0:
				inimigo1.projetil.xOrigem += inimigo1.projetil.velocidade;
	        	if (inimigo1.projetil.xOrigem > inimigo1.x + inimigo1.projetil.distancia){
	            	inimigo1.projetil.tiro = false;
	            	inimigo1.projetil.xOrigem = inimigo1.x;
	        	}
				break;
			
			case 180:
				inimigo1.projetil.xOrigem -= inimigo1.projetil.velocidade;
				if (inimigo1.projetil.xOrigem < inimigo1.x - inimigo1.projetil.distancia){
		         	inimigo1.projetil.tiro = false;
		          	inimigo1.projetil.xOrigem = inimigo1.x;
				}
	        	break;
   	     
	        case -90:
				inimigo1.projetil.yOrigem += inimigo1.projetil.velocidade;
	        	if (inimigo1.projetil.yOrigem > inimigo1.y + inimigo1.projetil.distancia){
	            	inimigo1.projetil.tiro = false;
	            	inimigo1.projetil.yOrigem = inimigo1.y;
	        	}
	        	break;
	        
	        case 90:
				inimigo1.projetil.yOrigem -= inimigo1.projetil.velocidade;
	        	if (inimigo1.projetil.yOrigem < inimigo1.y - inimigo1.projetil.distancia){
	            	inimigo1.projetil.tiro = false;
	            	inimigo1.projetil.yOrigem = inimigo1.y;
	        	}
	        	break;
	        
			default:
				break;
		}
		colisaoTiroBlocoInimigo(&inimigo1);
		colisaoTiroTanksInimigo(&inimigo1, &jogador);
    }
    
    //Para o inimigo 2.
    if (inimigo2.projetil.tiro) {
    	switch(inimigo2.projetil.direcao){
			case 0:
				inimigo2.projetil.xOrigem += inimigo2.projetil.velocidade;
	        	if (inimigo2.projetil.xOrigem > inimigo2.x + inimigo2.projetil.distancia){
	            	inimigo2.projetil.tiro = false;
	            	inimigo2.projetil.xOrigem = inimigo2.x;
	        	}
				break;
			
			case 180:
				inimigo2.projetil.xOrigem -= inimigo2.projetil.velocidade;
				if (inimigo2.projetil.xOrigem < inimigo2.x - inimigo2.projetil.distancia){
		         	inimigo2.projetil.tiro = false;
		          	inimigo2.projetil.xOrigem = inimigo2.x;
				}
	        	break;
   	     
	        case -90:
				inimigo2.projetil.yOrigem += inimigo2.projetil.velocidade;
	        	if (inimigo2.projetil.yOrigem > inimigo2.y + inimigo2.projetil.distancia){
	            	inimigo2.projetil.tiro = false;
	            	inimigo2.projetil.yOrigem = inimigo2.y;
	        	}
	        	break;
	        
	        case 90:
				inimigo2.projetil.yOrigem -= inimigo2.projetil.velocidade;
	        	if (inimigo2.projetil.yOrigem < inimigo2.y - inimigo2.projetil.distancia){
	            	inimigo2.projetil.tiro = false;
	            	inimigo2.projetil.yOrigem = inimigo2.y;
	        	}
	        	break;
	        
			default:
				break;
		}
		colisaoTiroBlocoInimigo(&inimigo2);
		colisaoTiroTanksInimigo(&inimigo2, &jogador);
    }
    
    //Para o inimigo 3.
    if (inimigo3.projetil.tiro) {
    	switch(inimigo3.projetil.direcao){
			case 0:
				inimigo3.projetil.xOrigem += inimigo3.projetil.velocidade;
	        	if (inimigo3.projetil.xOrigem > inimigo3.x + inimigo3.projetil.distancia){
	            	inimigo3.projetil.tiro = false;
	            	inimigo3.projetil.xOrigem = inimigo3.x;
	        	}
				break;
			
			case 180:
				inimigo3.projetil.xOrigem -= inimigo3.projetil.velocidade;
				if (inimigo3.projetil.xOrigem < inimigo3.x - inimigo3.projetil.distancia){
		         	inimigo3.projetil.tiro = false;
		          	inimigo3.projetil.xOrigem = inimigo3.x;
				}
	        	break;
   	     
	        case -90:
				inimigo3.projetil.yOrigem += inimigo3.projetil.velocidade;
	        	if (inimigo3.projetil.yOrigem > inimigo3.y + inimigo3.projetil.distancia){
	            	inimigo3.projetil.tiro = false;
	            	inimigo3.projetil.yOrigem = inimigo3.y;
	        	}
	        	break;
	        
	        case 90:
				inimigo3.projetil.yOrigem -= inimigo3.projetil.velocidade;
	        	if (inimigo3.projetil.yOrigem < inimigo3.y - inimigo3.projetil.distancia){
	            	inimigo3.projetil.tiro = false;
	            	inimigo3.projetil.yOrigem = inimigo3.y;
	        	}
	        	break;
	        
			default:
				break;
		}
		colisaoTiroBlocoInimigo(&inimigo3);
		colisaoTiroTanksInimigo(&inimigo3, &jogador);
    }
    //Atualiza o tiro 60 frames por segundo, fazendo a animação da bala.
    glutPostRedisplay();
    glutTimerFunc(16, atiraInimigo, 0);
}

bool colidir(float jogadorX, float jogadorY, float tam_tank, float blocoX, float blocoY, float tam_bloco){
	if(jogadorY + tam_tank <= blocoY){
		return false;
	} 
	else if(jogadorY >= blocoY + tam_bloco){
		return false;
	} 
	else if(jogadorX + tam_tank <= blocoX){
		return false;
	} 
	else if(jogadorX >= blocoX + tam_bloco){
		return false;
	} 
	
	return true;
}

void colisaoBlocoMovimentoJogador(unsigned char key, Jogador *jogador){
	for(int i = 0; i < tamMapa; i++){
		for(int j = 0; j < tamMapa; j++){
			if (colidir(jogador->x, jogador->y, tam_tank, i * tam_bloco, j * tam_bloco, tam_bloco) == true){
				if (bonus_boat){
					if((mapa[i][j] == 2) || (mapa[i][j] == 3) || (mapa[i][j] == 6) || (mapa[i][j] == 7)){
						if(key==GLUT_KEY_UP) jogador->x -= jogador->velocidade;
				    	else if(key==GLUT_KEY_DOWN) jogador->x += jogador->velocidade;
				    	else if(key==GLUT_KEY_LEFT) jogador->y += jogador->velocidade;
				    	else if(key==GLUT_KEY_RIGHT) jogador->y -= jogador->velocidade;
					}
					
				}
				else{
					if((mapa[i][j] == 2) || (mapa[i][j] == 3) || (mapa[i][j] == 6) || (mapa[i][j] == 7) || mapa[i][j] == 1){
						if(key==GLUT_KEY_UP) jogador->x -= jogador->velocidade;
				    	else if(key==GLUT_KEY_DOWN) jogador->x += jogador->velocidade;
				    	else if(key==GLUT_KEY_LEFT) jogador->y += jogador->velocidade;
				    	else if(key==GLUT_KEY_RIGHT) jogador->y -= jogador->velocidade;
					}
					
				}
				
				if(bonus_ativo == true && bonusX == i && bonusY == j){
					bonus_ativo = false;
					printf("PEGOU O BONUS!\n");
					printf("TIPO BONUS: %d\n", tipo_bonus);
					aplicaBonus(tipo_bonus);
					
				}
			}
		}
	}
}

void colisaoBlocoMovimentoInimigo(int movimentoInimigo, Inimigo *inimigoAtual){
	for(int i = 0; i < tamMapa; i++){
		for(int j = 0; j < tamMapa; j++){
			if (colidir(inimigoAtual->x, inimigoAtual->y, tam_tank, i * tam_bloco, j * tam_bloco, tam_bloco) == true){
				if((mapa[i][j] == 2) || (mapa[i][j] == 3) || (mapa[i][j] == 6) || (mapa[i][j] == 7) || mapa[i][j] == 1){
					if(movimentoInimigo==1) inimigoAtual->x -= inimigoAtual->velocidade;
				    else if(movimentoInimigo==2) inimigoAtual->x += inimigoAtual->velocidade;
				    else if(movimentoInimigo==4) inimigoAtual->y += inimigoAtual->velocidade;
				    else if(movimentoInimigo==3) inimigoAtual->y -= inimigoAtual->velocidade;
				}
			}
		}
	}
}

int gerarNumeroAleatorio(int min, int max) {
    return min + rand() % (max - min + 1);
}

void movimentaInimigo(Inimigo *inimigoAtual, int movimento){
	switch(movimento){
		case 1:
			inimigoAtual->x += inimigoAtual->velocidade;
			inimigoAtual->direcaoCano = 0;
			glutPostRedisplay();
			break;
		
		case 2:
			inimigoAtual->x -= inimigoAtual->velocidade;
			inimigoAtual->direcaoCano = 180;
			glutPostRedisplay();
			break;
		
		case 3:
			inimigoAtual->y += inimigoAtual->velocidade;
			inimigoAtual->direcaoCano = -90;
			glutPostRedisplay();
			break;
		
		case 4:
			inimigoAtual->y -= inimigoAtual->velocidade;
			inimigoAtual->direcaoCano = 90;
			glutPostRedisplay();
			break;
		
		default:
			break;
	}
	colisaoBlocoMovimentoInimigo(movimento, inimigoAtual);
}

void sorteiaMovimento(int value){
	mov_inimigo1 = gerarNumeroAleatorio(1,4);
	mov_inimigo2 = gerarNumeroAleatorio(1,4);
	mov_inimigo3 = gerarNumeroAleatorio(1,4);
	
	glutPostRedisplay();
	glutTimerFunc(2000, sorteiaMovimento, 0);
}

void esperaMovimento(int value){
	//movimento = gerarNumeroAleatorio(1,4);
	//distanciaMovimento = gerarNumeroAleatorio(1,10);
	movimentaInimigo(&inimigo1, mov_inimigo1);
	if (inimigo1.projetil.tiro != true && inimigo1.vivo == true){
		inimigo1.projetil.tiro = true;
		inimigo1.projetil.xOrigem = inimigo1.x;
		inimigo1.projetil.yOrigem = inimigo1.y;
		inimigo1.projetil.direcao = inimigo1.direcaoCano;
	}
	movimentaInimigo(&inimigo2, mov_inimigo2);
	if (inimigo2.projetil.tiro != true && inimigo2.vivo == true){
		inimigo2.projetil.tiro = true;
		inimigo2.projetil.xOrigem = inimigo2.x;
		inimigo2.projetil.yOrigem = inimigo2.y;
		inimigo2.projetil.direcao = inimigo2.direcaoCano;
	}
	movimentaInimigo(&inimigo3, mov_inimigo3);
	if (inimigo3.projetil.tiro != true && inimigo3.vivo == true){
		inimigo3.projetil.tiro = true;
		inimigo3.projetil.xOrigem = inimigo3.x;
		inimigo3.projetil.yOrigem = inimigo3.y;
		inimigo3.projetil.direcao = inimigo3.direcaoCano;
	}
	glutPostRedisplay();
	glutTimerFunc(16, esperaMovimento, 0);
}

void specialKeyboard(int key, int x, int y){
	switch(key){
		case GLUT_KEY_UP:
			jogador.x += jogador.velocidade;
			jogador.direcaoCano = 0;
			glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN:
			jogador.x -= jogador.velocidade;
			jogador.direcaoCano = 180;
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:
			jogador.y += jogador.velocidade;
			jogador.direcaoCano = -90;
			glutPostRedisplay();
			break;
		case GLUT_KEY_LEFT:
			jogador.y -= jogador.velocidade;
			jogador.direcaoCano = 90;
			glutPostRedisplay();
			break;
		default:
			break;
	}
	colisaoBlocoMovimentoJogador(key, &jogador);
}

void verificaStatus(int value){
	//Verifica se ocorreu game over ou vitória.
	if(jogador.vivo && (inimigo1.vivo == false && inimigo2.vivo == false && inimigo3.vivo == false)){
		venceu = true;
		printf("VITORIA!\n");
	}
	else if(game_over){
		printf("GAME OVER!\n");
	} 
	glutPostRedisplay();
	glutTimerFunc(16, verificaStatus, 0);
}

//Preciso fazer uma função pra remover a wall depois de 10 segundos.
void bonusWall(int value){
	if(bonus_wall){
		bonus_wall = false;
		if(mapa[2][6] == 3){
			mapa[2][6] = 2;
		}
		if(mapa[1][6] == 3){
			mapa[1][6] = 2;
		}
		if(mapa[2][7] == 3){
			mapa[2][7] = 2;
		}
		if(mapa[2][8] == 3){
			mapa[2][8] = 2;
		}
		if(mapa[1][8] == 3){
			mapa[1][8] = 2;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(15000, bonusWall, 0);
}

void aplicaBonus(int tipo_bonus){
	switch(tipo_bonus){
	case 1:
		bonus_wall = true;
		printf("Paredes reforçadas para a aguia!\n");
		mapa[2][6] = 3;
		mapa[1][6] = 3;
		mapa[2][7] = 3;
		mapa[2][8] = 3;
		mapa[1][8] = 3;
		glutTimerFunc(15000, bonusWall, 0);
		glutPostRedisplay();
		break;
	case 2:
		jogador.vida++;
		printf("Uma vida a mais, Vidas: %d", jogador.vida);
		break;
	case 3:
		jogador.velocidade +=0.1;
		jogador.projetil.velocidade += 0.2;
		printf("Velocidade de movimento e de projetil aumentadas!\nVelocidade de movimento: %f\nVelocidade de projetil: %f", jogador.velocidade, jogador.projetil.velocidade);
		break;
	case 4:
		bonus_boat = true;
		printf("Agora é permitido andar sobre a água!\n");
		break;
	case 5:
		bonus_gun = true;
		printf("Agora é permitido quebrar metal!\n");
		break;
	default:
		break;
	}
}

void sorteiaBonus(int value){
	if(bonus_ativo == false){
		posicaoBonus = gerarNumeroAleatorio(1, 3);
		tipo_bonus = gerarNumeroAleatorio(1, 5);
		bonus_ativo = true;
	}
	glutPostRedisplay();
	glutTimerFunc(15000, sorteiaBonus, 0);
}

void bonus(){
	switch(posicaoBonus){
		case 1:
			bonusX = 5;
			bonusY = 4;
			desenhaBonus(tipo_bonus, bonusX, bonusY);
			break;
		case 2:
			bonusX = 4;
			bonusY = 10;
			desenhaBonus(tipo_bonus, bonusX, bonusY);
			break;
		case 3:
			bonusX = 9;
			bonusY = 7;
			desenhaBonus(tipo_bonus, bonusX, bonusY);
			break;
		default:
			break;
	}
}

int main(int argc, char** argv){
	glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1366,768);
    glutInitWindowPosition(250,150); 
    glutCreateWindow ("Tank-1990 3D");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    
    GLfloat light_position[] = {-1.0, 1.0, 1.0, 0.0};
	GLfloat light_color[] = {1.0, 1.0, 1.0, 0.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING); //Ativa o modelo de iluminacao
    glEnable(GL_LIGHT0); //Ativa a Luz 0. O OpenGL suporta pelo menos 8 pontos de luz

    // Inicia as caracteristicas gerais dos materiais
	GLfloat mat_ambient_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_diffuse);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL); //Um ou mais parametros do material rastreiam a cor atual do glColor.


    // define a cor com a qual a tela sera apagada
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    glutTimerFunc(0, atira, 0); //(mseg, timer, value)
    glutTimerFunc(0, esperaMovimento, 0);
    glutTimerFunc(0, atiraInimigo, 0);
    glutTimerFunc(0, verificaStatus, 0);
    glutTimerFunc(15000, sorteiaBonus, 0);
    glutTimerFunc(0, sorteiaMovimento, 0);
    init();
    
    glutMainLoop();
    
	return EXIT_SUCCESS;
}