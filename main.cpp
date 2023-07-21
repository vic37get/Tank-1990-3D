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


#include "mapa.h"
#include "jogador.h"
#include "inimigo.h"
#include "projetil.h"

// Variaveis Globais
int h, w = 0;
bool game_over = false;
int proximo_move = 0;

//Instancia de Jogador.
//X, Y, Velocidade, DirecaoCano, R, G, B, Vidas, Vivo. Projetil{ x, y, velocidade, distancia, direcao, tiro.}
Jogador jogador = {1, 4, 0.1, 0, 1.0, 1.0, 0.0, 3, true, {1, 4, 0.25f, 5.0f, 0, false}};

//Instancia de Inimigo.
//x, y, velocidade, direcaoCano, R, G, B, vivo. Projetil{ x, y, velocidade, distancia, direcao, tiro.}
Inimigo inimigo1 = {13, 13, 0.2, 180, 1.0, 0.0, 0.0, true, {13, 13, 0.25f, 5.0f, 0, false}};
Inimigo inimigo2 = {13, 6, 0.2, 180, 1.0, 0.0, 1.0, true, {13, 13, 0.25f, 5.0f, 0, false}};
Inimigo inimigo3 = {13, 1, 0.2, -90, 0.0, 1.0, 1.0, true, {13, 13, 0.25f, 5.0f, 0, false}};

//CallBacks das funções.
void init(void);
void keyboard (unsigned char key, int x, int y);
void display(void);
void reshape (int w, int h);
void atira(int value);
bool colidir(float jogadorX, float jogadorY, float tam_tank, float blocoX, float blocoY, float tam_bloco);

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

    // Define a forma do volume de visualizacao para termos
    // uma projecao perspectiva (3D).
    // gluPerspective(70, (float)w/(float)h, 1.0, 80.0); //(angulo, aspecto, ponto_proximo, ponto distante)
    // gluLookAt(6.0, 6.0, 14.0, 	// posição da câmera (olho) 
			 //  6.0, 6.0, 0.0, 	// centro da cena
			 //  0.0, 1.0, 0.0); // sentido ou orientacao da camera (de cabeca para cima)
    // muda para o modo GL_MODELVIEW para desenhar na tela
    glMatrixMode (GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y){
	switch (key) {
		//Atirar
		case 'q':
		case 'Q':
			if (jogador.projetil.tiro != true){
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
					//Se for tijolo.
					if(mapa[i][j] == 2){
						//Destroi o bloco.
						mapa[i][j] = 0;
					}
					if (mapa[i][j] == 6){
						mapa[i][j] = 0;
						game_over = true;
					}
				}
			}
		}
	}
	glutPostRedisplay();
}

void colisaoTiroTanksJogador(Jogador *jogador, Inimigo *primeiroInimigo, Inimigo *segundoInimigo, Inimigo *terceiroInimigo){
	for(int i = 0; i < tamMapa; i++){
		for(int j = 0; j < tamMapa; j++){
			if (colidir(jogador->projetil.xOrigem, jogador->projetil.yOrigem, tam_projetil, i * tam_bloco, j * tam_bloco, tam_bloco) == true){
				//printf("Inimigo.x: %d, Inimigo.y: %d\n", inimigo1.x, inimigo1.y);
				if(primeiroInimigo->x == i && primeiroInimigo->y == j){
					jogador->projetil.tiro = false;
					primeiroInimigo->vivo = false;
				}
				
				if(segundoInimigo->x == i && segundoInimigo->y == j){
					jogador->projetil.tiro = false;
					segundoInimigo->vivo = false;
				}
				
				if(terceiroInimigo->x == i && terceiroInimigo->y == j){
					jogador->projetil.tiro = false;
					terceiroInimigo->vivo = false;
				}
			}
		}
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
						game_over = true;
					}
				}
			}
		}
	}
	glutPostRedisplay();
}



void colisaoTiroTanksInimigo(Inimigo *inimigoAtual, Jogador *player, Inimigo *primeiroInimigo, Inimigo *segundoInimigo){
	for(int i = 0; i < tamMapa; i++){
		for(int j = 0; j < tamMapa; j++){
			if (colidir(inimigoAtual->projetil.xOrigem, inimigoAtual->projetil.yOrigem, tam_projetil, i * tam_bloco, j * tam_bloco, tam_bloco) == true){
				//Se o inimigo atirar no jogador.
				if(player->x == i && player->y == j){
					inimigoAtual->projetil.tiro = false;
					//Decrementa a vida do jogador em 1.
					player->vida--;
					//Se ficar com 0 vidas, game over.
					if(player->vida == 0){
						game_over = true;
					}
				}
				
				if(primeiroInimigo->x == i && primeiroInimigo->y == j){
					inimigoAtual->projetil.tiro = false;
					primeiroInimigo->vivo = false;
				}
				
				if(segundoInimigo->x == i && segundoInimigo->y == j){
					inimigoAtual->projetil.tiro = false;
					segundoInimigo->vivo = false;
				}
			}
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
    if (jogador.projetil.tiro) {
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
				if((mapa[i][j] == 2) || (mapa[i][j] == 3) || (mapa[i][j] == 6) || (mapa[i][j] == 7)){
					if(key==GLUT_KEY_UP) jogador->x -= jogador->velocidade;
				    else if(key==GLUT_KEY_DOWN) jogador->x += jogador->velocidade;
				    else if(key==GLUT_KEY_LEFT) jogador->y += jogador->velocidade;
				    else if(key==GLUT_KEY_RIGHT) jogador->y -= jogador->velocidade;
				}
			}
		}
	}
}

void colisaoBlocoMovimentoInimigo(int movimentoInimigo, Inimigo *inimigoAtual){
	for(int i = 0; i < tamMapa; i++){
		for(int j = 0; j < tamMapa; j++){
			if (colidir(inimigoAtual->x, inimigoAtual->y, tam_tank, i * tam_bloco, j * tam_bloco, tam_bloco) == true){
				if((mapa[i][j] == 2) || (mapa[i][j] == 3) || (mapa[i][j] == 6) || (mapa[i][j] == 7)){
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

void movimentaInimigo(Inimigo *inimigoAtual){
	int movimento;
	movimento = gerarNumeroAleatorio(1,4);
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

void esperaMovimento(int value){
	movimentaInimigo(&inimigo1);
	
	movimentaInimigo(&inimigo2);
	movimentaInimigo(&inimigo3);
	glutPostRedisplay();
	glutTimerFunc(1000, esperaMovimento, 0);
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
    init();
    
    glutMainLoop();
    
	return EXIT_SUCCESS;
}
