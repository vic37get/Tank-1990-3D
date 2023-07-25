//Criação dos tipos de bonus.
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

void visualBonus(float i, float j, int rotacao, float R, float G, float B){
	glPushMatrix();
		glColor3f(R, G, B);
		glTranslatef (j*1, i*1, 0.5);
		glScalef (0.8, 0.8, 1.0);
		glRotatef(rotacao, 0.0, 0.0, 1.0);
		glutSolidCube(1.0);
    glPopMatrix();
}

void desenhaBonus(int tipo_bonus, float i, float j, int rotacao){
	switch(tipo_bonus){
	case 1:
		//Cria uma barreira de pedra ao redor da aguia.
		visualBonus(i, j, rotacao, 0.0, 1.0, 0.2);
		break;
	case 2:
		//Adiciona uma vida ao jogador.
		visualBonus(i, j, rotacao, 1.0, 0.5, 0.2);
		break;
	case 3:
		//Adiciona velocidade de movimento ao jogador e velocidade de tiro.
		visualBonus(i, j, rotacao, 0.0, 0.5, 0.9);
		break;
	case 4:
		//Permite andar na água.
		visualBonus(i, j, rotacao, 0.0, 0.5, 0.2);
		break;
	case 5:
		//Destroi blocos de metal.
		visualBonus(i, j, rotacao, 0.0, 0.8, 1.0);
		break;
	default:
		break;
	}
	
}