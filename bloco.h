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

// void parede(int i, int j){
// 	glPushMatrix();
// 		glColor3f(0.3, 0.3, 0.3);
// 		glScalef (0.5, 0.5, 0.8);
// 		glTranslatef (j*1, i*1, 0.5);
// 		glutSolidCube(1.0);	
//     glPopMatrix();
// }
// 
// void tijolo(int i, int j){
// 	glPushMatrix();
// 		glColor3f(1.0, 0.5, 0.0);
// 		glScalef (0.5, 0.5, 0.7);
// 		glTranslatef (j*1, i*1, 0.5);
// 		glutSolidCube(1.0);
//     glPopMatrix();
// }
// 
// void metal(int i, int j){
// 	glPushMatrix();
// 		glColor3f(0.9, 0.9, 0.9);
// 		glScalef (0.5, 0.5, 0.7);
// 		glTranslatef (j*1, i*1, 0.5);
// 		glutSolidCube(1.0);
//     glPopMatrix();
// }
// 
// void arbusto(int i, int j){
// 	glPushMatrix();
// 		glColor3f(0.0, 0.7, 0.0);
// 		glScalef (0.5, 0.5, 0.7);
// 		glTranslatef (j*1, i*1, 0.5);
// 		glutSolidCube(1.0);
//     glPopMatrix();
// }
// 
//Implementar o mais parecido possivel.
// void aguia(int i, int j){
// 	glPushMatrix();
// 		glColor3f(0.6, 0.6, 0.6);
// 		glScalef (0.5, 0.5, 0.5);
// 		glTranslatef (j*1, i*1, 0.5);
// 		glutSolidCube(1.0);
//     glPopMatrix();
// }
// 
// void chao(int i, int j){
// 	glPushMatrix();
// 		glColor3f(0.1, 0.1, 0.1);
// 		glScalef (0.5, 0.5, 0.1);
// 		glTranslatef (j*1, i*1, 0.5);
// 		glutSolidCube(1.0);	
//     glPopMatrix();
// }
// 
// void agua(int i, int j){
// 	glPushMatrix();
// 		glColor3f(0.0, 0.5, 1.0);
// 		glScalef (0.5, 0.5, 0.1);
// 		glTranslatef (j*1, i*1, 0.5);
// 		glutSolidCube(1.0);
//     glPopMatrix();
// }
// 
// void pista(int i, int j){
// 	glPushMatrix();
// 		glColor3f(0.7, 0.7, 0.7);
// 		glScalef (0.5, 0.5, 0.1);
// 		glTranslatef (j*1, i*1, 0.5);
// 		glutSolidCube(1.0);
//     glPopMatrix();
// }


void parede(int i, int j){
	glPushMatrix();
		glColor3f(0.3, 0.3, 0.3);
		//glScalef (1.0, 1.0, 0.8);
		glScalef (1.0, 1.0, 0.0);
		glTranslatef (j*1, i*1, 0.5);
		glutSolidCube(1.0);	
    glPopMatrix();
}

void tijolo(int i, int j){
	glPushMatrix();
		glColor3f(1.0, 0.5, 0.0);
		//glScalef (1.0, 1.0, 0.7);
		glScalef (1.0, 1.0, 0.0);
		glTranslatef (j*1, i*1, 0.5);
		glutSolidCube(1.0);
    glPopMatrix();
}

void metal(int i, int j){
	glPushMatrix();
		glColor3f(0.9, 0.9, 0.9);
		//glScalef (1.0, 1.0, 0.7);
		glScalef (1.0, 1.0, 0.0);
		glTranslatef (j*1, i*1, 0.5);
		glutSolidCube(1.0);
    glPopMatrix();
}

void arbusto(int i, int j){
	glPushMatrix();
		glColor3f(0.0, 0.7, 0.0);
		//glScalef (1.0, 1.0, 0.7);
		glScalef (1.0, 1.0, 0.0);
		glTranslatef (j*1, i*1, 0.5);
		glutSolidCube(1.0);
    glPopMatrix();
}

//Implementar o mais parecido possivel.
void aguia(int i, int j){
	glPushMatrix();
		glColor3f(0.6, 0.6, 0.6);
		//glScalef (1.0, 1.0, 0.5);
		glScalef (1.0, 1.0, 0.0);
		glTranslatef (j*1, i*1, 0.5);
		glutSolidCube(1.0);
    glPopMatrix();
}

void chao(int i, int j){
	glPushMatrix();
		glColor3f(0.1, 0.1, 0.1);
		glScalef (1.0, 1.0, 0.1);
		glTranslatef (j*1, i*1, 0.5);
		glutSolidCube(1.0);	
    glPopMatrix();
}

void agua(int i, int j){
	glPushMatrix();
		glColor3f(0.0, 0.5, 1.0);
		glScalef (1.0, 1.0, 0.1);
		glTranslatef (j*1, i*1, 0.5);
		glutSolidCube(1.0);
    glPopMatrix();
}

void pista(int i, int j){
	glPushMatrix();
		glColor3f(0.7, 0.7, 0.7);
		glScalef (1.0, 1.0, 0.1);
		glTranslatef (j*1, i*1, 0.5);
		glutSolidCube(1.0);
    glPopMatrix();
}