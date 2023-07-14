//Implementação do projetil (munição)
#ifndef PROJETIL_H
#define PROJETIL_H
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

typedef struct{
	float xOrigem;
	float yOrigem;
	float velocidade;
	
}Projetil;

void desenhaProjetil(Projetil projetil){
	
	glPushMatrix();
		glColor3f(0.8, 0.8, 0.0);
		glScalef (0.3, 0.3, 0.5);
		glTranslatef (projetil.yOrigem*1 +15, projetil.xOrigem*1 + 15, 1.0);
		glutSolidCube(1.0);
	glPopMatrix();
}

#endif