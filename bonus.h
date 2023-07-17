//Criação dos tipos de bonus.
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

void bonusGun(int i, int j){
	glPushMatrix();
		glColor3f(0.0, 0.5, 0.2);
		glTranslatef (j*1, i*1, 0.5);
		glScalef (0.8, 0.8, 1.0);
		glutSolidCube(1.0);	
    glPopMatrix();
}