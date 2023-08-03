#ifndef TEXTOS_H
#define TEXTOS_H


void desenhaVidasJogador(int vidas){
	char texto1[19] = "Vidas do Jogador: ";
    stringstream ss;
    ss<<vidas;
    string str = ss.str();
    int i = 0;
    glDisable(GL_TEXTURE_2D);
    GLfloat w = 1.0, h = 1.0, x = 0, y = 0;
    glPushMatrix();
    	glTranslatef(15.6, -5, 0);
    	glColor3f(1.0, 1.0, 1.0);
    	glRasterPos2f(0.0,15);
    	for(i = 0; i<=static_cast<int>(strlen(texto1)); i++){
    		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,texto1[i]);
		}
    glPopMatrix();
    
    glPushMatrix();
    	glColor3f(0.0, 1.0, 0.0);
		glTranslatef(15.5, 3.0, 0.5);
		for (int i = 0; i < vidas; i++){
			blocoVida(5, i, x, y, h, w);
		}
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
}

void desenhaVidasInimigo(int vidas){
	char texto[25] = "Vidas dos Inimigos: ";
    stringstream ss;
    ss<<vidas;
    string str = ss.str();
    int i = 0;
	glDisable(GL_TEXTURE_2D);
	GLfloat w = 1.0, h = 1.0, x = 0, y = 0;
	glPushMatrix();
		glTranslatef(16, -2, 0);
		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2f(0.0,15);
		for(i = 0; i<=static_cast<int>(strlen(texto)); i++){
    		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,texto[i]);
		}
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glTranslatef(15.8, 5.8, 0.5);
		for (int i = 0; i < vidas; i++){
			blocoVida(5, i, x, y, h, w);
		}
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
}

#endif