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

void desenhaProjetil(float xOrigem, float yOrigem){
	printf("Projetil x e y: %f, %f\n", xOrigem, yOrigem);
	glPushMatrix();
		glColor3f(1.0, 1.0, 0.0);
		glTranslatef (yOrigem*1, xOrigem*1, 0.5);
		glScalef (0.3, 0.4, 0.8);
		glutSolidCube(1.0);
	glPopMatrix();
}
#endif