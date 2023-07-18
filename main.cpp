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

void init(void){
  glClearColor (1.0, 1.0, 1.0, 1.0);
  glEnable(GL_DEPTH_TEST); // Algoritmo Z-Buffer
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

    // Define a forma do volume de visualizacao para termos
    // uma projecao perspectiva (3D).
    gluPerspective(70, (float)w/(float)h, 1.0, 80.0); //(angulo, aspecto, ponto_proximo, ponto distante)
    gluLookAt(6.0, 6.0, 14.0, 	// posição da câmera (olho) 
			  6.0, 6.0, 0.0, 	// centro da cena
			  0.0, 1.0, 0.0); // sentido ou orientacao da camera (de cabeca para cima)
    // muda para o modo GL_MODELVIEW para desenhar na tela
    glMatrixMode (GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y){
	switch (key) {
		//Atirar
		case 'q':
		case 'Q':
			jogador.projetil.tiro = true;
			jogador.projetil.xOrigem = jogador.x;
			jogador.projetil.yOrigem = jogador.y;
			jogador.projetil.direcao = jogador.direcaoCano;
			break;
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
    }
    //Atualiza o tiro 60 frames por segundo, fazendo a animação da bala.
    glutPostRedisplay();
    glutTimerFunc(16, atira, 0);
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

    // Ativa o modelo de sombreamento de Gouraud.
    glShadeModel(GL_SMOOTH);

    // Ativa o z-buffering, de modo a remover as superficies escondidas
    glEnable(GL_DEPTH_TEST);

    // define a cor com a qual a tela sera apagada
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    glutTimerFunc(0, atira, 0); //(mseg, timer, value)
    init();
    
    glutMainLoop();
    
	return EXIT_SUCCESS;
}
