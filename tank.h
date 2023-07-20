//Implementação do visual do tank.
#ifndef TANK_H
#define TANK_H
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "bloco.h"

void desenhaTank(float i, float j, int direcao, int R, int G, int B){
	//Corpo do tank.
	glPushMatrix();
		glColor3f(R, G, B);
		glTranslatef (j*1, i*1, 0.5);
		glScalef (1.0, 1.0, 0.6);
		draw_object_smooth();
		glRotatef(direcao, 0.0 , 0.0 , 1.0);
		//Parte de cima do tank.
		glPushMatrix();
			glColor3f(R - 0.1, G - 0.1, B - 0.1);
			glTranslatef(0, 0, 0.25);
			glScalef(0.6, 0.6, 0.7);
			draw_object_smooth();
        glPopMatrix();
		//Cano do tank.
		glPushMatrix();
			glTranslatef(0, 0.5, 0.3);
			glScalef (0.3, 1.0, 0.25);
			draw_object_smooth();
		glPopMatrix();
    glPopMatrix();
}
#endif