//Implementação do visual do tank.
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

void desenhaTank(float i, float j, float direcao, int R, int G, int B){
	glPushMatrix();
		glColor3f(R, G, B);
		glTranslatef (j*1, i*1, 0.5);
		glScalef (1.0, 1.0, 0.8);
		glutSolidCube(1.0);
		
		glPushMatrix();
			glColor3f(R - 0.1, G - 0.1, B - 0.1);
			glTranslatef(0, 0, 0.25);
			glScalef(0.6, 0.6, 1.0);
			glutSolidCube(1.0);
        glPopMatrix();
		
		glPushMatrix();
			glTranslatef(0, 0.5, 0);
			glScalef (0.3, 1.0, 0.5);
			glutSolidCube(1.0);
		glPopMatrix();
    glPopMatrix();
}