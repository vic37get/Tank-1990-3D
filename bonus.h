//Visual do bonus

void visualBonus(float i, float j, int rotacao){
	glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef (j*1, i*1, 0.5);
		glScalef (0.8, 0.8, 0.8);
		glRotatef(rotacao, 0.0, 0.0, 1.0);
		draw_object_smooth();
    glPopMatrix();
}