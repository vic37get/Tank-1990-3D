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
*/

void chao(){
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glutSolidCube(1.0);
    glPopMatrix();
}

void agua(){
	glPushMatrix();
		glColor3f(0.0, 0.0, 1.0);
		glutSolidCube(1.0);
    glPopMatrix();
}

void tijolo(){
	glPushMatrix();
		glColor3f(1.0, 0.5, 0.0);
		glutSolidCube(1.0);
    glPopMatrix();
}

void metal(){
	glPushMatrix();
		glColor3f(0.6, 0.6, 0.6);
		glutSolidCube(1.0);
    glPopMatrix();
}

void arbusto(){
	glPushMatrix();
		glColor3f(0.0, 1.0, 0.0);
		glutSolidCube(1.0);
    glPopMatrix();
}

void pista(){
	glPushMatrix();
		glColor3f(0.8, 0.8, 0.8);
		glutSolidCube(1.0);
    glPopMatrix();
}

//Implementar o mais parecido possivel.
void aguia(){
	glPushMatrix();
		glColor3f(0.9, 0.9, 0.9);
		glutSolidCube(1.0);
    glPopMatrix();
}