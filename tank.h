//Implementação do visual do tank.
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

void desenhaTank(float i, float j, float direcao, int R, int G, int B){
	glPushMatrix();
		glColor3f(R, G, B);
		glScalef (1.0, 1.0, 0.5);
		glTranslatef (j*1, i*1, 1.0);
		glutSolidCube(1.0);
		
		glPushMatrix();
			glColor3f(R - 0.1, G - 0.1, B - 0.1);
			glScalef(0.5, 0.5, 1.0);
			glTranslatef(0, 0.5, 0.25);
			glutSolidCube(1.0);
        glPopMatrix();
		
		glPushMatrix();
			glScalef (0.3, 1.0, 0.5);
			glTranslatef(0, 0.5, 0);
			glutSolidCube(1.0);
		glPopMatrix();
    glPopMatrix();
}