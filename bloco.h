//Criação dos tipos de bloco
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

/*
- Detalhamento do Mapa
	- Chão: 0
	- Agua: 1
	- Tijolo: 2
	- Metal: 3
	- Arbusto: 4
	- Pista: 5
	- Aguia: 6
	- Parede: 7
*/


void parede(int h, int w, int x, int y, int j, int i){
	glPushMatrix();
		glColor3f(0.2, 0.2, 0.2);
		glScalef (1.0, 1.0, 0.5);
		glTranslatef (j*h+x, i*w+y, 0.5);
		glutSolidCube(1.0);	
    glPopMatrix();
}

void tijolo(int h, int w, int x, int y, int j, int i){
	glPushMatrix();
		glColor3f(1.0, 0.5, 0.0);
		glScalef (1.0, 1.0, 0.5);
		glTranslatef (j*h+x, i*w+y, 0.5);
		glutSolidCube(1.0);
    glPopMatrix();
}

void metal(int h, int w, int x, int y, int j, int i){
	glPushMatrix();
		glColor3f(0.8, 0.8, 0.8);
		glScalef (1.0, 1.0, 0.5);
		glTranslatef (j*h+x, i*w+y, 0.5);
		glutSolidCube(1.0);
    glPopMatrix();
}

void arbusto(int h, int w, int x, int y, int j, int i){
	glPushMatrix();
		glColor3f(0.5, 1.0, 0.3);
		glScalef (1.0, 1.0, 0.5);
		glTranslatef (j*h+x, i*w+y, 0.5);
		glutSolidCube(1.0);
    glPopMatrix();
}

//Implementar o mais parecido possivel.
void aguia(int h, int w, int x, int y, int j, int i){
	glPushMatrix();
		glColor3f(0.6, 0.6, 0.6);
		glScalef (1.0, 1.0, 0.5);
		glTranslatef (j*h+x, i*w+y, 0.5);
		glutSolidCube(1.0);
    glPopMatrix();
}

void chao(int h, int w, int x, int y, int j, int i){
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glScalef (1.0, 1.0, 0.1);
		glTranslatef (j*h+x, i*w+y, 0.5);
		glutSolidCube(1.0);	
    glPopMatrix();
}

void agua(int h, int w, int x, int y, int j, int i){
	glPushMatrix();
		glColor3f(0.0, 0.3, 1.0);
		glScalef (1.0, 1.0, 0.1);
		glTranslatef (j*h+x, i*w+y, 0.5);
		glutSolidCube(1.0);
    glPopMatrix();
}

void pista(int h, int w, int x, int y, int j, int i){
	glPushMatrix();
		glColor3f(0.7, 0.7, 0.7);
		glScalef (1.0, 1.0, 0.1);
		glTranslatef (j*h+x, i*w+y, 0.5);
		glutSolidCube(1.0);
    glPopMatrix();
}