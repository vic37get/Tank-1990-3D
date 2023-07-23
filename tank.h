//Implementação do visual do tank.
#ifndef TANK_H
#define TANK_H
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "bloco.h"

float tam_tank = 0.8;

void desenhaTank(float i, float j, int direcao, int R, int G, int B){
	//Corpo do tank.
	glPushMatrix();
		glColor3f(R, G, B);
		glTranslatef (j*1, i*1, 0.5);
		glScalef (tam_tank, tam_tank, 0.5);
		draw_object_smooth();
		glRotatef(direcao, 0.0 , 0.0 , 1.0);
		//Esteira direita.
		glPushMatrix();
			glColor3f(0.1, 0.1, 0.1);
			glTranslatef(0.55, 0, 0);
			glScalef (0.3, 1.3, 0.6);
			draw_object_smooth();
		glPopMatrix();
		//Esteira esquerda.
		glPushMatrix();
			glColor3f(0.1, 0.1, 0.1);
			glTranslatef(-0.55, 0, 0);
			glScalef (0.3, 1.3, 0.6);
			draw_object_smooth();
		glPopMatrix();
		//Parte de cima do tank.
		glPushMatrix();
			glColor3f(R - 0.5, G - 0.5, B - 0.5);
			glTranslatef(0, 0, 0.5);
			glScalef(0.6, 0.6, 0.7);
			draw_object_smooth();
        glPopMatrix();
		//Cano do tank.
		glPushMatrix();
			glTranslatef(0, 0.5, 0.3);
			glScalef (0.3, 1.2, 0.3);
			draw_object_smooth();
		glPopMatrix();
    glPopMatrix();
}
#endif