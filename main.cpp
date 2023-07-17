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

// Instancia de Jogador.
// Jogador jogador = {1.5, 5.5, 0.08, 0, 1.0, 1.0, 0.0};
// 
// Instancia de Inimigo.
// Inimigo inimigo1 = {13.0, 13.0, 0.08, 0, 1.0, 0.0, 0.0};
// Inimigo inimigo2 = {13.0, 6.5, 0.08, 0, 1.0, 0.0, 1.0};
// Inimigo inimigo3 = {13.0, 1.5, 0.08, 0, 0.0, 1.0, 1.0};

//Instancia de Jogador.

//X, Y, Velocidade, DirecaoCano, R, G, B, Vidas, Vivo.
Projetil projetilJogador  = {1, 4, 5};
Jogador jogador = {1, 4, 0.08, 0, 1.0, 1.0, 0.0, 3, false};

//Instancia de Inimigo.
Inimigo inimigo1 = {13, 13, 0.08, 0, 1.0, 0.0, 0.0};
Inimigo inimigo2 = {13, 6, 0.08, 0, 1.0, 0.0, 1.0};
Inimigo inimigo3 = {13, 1, 0.08, 0, 0.0, 1.0, 1.0};

//CallBacks das funções.
void init(void);
void keyboard (unsigned char key, int x, int y);
void display(void);
void reshape (int w, int h);

void init(void){
  glClearColor (1.0, 1.0, 1.0, 1.0);
  glEnable(GL_DEPTH_TEST); // Algoritmo Z-Buffer
}

void display(){
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpa o Buffer de Cores
    glLoadIdentity();
    criaMapa(jogador, inimigo1, inimigo2, inimigo3, projetilJogador);
	if (jogador.projetil.tiro){
		desenhaProjetil(jogador.projetil.xOrigem, jogador.projetil.yOrigem);
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
    gluLookAt(6.0, 6.0, 13.0, 	// posição da câmera (olho) 
			  6.0, 6.0, 6.0, 	// centro da cena
			  0.0, 1.0, 0.0); // sentido ou orientacao da camera (de cabeca para cima)
    // muda para o modo GL_MODELVIEW para desenhar na tela
    glMatrixMode (GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y){
	switch (key) {
		//Atirar
		case 'q':
			jogador.projetil.tiro = true;
			jogador.projetil.xOrigem = jogador.x;
			jogador.projetil.yOrigem = jogador.y;
			break;
		case 'Q':
			break;
	}
    glutPostRedisplay();
}

void updateTiro(int value) {
    if (jogador.projetil.tiro) {
        jogador.projetil.xOrigem += 1.0f;

        if (jogador.projetil.xOrigem > 1.0f) {
            jogador.projetil.tiro = false;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateTiro, 0);
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
			jogador.direcaoCano = 10;
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:
			jogador.y += jogador.velocidade;
			jogador.direcaoCano = 180;
			glutPostRedisplay();
			break;
		case GLUT_KEY_LEFT:
			jogador.y -= jogador.velocidade;
			jogador.direcaoCano = -90;
			glutPostRedisplay();
			break;
	}
}

int main(int argc, char** argv){
	glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1366,768);
    glutInitWindowPosition(500,100); 
    glutCreateWindow ("Tank-1990 3D");
    
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, updateTiro, 0);
    glutSpecialFunc(specialKeyboard);
    glutMainLoop();
    
	return EXIT_SUCCESS;
}
