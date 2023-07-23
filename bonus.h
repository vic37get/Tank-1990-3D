//Criação dos tipos de bonus.
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

//Cria uma barreira de pedra ao redor da aguia.
void bonusStoneWall(int i, int j){
	glPushMatrix();
		glColor3f(0.0, 1.0, 0.2);
		glTranslatef (j*1, i*1, 0.5);
		glScalef (0.8, 0.8, 1.0);
		glutSolidCube(1.0);	
    glPopMatrix();
}

//Adiciona uma vida ao jogador.
void bonusAddVida(int i, int j){
	glPushMatrix();
		glColor3f(1.0, 0.5, 0.2);
		glTranslatef (j*1, i*1, 0.5);
		glScalef (0.8, 0.8, 1.0);
		glutSolidCube(1.0);	
    glPopMatrix();
}

//Adiciona velocidade de movimento ao jogador e velocidade de tiro.
void bonusSpeed(int i, int j){
	glPushMatrix();
		glColor3f(0.0, 0.5, 0.9);
		glTranslatef (j*1, i*1, 0.5);
		glScalef (0.8, 0.8, 1.0);
		glutSolidCube(1.0);	
    glPopMatrix();
}

//Permite andar na água.
void bonusBoat(int i, int j){
	glPushMatrix();
		glColor3f(0.0, 0.5, 0.2);
		glTranslatef (j*1, i*1, 0.5);
		glScalef (0.8, 0.8, 1.0);
		glutSolidCube(1.0);	
    glPopMatrix();
}

//Destroi blocos de metal.
void bonusGun(int i, int j){
	glPushMatrix();
		glColor3f(0.0, 0.8, 1.0);
		glTranslatef (j*1, i*1, 0.5);
		glScalef (0.8, 0.8, 1.0);
		glutSolidCube(1.0);	
    glPopMatrix();
}

void desenhaBonus(int tipo_bonus, int i, int j){
	switch(tipo_bonus){
	case 1:
		bonusStoneWall(i, j);
		break;
	case 2:
		bonusAddVida(i, j);
		break;
	case 3:
		bonusSpeed(i, j);
		break;
	case 4:
		bonusBoat(i, j);
		break;
	case 5:
		bonusGun(i, j);
		break;
	default:
		break;
	}
	
}