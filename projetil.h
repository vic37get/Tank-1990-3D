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
	float tiro;
	
}Projetil;

void desenhaProjetil(float yorigem, float xorigem){
	
	glPushMatrix();
		glColor3f(0.8, 0.8, 0.0);
		glTranslatef (yorigem*1, xorigem*1, 0.5);
		glScalef (0.2, 0.2, 0.2);
		glutSolidCube(1.0);
	glPopMatrix();
}

#endif